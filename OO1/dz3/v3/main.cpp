#include <iostream>
#include "igrac.hpp"
#include "tim.hpp"
#include "privilegovani.hpp"
#include "par.hpp"
#include "mec.hpp"

int main(void) {
    std::cout << "==================== Igrač ===================" << std::endl;
    Igrac i1("Pera"), i2("Žika", 2000);
    std::cout << "Dohvatanje imena (Pera): " << i1.dohvatiIme() << std::endl
              << "Dohvatanje podrazumevane vrednosti (1000): " << i1.dohvatiVrednost() << std::endl
              << "Dohvatanje nepodrazumevane vrednost (2000): " << i2.dohvatiVrednost() << std::endl;
    i1.promeniVrednost(10);
    Igrac i3("Pera", 1100);
    std::cout << "Promena vrednosti za 10% (1100): " << i1.dohvatiVrednost() << std::endl
              << "Jednakost igrača: " << (i1 == i3) << std::endl
              << "Nejednakost igrača: " << (i1 == i2) << std::endl
              << "Ispis igrača (Pera#1100): " << i1 << std::endl;

    std::cout << "===================== Tim ====================" << std::endl;
    Tim tim1("Perin tim", 2), tim2("Takođe Perin tim", 1), tim3("Perin tim", 2);
    std::cout << "Tim bez igrača: " << tim1.dohvatiBrojIgraca() << std::endl;
    tim1.prikljuci(i1, 0);
    tim3.prikljuci(i1, 0);
    std::cout << "Tim s jednim igračom: " << tim1.dohvatiBrojIgraca() << std::endl
              << "Vrednost tima (1100): " << tim1.dohvatiVrednostTima() << std::endl
              << "Dohvatanje člana (Pera#1100): " << (*tim1[0]) << std::endl
              << "Jednakost tima: " << (tim1 == tim3) << std::endl
              << "Nejednakost tima: " << (tim1 == tim2) << std::endl;
    tim1.prikljuci(i2, 1);
    std::cout << "Prosečna vrednost tima (1550): " << tim1.dohvatiVrednostTima() << std::endl;
    tim1 = tim3;
    std::cout << "Ispis dodeljenog tima (Perin tim [Pera#1100]): " << tim1 << std::endl;

    std::cout << "============= Privilegovani tim ==============" << std::endl;
    PrivilegovaniTim priv("Žikin tim", 1, 1500);
    priv.prikljuci(i2, 0);
    try {
        priv.prikljuci(i1, 1);
        std::cout << "Nije se desila greška!" << std::endl;
    } catch (std::exception &greska) {
        std::cout << "Greška jer igrač nije dovoljno vredan: " << greska.what() << std::endl;
    }
    std::cout << "Ispis privilegovanog tima (Žikin tim (1500) [Žika#2000]): " << priv << std::endl;

    std::cout << "=================== Par ======================" << std::endl;
    int a = 1, b = 2, c = 1;
    Par<int> par1(&a, &b), par2(&b, &c), par3(&c, &b);
    std::cout << "Jednakost parova: " << (par1 == par3) << std::endl
              << "Nejednakost parova: " << (par1 == par2) << std::endl
              << "Prvi član para (1): " << (*par1.dohvatiPrvi()) << std::endl
              << "Drugi član para (2): " << (*par1.dohvatiDrugi()) << std::endl
              << "Ispis para ([1 - 2]): " << par1 << std::endl;
    par1.postaviPrvi(&b);
    par1.postaviDrugi(&a);
    std::cout << "Ispis postavljenog para ([2 - 1]): " << par1 << std::endl;

    std::cout << "=================== Meč ======================" << std::endl;
    Mec mec1(tim1, tim2), mec2(tim1, tim1);
    std::cout << "Neodigrani meč: " << mec1.jeOdigran() << std::endl
              << "Dohvatanje timova ([Perin tim [Pera#1100] - Takođe Perin tim []]): " << mec1.dohvatiTimove() << std::endl
              << "Ispis neodigranog meča ([Perin tim [Pera#1100] - Takođe Perin tim []], ishod: neodigrano): " << mec1 << std::endl;
    try {
        mec1.poeni();
        std::cout << "Nije se desila greška!" << std::endl;
    } catch (std::exception &greska) {
        std::cout << "Greška prilikom dohvatanja poena dok meč nije odigran: " << greska.what() << std::endl;
    }
    mec1.odigraj();
    mec2.odigraj();
    Par<int> poeni1 = mec1.poeni(), poeni2 = mec2.poeni();
    std::cout << "Odigrani meč: " << mec1.jeOdigran() << std::endl
              << "Poeni kad domaćin pobedi ([3 - 0]): " << poeni1 << std::endl
              << "Poeni kad je nerešeno ([1 - 1]): " << poeni2 << std::endl
              << "Ispis odigranog meča: ([Perin tim [Pera#1210] - Takođe Perin tim []], ishod: domaćin je pobedio): " << mec1 << std::endl;
    delete poeni1.dohvatiPrvi();
    delete poeni1.dohvatiDrugi();
    delete poeni2.dohvatiPrvi();
    delete poeni2.dohvatiDrugi();
    return 0;
}
