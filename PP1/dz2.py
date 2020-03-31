from typing import List
import math

# 1. Da li se u modifikaciji ispisuje i rezultat osnovne obrade?
# 2. Šta znači lokalni maksimum/minimum?
# 3. Da li sme da se koristi ovakav kod?
# 4. Da li su "pozicije elemenata" indeksirane od 0 ili od 1?

class Domaći:
    """Drugi domaći zadatak iz Programiranja 1.

    Student Luka Simić, 19/0368, branjen 27. 11. 2019.
    """
    lista: List[int] = []

    def uradi(self) -> None:
        """Izvršava unos, obradu i ispis u petlji dok se ne unese unos koji
        nije validan.
        """
        while self.unos():
            ispis1 = self.osnovni()
            ispis2 = self.modifikacija()
            self.ispis(ispis1)
            self.ispis(ispis2, True)

    def unos(self) -> bool:
        """Učitava dužinu a zatim i elemente niza.

        :return: da li je unos validan
        :rtype: bool
        """
        try:
            dužina = int(input("Unesi dužinu liste: "))
            if dužina < 1:
                return False
            self.lista = []
            for i in range(dužina):
                unos = int(input("Unesi element liste: "))
                if unos < 1:
                    return False
                self.lista.append(unos)
            return True
        except ValueError:
            return False

    def osnovni(self) -> List[int]:
        """Vrši osnovnu funkcionalnost domaćeg zadatka.

        Pronalazi i ispisuje pozicije elemenata liste pozitivnih celih brojeva
        koji su deljivi brojem 13.

        :return: unesena lista nakon obrade
        :rtype: list
        """
        return [i for i in range(len(self.lista)) if self.deljiv(self.lista[i])]

    def deljiv(self, broj: int) -> bool:
        """Proverava da li je broj deljiv sa 13.

        Po uslovima zadatka, provera se radi tako što se cifre broja čitaju u
        trojkama otpozadi, i ako je razlika trojki deljiva sa 13 ceo broj je
        deljiv sa 13.

        :param int broj: broj kojem se proverava deljivost
        :return: da li je broj deljiv sa 13
        :rtype: bool
        """
        niska = str(broj)
        dužina = len(niska)
        broj_trocifri = math.ceil(dužina / 3)
        trocifre = [int(niska[max(0, dužina - (x + 1)*3):dužina - x*3]) for x in range(broj_trocifri)]
        suma = sum([((i % 2 == 0) and 1 or -1) * trocifre[i] for i in range(broj_trocifri)])
        return suma % 13 == 0

    def modifikacija(self) -> List[int]:
        """Vrši dodatnu obradu zadatih podataka.

        Za implementirati u datoteci za modifikaciju.
        :return: obrađena lista za ispis
        :rtype: list
        """
        return []

    def ispis(self, lista: List[int], ispiši_dužinu: bool = False) -> None:
        """Ispisuje sve elemente liste odvojene zarezima ukoliko lista nije
        prazna.

        :param list lista: lista koja se ispisuje
        """
        if (len(lista) > 0):
            print(', '.join([str(element) for element in lista]))


if __name__ == '__main__':
    domaći = Domaći()
    domaći.uradi()
