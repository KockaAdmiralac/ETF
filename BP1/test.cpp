#include <iostream>
#include "sqlite3.h"

sqlite3 *otvoriBazu(const char *imeBaze) {
    sqlite3 *baza = nullptr;
    int kod = sqlite3_open(imeBaze, &baza);
    if (kod != SQLITE_OK) {
        throw std::string("Kod pri otvaranju: ") + std::to_string(kod);
    }
    return baza;
}

void zatvoriBazu(sqlite3 *baza) {
    int kod = sqlite3_close(baza);
    if (kod != SQLITE_OK) {
        throw std::string("Kod pri zatvaranju: ") + std::to_string(kod);
    }
}

void pripremi(sqlite3 *baza, const char *sql, sqlite3_stmt *&stmt) {
    int kod = sqlite3_prepare(baza, sql, -1, &stmt, nullptr);
    if (kod != SQLITE_OK) {
        sqlite3_finalize(stmt);
        throw std::string("Greška pri pripremanju upita: ") + sqlite3_errmsg(baza);
    }
}

void izvrsiBezParametara(sqlite3 *baza, const char *sql, int (*callback)(void *, int, char **, char **)=nullptr) {
    char *errmsg = nullptr;
    int kod = sqlite3_exec(baza, sql, callback, nullptr, &errmsg);
    if (kod != SQLITE_OK) {
        sqlite3_free(errmsg);
        throw std::string("Greška pri izvršavanju: ") + errmsg;
    }
}

int ispisSvega(void *, int colCount, char **rows, char **) {
    for (int i = 0; i < colCount; ++i) {
        if (rows[i] == nullptr) {
            std::cout << "null\t";
        } else {
            std::cout << rows[i] << "\t";
        }
    }
    std::cout << std::endl;
    return 0;
}

void sveStavke(sqlite3 *baza) {
    std::cout << "IdSta\tRedBroj\tDatum\t\tVreme\tIznos\tIdFil\tIdRac" << std::endl;
    izvrsiBezParametara(baza, "SELECT * FROM Stavka", ispisSvega);
}

void sveUplate(sqlite3 *baza) {
    std::cout << "IdSta\tOsnov" << std::endl;
    izvrsiBezParametara(baza, "SELECT * FROM Uplata", ispisSvega);
}

void sviRacuniKomitenta(sqlite3 *baza, int idKom) {
    const char *sql = "SELECT IdRac, Status, BrojStavki, DozvMinus, Stanje, IdFil, IdKom "
                      "FROM Racun "
                      "WHERE IdKom = ?";
    sqlite3_stmt *stmt = nullptr;
    int kod;
    pripremi(baza, sql, stmt);
    sqlite3_bind_int(stmt, 1, idKom);
    std::cout << "IdRac\tStatus\tBrojStavki\tDozvMinus\tStanje\tIdFil\tIdKom" << std::endl;
    while ((kod = sqlite3_step(stmt)) == SQLITE_ROW) {
        for (int i = 0; i < 7; ++i) {
            const unsigned char *red = sqlite3_column_text(stmt, i);
            if (red == nullptr) {
                std::cout << "null" << "\t";
            } else {
                std::cout << red << "\t";
            }
        }
        std::cout << std::endl;
    }
    if (kod != SQLITE_DONE) {
        const char *err = sqlite3_errmsg(baza);
        sqlite3_finalize(stmt);
        throw std::string("Greška prilikom ispisivanja računa: ") + err;
    }
    sqlite3_finalize(stmt);
}

void proknjiziStavku(sqlite3 *baza, int iznos, int idFil, int idRac) {
    const char *sql = "INSERT INTO Stavka (RedBroj, Datum, Vreme, Iznos, IdFil, IdRac) "
                      "SELECT MAX(S.RedBroj), DATE(), TIME(), ?, ?, ? "
                      "FROM Stavka S "
                      "WHERE S.IdRac = ?";
    sqlite3_stmt *stmt = nullptr;
    int kod;
    pripremi(baza, sql, stmt);
    sqlite3_bind_int(stmt, 1, iznos);
    sqlite3_bind_int(stmt, 2, idFil);
    sqlite3_bind_int(stmt, 3, idRac);
    sqlite3_bind_int(stmt, 4, idRac);
    kod = sqlite3_step(stmt);
    if (kod != SQLITE_DONE) {
        const char *err = sqlite3_errmsg(baza);
        sqlite3_finalize(stmt);
        throw std::string("Greška pri proknjižavanju stavke: ") + err;
    }
    sqlite3_finalize(stmt);
}

void proknjiziUplatu(sqlite3 *baza, int idFil, int idRac) {
    const char *sql = "INSERT INTO Uplata (IdSta, Osnov) "
                      "SELECT MAX(S.IdSta), 'Uplata' "
                      "FROM Stavka S "
                      "WHERE S.IdFil = ? AND S.IdRac = ?";
    sqlite3_stmt *stmt = nullptr;
    int kod;
    pripremi(baza, sql, stmt);
    sqlite3_bind_int(stmt, 1, idFil);
    sqlite3_bind_int(stmt, 2, idRac);
    kod = sqlite3_step(stmt);
    if (kod != SQLITE_DONE) {
        const char *err = sqlite3_errmsg(baza);
        sqlite3_finalize(stmt);
        throw std::string("Greška pri proknjižavanju uplate: ") + err;
    }
    sqlite3_finalize(stmt);
}

void azurirajRacun(sqlite3 *baza, int idRac) {
    const char *sql = "UPDATE Racun "
                      "SET Status = (CASE "
                                       "WHEN 'B' THEN 'A' "
                                       "ELSE Status "
                                    "END),"
                          "BrojStavki = (SELECT MAX(IdSta) FROM Stavka WHERE IdRac = ?),"
                          "Stanje = 0 "
                      "WHERE IdRac = ?";
    sqlite3_stmt *stmt = nullptr;
    int kod;
    pripremi(baza, sql, stmt);
    sqlite3_bind_int(stmt, 1, idRac);
    sqlite3_bind_int(stmt, 2, idRac);
    kod = sqlite3_step(stmt);
    if (kod != SQLITE_DONE) {
        const char *err = sqlite3_errmsg(baza);
        sqlite3_finalize(stmt);
        throw std::string("Greška pri ažuriranju računa: ") + err;
    }
    sqlite3_finalize(stmt);
}

void resi(int idKom, int idFil, sqlite3 *baza) {
    const char *sql = "SELECT IdRac, Stanje "
                      "FROM Racun "
                      "WHERE IdKom = ? AND Stanje < 0";
    sqlite3_stmt *stmt = nullptr;
    int kod;
    pripremi(baza, sql, stmt);
    sqlite3_bind_int(stmt, 1, idKom);
    while ((kod = sqlite3_step(stmt)) == SQLITE_ROW) {
        izvrsiBezParametara(baza, "BEGIN TRANSACTION");
        try {
            int idRac = sqlite3_column_int(stmt, 0);
            int stanje = sqlite3_column_int(stmt, 1);
            proknjiziStavku(baza, -stanje, idFil, idRac);
            proknjiziUplatu(baza, idFil, idRac);
            azurirajRacun(baza, idRac);
            izvrsiBezParametara(baza, "COMMIT");
        } catch (std::string &greska) {
            izvrsiBezParametara(baza, "ROLLBACK");
            sqlite3_finalize(stmt);
            throw;
        }
    }
    if (kod != SQLITE_DONE) {
        const char *err = sqlite3_errmsg(baza);
        sqlite3_finalize(stmt);
        throw std::string("Greška pri dohvatanju računa komitenta: ") + err;
    }
    sqlite3_finalize(stmt);
}

void ispisiStanje(int idKom, sqlite3 *baza) {
    sveStavke(baza);
    std::cout << std::endl;
    sveUplate(baza);
    std::cout << std::endl;
    sviRacuniKomitenta(baza, idKom);
    std::cout << std::endl;
}

int main(void) {
    try {
        sqlite3 *baza = otvoriBazu("Banka.db");
        int idKom, idFil;
        std::cout << "Unesi ID komitenta: ";
        std::cin >> idKom;
        std::cout << "Unesi ID filijale: ";
        std::cin >> idFil;
        std::cout << "Trenutno stanje:" << std::endl;
        ispisiStanje(idKom, baza);
        resi(idKom, idFil, baza);
        std::cout << "Novo stanje:" << std::endl;
        ispisiStanje(idKom, baza);
        zatvoriBazu(baza);
    } catch (std::string &greska) {
        std::cout << "Desila se greška." << std::endl << greska << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
