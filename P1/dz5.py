from typing import List
from operator import attrgetter

class Student:
    """Klasa koja predstavlja jednog studenta čije se informacije čitaju iz datoteke.
    
    Sva logika parsiranja se nalazi ovde.
    """
    godina: int
    indeks: int
    ime: str
    prezime: str
    profil: str
    jezik_na_p1: str
    jezik_na_pp1: str

    def __init__(self, linija: str):
        """Izvlači informacije o studentu iz reda u datoteci.
        
        :param str linija: red iz datoteke
        """
        podeljeno = [deo.strip() for deo in linija.split(';')]
        if len(podeljeno) == 7:
            podeljeno.append('')
        godina, indeks, ime, prezime, profil, jezik_na_p1, sluša_pp1, jezik_na_pp1 = podeljeno
        self.godina = int(godina)
        self.indeks = int(indeks)
        self.ime = ime
        self.prezime = prezime
        self.profil = profil
        self.jezik_na_p1 = self.formatiraj_jezik('DA', jezik_na_p1)
        self.jezik_na_pp1 = self.formatiraj_jezik(sluša_pp1, jezik_na_pp1)

    def __str__(self) -> str:
        """Vraća kako bi student trebalo da bude zapisan u redu CSV datoteke.
        
        :return: red iz CSV datoteke
        :rtype: str
        """
        if self.profil == 'OO':
            return '"{:04d}/{:02d}","{} {}","{}"\n'.format(self.indeks, self.godina - 2000, self.ime, self.prezime, self.jezik_na_pp1)
        else:
            return '"{:04d}/{:04d}","{} {}","{}"\n'.format(self.godina, self.indeks, self.prezime, self.ime, self.jezik_na_p1)

    def formatiraj_jezik(self, sluša: str, jezik: str) -> str:
        """Formatira programski jezik na način propisan zadatkom.
        
        Ako student ne sluša predmet, vraća "ne sluša". Ako je jezik Python vraća
        "Py", a u suprotnom "Pas".
        :param str sluša: da li student sluša jezik
        :param str jezik: koji jezik student sluša
        :return: jezik formatiran na traženi način
        :rtype: str
        """
        if sluša == 'DA':
            if jezik == 'Pascal':
                return 'PAS'
            else:
                return 'Py'
        else:
            return 'ne sluša'

class Domaći:
    """Peti domaći iz Praktikuma iz Programiranja 1.
    
    Student Luka Simić, broj indeksa 2019/0368.
    """
    studenti: List[Student] = []

    def reši(self) -> None:
        """Vrši čitanje, obradu i pisanje podataka predviđenim zadatkom."""
        unos = input().strip()
        while unos != '':
            with open(unos, 'r', encoding='utf-8') as datoteka:
                studenti = [Student(linija) for linija in datoteka.readlines() if linija.strip() != '']
            studenti.sort(key=attrgetter('jezik_na_p1', 'prezime', 'ime'))
            self.upiši(studenti, 'OO')
            self.upiši(studenti, 'SI')
            unos = input().strip()

    def upiši(self, studenti: List[Student], profil: str) -> None:
        """Upisuje studente jednog odseka u traženu CSV datoteku.
        
        :param list studenti: studenti svih odseka
        :param str profil: profil studenata koji bi trebalo da budu upisani u datoteku
        """
        with open('{}.csv'.format(profil), 'w', encoding='utf-8') as fajl:
            fajl.writelines([str(student) for student in studenti if student.profil == profil])

if __name__ == '__main__':
    domaći = Domaći()
    domaći.reši()
