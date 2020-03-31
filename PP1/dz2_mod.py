from dz2 import Domaći
from typing import List

class DomaćiModifikacija(Domaći):
    """Modifikacija drugog domaćeg zadatka iz Programiranja 1.

    Student Luka Simić, 19/0368, branjena 27. 11. 2019.
    """
    def modifikacija(self) -> List[int]:
        """Vrši dodatnu obradu zadatih podataka.

        Za implementirati u datoteci za modifikaciju.
        :return: obrađena lista za ispis
        :rtype: list
        """
        maksimalno = max(self.lista)
        minimalno = min(self.lista)
        return [element for element in self.lista if element != maksimalno and element != minimalno]

    def ispis(self, lista: List[int], ispiši_dužinu: bool = False) -> None:
        """Ispisuje sve elemente liste odvojene zarezima ukoliko lista nije
        prazna.

        :param list lista: lista koja se ispisuje
        """
        if ispiši_dužinu:
            print(len(lista))
        super().ispis(lista, ispiši_dužinu)

if __name__ == '__main__':
    domaći = DomaćiModifikacija()
    domaći.uradi()
