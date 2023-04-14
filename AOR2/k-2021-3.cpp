struct Student {
    // B0: 4B
    int id;
    // B0: 4B
    int jmbg;
    // B0: 4B
    char gggg[4];
    // B0: 4B
    char bbbb[4];
    // B1: 1B
    char pol;
    // B1: 3B padding
    // B1: 4B
    char* Ime;
    // B1: 4B
    char* Prezime;
    // B1: 4B
    int godinaStudija;
    // B2: 4B
    float prosek;
    // B2: 1B
    bool isActive;
    // B2: 3B padding
    // B2: 1B
    char polozenoIspita;
    // B2: 3B padding
    // B2: 1B
    char nivoStudija;
    // B2: 3B padding
};

void procitajStudente(Student** studenti, int* n);

Student* pronadjiStudentaPoIndeksu(Student** list, int n, const char gggg[], const char bbbb[]) {
    for (int i = 0; i < n; i++) {
        bool indeks_ok = true;
        for (int j = 0; j < 4 && indeks_ok; j++)
            indeks_ok = indeks_ok && list[i]->gggg[j] == gggg[j];
        for (int j = 0; j < 4 && indeks_ok; j++)
            indeks_ok = indeks_ok && list[i]->bbbb[j] == bbbb[j];
        if (indeks_ok && list[i]->isActive)
            return list[i];
    }
    return 0;
}

int main() {
    int n;
    Student** studenti;
    procitajStudente(studenti, &n);
    // ...
    Student* s = pronadjiStudentaPoIndeksu(studenti, n, "2000", "0001");
    // ...
    return 0;
}
