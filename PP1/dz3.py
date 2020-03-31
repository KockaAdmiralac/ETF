from typing import List, Tuple

Matrica = List[List[int]]
PozicijaVrednost = Tuple[int, int]

class Domaći():
    """Treći domaći zadatak iz Praktikuma iz Programiranja 1.

    Student Luka Simić, 19/0368, branjen 11. 12. 2019.
    """
    def reši(self) -> None:
        """Izvršava unos, obradu i ispis u petlji dok god je unos validan."""
        unos, validno = self.unos()
        while validno:
            unos = self.transponovanje(unos)
            prvi_niz, drugi_niz = self.obrada(unos)
            self.ispis(prvi_niz)
            self.ispis(drugi_niz)
            unos, validno = self.unos()

    def unos_reda(self) -> List[int]:
        """Vrši unos jednog reda matrice.

        :return: uneseni red matrice
        :rtype: list"""
        return [int(broj) for broj in input().split(' ')]

    def unos(self) -> Tuple[Matrica, bool]:
        """Vrši unos dimenzija matrice i cele matrice, kao i proveru validnosti
        unosa.

        :return: unesena matrica i da li je unos validan
        :rtype: tuple
        """
        try:
            x, y = self.unos_reda()
            if x < 0 or y < 0:
                return ([], False)
            elif x == 0 or y == 0:
                return ([], True)
            else:
                return ([self.unos_reda() for i in range(y)], True)
        except ValueError:
            return ([], False)

    def transponovanje(self, unos: Matrica) -> Matrica:
        """Transponuje unesenu matricu.

        Za implementirati u modifikaciji.

        :return: unesena matrica
        :rtype: list
        """
        return unos

    def maksimum_sa_pozicijom(self, niz: List) -> PozicijaVrednost:
        """Pronalazi poziciju i vrednost maksimalnog člana niza.

        :param list niz: niz čiji se maksimalni član proverava
        :return: pozicija i vrednost maksimalnog člana niza
        :rtype: tuple
        """
        maksimum = niz[0]
        pozicija = 0
        for i in range(1, len(niz)):
            if niz[i] > maksimum:
                maksimum = niz[i]
                pozicija = i
        return (pozicija, maksimum)

    def obrada(self, unos: Matrica) -> Tuple[List[PozicijaVrednost], List[PozicijaVrednost]]:
        """Vrši obradu definisanu zadatkom.

        Formira dva niza elemenata na osnovu zadate matrice celih brojeva;
        prvi niz sadrži pozicije i vrednosti maksimalnih elemenata po vrstama
        matrice, dok drugi niz sadrži pozicije i vrednosti minimalnih elemenata
        po kolonama matrice.

        :param list unos: unesena matrica
        :return: obrađena matrica
        :rtype: list
        """
        if len(unos) == 0 or len(unos[0]) == 0:
            return ([], [])
        prvi_niz = [self.maksimum_sa_pozicijom(niz) for niz in unos]
        drugi_niz = [
            self.maksimum_sa_pozicijom([unos[x][y] for x in range(len(unos))])
            for y in range(len(unos[0]))
        ]
        return (prvi_niz, drugi_niz)

    def ispis(self, niz: List[PozicijaVrednost]) -> None:
        """Ispisuje niz.

        :param list niz: niz za ispis
        """
        if len(niz) > 0:
            print(', '.join([str(x) for x in niz]))

if __name__ == '__main__':
    domaći = Domaći()
    domaći.reši()
