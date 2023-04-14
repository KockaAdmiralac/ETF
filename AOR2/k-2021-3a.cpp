struct StudentMisc {
    int id;
    int jmbg;
    char pol;
    char* Ime;
    char* Prezime;
    int godinaStudija;
    float prosek;
    char polozenoIspita;
    char nivoStudija;
};

// Укупно: један студент = 1 блок кеша
struct Student {
    // 4B
    char gggg[4];
    // 4B
    char bbbb[4];
    // 1B
    bool isActive;
    // 3B padding овде
    // 4B
    StudentMisc* misc;
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
