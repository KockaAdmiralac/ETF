from dz3 import Domaći, Matrica

class DomaćiModifikacija(Domaći):
    """Modifikacija trećeg domaćeg zadatka iz Praktikuma iz Programiranja 1.

    Student Luka Simić, 19/0368, branjena 11. 12. 2019.
    """
    def transponovanje(self, unos: Matrica) -> Matrica:
        """Transponuje unesenu matricu.
        
        :return: transponovana matrica
        :rtype: list
        """
        if len(unos) == 0 or len(unos[0]) == 0:
            return []
        return [[unos[y][x] for y in range(len(unos))] for x in range(len(unos[0]))]

if __name__ == '__main__':
    domaći = DomaćiModifikacija()
    domaći.reši()
