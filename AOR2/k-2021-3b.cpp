void prefetch(void* addr);

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

Student* pronadjiStudentaPoIndeksu(Student** list, int n, const char gggg[], const char bbbb[]) {
    // Дохватање броја индекса и године првог студента.
    if (n != 0)
        prefetch(&(list[0]->id));
    for (int i = 0; i < n; i++) {
        // Дохватање статуса активности тренутног студента.
        prefetch(&(list[i]->prosek));
        bool indeks_ok = true;
        for (int j = 0; j < 4 && indeks_ok; j++)
            indeks_ok &= list[i]->gggg[j] == gggg[j];
        // Дохватање броја индекса и године следећег студента.
        if (i != n - 1)
            prefetch(&(list[i + 1]->id));
        for (int j = 0; j < 4 && indeks_ok; j++)
            indeks_ok &= list[i]->bbbb[j] == bbbb[j];
        if (indeks_ok && list[i]->isActive)
            return list[i];
    }
    return 0;
}

void procitajStudente(Student** studenti, int* n);

int main() {
    int n;
    Student** studenti;
    procitajStudente(studenti, &n);
    // ...
    Student* s = pronadjiStudentaPoIndeksu(studenti, n, "2000", "0001");
    // ...
    return 0;
}
