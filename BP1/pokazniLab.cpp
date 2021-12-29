#include <iostream>
#include <exception>
#include <string>
#include "sqlite3.h"

using namespace std;

// Otvaranje baze podataka
sqlite3* openDatabase(const char* url) {
    sqlite3* db = nullptr;
    // Svaka funkcija vraća kod greške.
    // 1. putanja do baze
    // 2. vraća sqlite3* koji predstavlja našu bazu
    int rc = sqlite3_open(url, &db);
    if (rc != SQLITE_OK) {
        // Greška se obrađuje izuzetkom
        throw string("Kod pri otvaranju: ") + to_string(rc);
    }
    return db;
}

// Zatvaranje baze podataka
void closeDatabase(sqlite3* db) {
    // 1. param: sqlite3*
    int rc = sqlite3_close(db);
    if (rc != SQLITE_OK)
        throw string("Kod pri zatvaranju: ") + to_string(rc);
}

// Pripremanje upita
sqlite3_stmt* prepare(sqlite3* db, const char* query) {
    sqlite3_stmt *stmt = nullptr;
    int rc = sqlite3_prepare(db, query, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        string err = string("Greška pri pripremanju upita: ") + sqlite3_errmsg(db);
        sqlite3_finalize(stmt);
        throw err;
    }
    return stmt;
}

// 1. zadatak, prepare način
void printSelectQuery1(sqlite3* db, const char* query) {
    sqlite3_stmt* stmt = prepare(db, query);

    int rc = 0;

    // Za svaki red
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        for (int i = 0; i < sqlite3_column_count(stmt); i++) {
            switch (sqlite3_column_type(stmt, i)) {
                case SQLITE_INTEGER:
                    printf("%d\t", sqlite3_column_int(stmt, i));
                    break;
                case SQLITE_FLOAT:
                    printf("%f\t", sqlite3_column_double(stmt, i));
                    break;
                case SQLITE_TEXT:
                    // U realnosti sve radi sa sqlite3_column_text
                    printf("%s\t", sqlite3_column_text(stmt, i));
                    break;
            }
        }
        printf("\n");
    }
    printf("\n");

    // Kraj upita, provera greške
    if (rc != SQLITE_DONE) {
        string err = string("Greška prilikom ispisivanja: ") + sqlite3_errmsg(db);
        sqlite3_finalize(stmt);
        throw err;
    }

    // Svaki statement mora da se finalizuje
    sqlite3_finalize(stmt);
}

// Izvršavanje upita bez parametara
// Prima bazu, upit i pokazivač na callback funkciju
void executeNoParam(sqlite3* db, const char* query, int(*callback)(void*, int, char**, char**) = nullptr) {
    char *errMsg = nullptr;
    // Parametri:
    // 1. baza
    // 2. upit
    // 3. callback
    // 4. pokazivač prvi argument koji će se proslediti callback (ne koristimo)
    // 5. pokazivač na string gde će nam biti ispisana greška - mora se osloboditi
    int rc = sqlite3_exec(db, query, callback, nullptr, &errMsg);
    // Argumenti za callback:
    // 1. argument koji mi zadajemo proizvoljnog tipa (struktura)
    // 2. broj kolona - dužina sledećih nizova:
    // 3. niz rezultata upita u formi stringova
    // 4. niz imena kolona u formi stringova
    // Vraćanje ne-0 označava grešku

    if (rc != SQLITE_OK) {
        string err = string("Greška pri izvršavanju: ") + errMsg;
        sqlite3_free(errMsg); // Ne zaboraviti!
        throw err;
    }
    
}

// Callback funkcija
// Vraćanje ne-0 označava grešku i prekida upit
int printRows(void*, int colCount, char** rows, char**) {
    for (int i = 0; i < colCount; ++i) {
        if (rows[i] == nullptr) {
            cout << "null\t";
        }
        else {
            cout << rows[i] << "\t";
        }
    }
    cout << endl;
    return 0;
}

// 1. zadatak, exec način
void printSelectQuery2(sqlite3* db, const char* query) {
    executeNoParam(db, query, printRows);
}

// 2. zadatak
void addNewDriver(sqlite3* db, string name, int experience, string category) {
    try {
        // Begin transaction
        executeNoParam(db, "BEGIN TRANSACTION");

        // Insert into Zaposlen
        sqlite3_stmt* insertZaposlen = prepare(db, "INSERT INTO Zaposlen (ImePrezime, Staz) VALUES (?, ?)");
        sqlite3_bind_text(insertZaposlen, 1, name.c_str(), name.size(), SQLITE_STATIC);
        sqlite3_bind_int(insertZaposlen, 2, experience);
        if (sqlite3_step(insertZaposlen) != SQLITE_DONE) {
            string greska = string("Greška pri dodavanju zaposlenog: ") + sqlite3_errmsg(db);
            sqlite3_finalize(insertZaposlen);
            throw greska;
        }
        sqlite3_finalize(insertZaposlen);

        // Insert into Vozac
        sqlite3_stmt* insertVozac = prepare(db, "INSERT INTO Vozac (IDZap, Kategorija) VALUES (?, ?)");
        sqlite3_bind_int(insertVozac, 1, sqlite3_last_insert_rowid(db));
        sqlite3_bind_text(insertVozac, 2, category.c_str(), category.size(), SQLITE_STATIC);
        if (sqlite3_step(insertVozac) != SQLITE_DONE) {
            string greska = string("Greška pri dodavanju vozača: ") + sqlite3_errmsg(db);
            sqlite3_finalize(insertVozac);
            throw greska;
        }
        sqlite3_finalize(insertVozac);
        
        // Commit transaction
        executeNoParam(db, "COMMIT");
    } catch (string& err) {
        executeNoParam(db, "ROLLBACK");
        throw err;
    }
}

int main(void) {
    try {
        // Otvaramo bazu
        const char *uri = "KompanijaZaPrevoz.db";
        sqlite3 *db = openDatabase(uri);

        printSelectQuery1(db, "SELECT * FROM Zaposlen");

        // sqlite3_exec izvršava sve upite odvojene ; redom
        printSelectQuery2(db, "SELECT * FROM Mehanicar; SELECT * FROM Vozac");

        addNewDriver(db, "Stefan Tubić", 4, "A");

        printSelectQuery2(db, "SELECT * FROM Zaposlen; SELECT * FROM Vozac");

        // Zatvaramo bazu
        closeDatabase(db);
    }
    catch (string& errMsg) {
        // Ispisujemo izuzetak tipa string
        cout << errMsg << endl;
    }
    return 0;
}
