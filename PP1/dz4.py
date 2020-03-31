from enum import IntEnum
from typing import List

LOGIČKI_OPERATORI = {'&', '|'}
OPERATORI_POREĐENJA = {'>', '<', '='}

class TipTokena(IntEnum):
    """Mogući tipovi tokena u izrazu."""
    BROJ = 1
    OPERATOR_POREĐENJA = 2
    LOGIČKI_OPERATOR = 3

class Token:
    """Struktura koja predstavlja jedan token izraza koji parsiramo."""
    tip: TipTokena

    def __init__(self, tip: TipTokena, sadržaj):
        self.tip = tip
        self.sadržaj = sadržaj

TokenList = List[Token]

class Domaći:
    """Četvrti domaći zadatak iz Praktikuma iz Programiranja 1.

    Student Luka Simić, 19/0368, branjen 18. 12. 2019.
    """
    def reši(self) -> None:
        """Vrši unos i parsiranje izraza i rezultat njegove evaluacije."""
        izraz = input().strip()
        while izraz != '':
            tokeni: TokenList = []
            pozicija = self.čitaj_broj(izraz, 0, tokeni)
            while pozicija != len(izraz):
                pozicija = self.čitaj_prazno(izraz, pozicija)
                pozicija = self.čitaj_operator(izraz, pozicija, tokeni)
                pozicija = self.čitaj_prazno(izraz, pozicija)
                pozicija = self.čitaj_broj(izraz, pozicija, tokeni)
            print(str(self.evaluiraj(tokeni)).lower())
            izraz = input().strip()

    def čitaj_prazno(self, izraz: str, pozicija: int) -> int:
        """Nastavlja parsiranje izraza do sledećeg ne-razmaka.
        
        :param str izraz: izraz koji se parsira
        :param str pozicija: pozicija trenutnog parsiranja
        :return: pozicija parsiranja nakon kraja čitanja razmaka
        :rtype: int
        """
        while pozicija != len(izraz) and izraz[pozicija] == ' ':
            pozicija += 1
        return pozicija

    def čitaj_broj(self, izraz: str, pozicija: int, tokeni: TokenList) -> int:
        """Čita jedan broj iz izraza.

        :param str izraz: izraz koji se parsira
        :param str pozicija: pozicija trenutnog parsiranja
        :param list tokeni: trenutno parsirani tokeni
        :return: pozicija parsiranja nakon kraja čitanja broja
        :rtype: int
        """
        cifre: List[str] = []
        while pozicija != len(izraz) and izraz[pozicija].isdigit():
            cifre.append(izraz[pozicija])
            pozicija += 1
        tokeni.append(Token(TipTokena.BROJ, int(''.join(cifre))))
        return pozicija

    def čitaj_operator(self, izraz: str, pozicija: int, tokeni: TokenList) -> int:
        """Čita jedan logički operator ili operator poređenja iz izraza.
        
        :param str izraz: izraz koji se parsira
        :param str pozicija: pozicija trenutnog parsiranja
        :param list tokeni: trenutno parsirani tokeni
        :return: pozicija parsiranja nakon kraja čitanja operatora
        :rtype: int
        """
        operator: List[str] = []
        tip = TipTokena.OPERATOR_POREĐENJA
        while pozicija != len(izraz):
            if izraz[pozicija] in LOGIČKI_OPERATORI:
                tip = TipTokena.LOGIČKI_OPERATOR
                operator.append(izraz[pozicija])
                pozicija += 1
            elif izraz[pozicija] in OPERATORI_POREĐENJA:
                operator.append(izraz[pozicija])
                pozicija += 1
            else:
                break
        tokeni.append(Token(tip, ''.join(operator)))
        return pozicija

    def evaluiraj(self, tokeni: TokenList) -> bool:
        """Evaluira izraz u vidu parsiranih tokena.
        
        :param list tokeni: niz parsiranih tokena koji predstavljaju izraz
        :return: istinitosna vrednost izraza
        :rtype: bool
        """
        vrednosti: List[bool] = []
        operatori: List[str] = []
        prošlo_poređenje = False
        for indeks, token in enumerate(tokeni):
            if token.tip == TipTokena.OPERATOR_POREĐENJA:
                ovo_poređenje = self.evaluiraj_poređenje(tokeni[indeks - 1], tokeni[indeks + 1], token)
                if prošlo_poređenje:
                    vrednosti[-1] = vrednosti[-1] and ovo_poređenje
                else:
                    vrednosti.append(ovo_poređenje)
            elif token.tip == TipTokena.LOGIČKI_OPERATOR:
                operatori.append(token.sadržaj)
        levi_operand = vrednosti[0]
        for indeks, operator in enumerate(operatori):
            desni_operand = vrednosti[indeks + 1]
            levi_operand = self.evaluiraj_logički(levi_operand, desni_operand, operator)
        return levi_operand

    def evaluiraj_poređenje(self, prvi_operand: Token, drugi_operand: Token, operacija: Token) -> bool:
        """Poredi dva broja u vidu tokena.
        
        :param Token prvi_operand: operand levo od operatora poređenja
        :param Token drugi_operand: operand desno od operatora poređenja
        :param Token operacija: operator poređenja
        :return: istinitosna vrednost poređenja
        :rtype: bool
        """
        if operacija.sadržaj == '<':
            return prvi_operand.sadržaj < drugi_operand.sadržaj
        elif operacija.sadržaj == '>':
            return prvi_operand.sadržaj > drugi_operand.sadržaj
        elif operacija.sadržaj == '==':
            return prvi_operand.sadržaj == drugi_operand.sadržaj
        else:
            # wtf
            return False

    def evaluiraj_logički(self, prvi_operand: bool, drugi_operand: bool, operacija: str) -> bool:
        """"Poredi dva logička izraza.
        
        :param bool prvi_operand: operand levo od operatora poređenja
        :param bool drugi_operand: operand desno od operatora poređenja
        :param str operacija: operator poređenja
        :return: istinitosna vrednost poređenja
        :rtype: bool
        """
        if operacija == '&&':
            return prvi_operand and drugi_operand
        elif operacija == '||':
            return prvi_operand or drugi_operand
        else:
            # wtf
            return False

if __name__ == '__main__':
    domaći = Domaći()
    domaći.reši()
