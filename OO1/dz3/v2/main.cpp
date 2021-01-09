#include <iostream>
#include "nut.hpp"
#include "namirnica.hpp"
#include "sastojak.hpp"
#include "lista.hpp"

int main(void) {
    std::cout << "============ Nutritivna vrednost =============" << std::endl;
    NutritivnaVrednost nv1(1, 2, 3), nv2(2, 3, 4);
    std::cout << "Dohvatanje ugljenih hidrata (1): " << nv1.dohvatiUgljeneHidrate() << std::endl
              << "Dohvatanje masti (2): " << nv1.dohvatiMasti() << std::endl
              << "Dohvatanje proteina (3): " << nv1.dohvatiProteine() << std::endl
              << "Dohvatanje broja kalorija (34): " << nv1.brojKalorija() << std::endl
              << "Zbir i ispis nutritivnih vrednosti ([uh: 3, ma: 5, pr: 7]): " << nv1 + nv2 << std::endl;

    std::cout << "================ Namirnica ===================" << std::endl;
    Namirnica n1("Šećer", nv1, true), n2("Mleko", nv2, false), n3("Šećer", nv2, false);
    std::cout << "Dohvatanje naziva (Šećer): " << n1.dohvatiNaziv() << std::endl
              << "Dohvatanje nutritivne vrednosti ([uh: 1, ma: 2, pr: 3]): " << n1.dohvatiNutritivnuVrednost() << std::endl
              << "Jeste posna: " << n1.jePosna() << std::endl
              << "Nije posna: " << n2.jePosna() << std::endl
              << "Jednakost namirnica: " << (n1 == n3) << std::endl
              << "Nejednakost namirnica: " << (n1 == n2) << std::endl
              << "Ispis namirnice (Šećer - [uh: 1, ma: 2, pr: 3]): " << n1 << std::endl;

    std::cout << "================== Sastojak ==================" << std::endl;
    Sastojak s1(n1, 200), s2(n2, 300);
    std::cout << "Dohvatanje namirnice (Šećer - [uh: 1, ma: 2, pr: 3]): " << s1.dohvatiNamirnicu() << std::endl
              << "Dohvatanje količine (200): " << s1.dohvatiKolicinu() << std::endl
              << "Nutritivna vrednost ([uh: 2, ma: 4, pr: 6]): " << s1.nutritivnaVrednost() << std::endl
              << "Broj kalorija (68): " << s1.brojKalorija() << std::endl
              << "Ispis sastojka ([0.068kcal] 200g x Šećer - [uh: 1, ma: 2, pr: 3]): " << s1 << std::endl;
    
    std::cout << "=================== Lista ====================" << std::endl;
    Lista<Sastojak *> lista;
    lista.dodaj(&s1);
    lista.dodaj(&s2);
    std::cout << "Tekući ([0.068kcal] 200g x Šećer - [uh: 1, ma: 2, pr: 3]): " << (*lista.dohvatiTekuci()) << std::endl
              << "Tekući postoji: " << lista.postojiTekuci() << std::endl;
    lista.naSledeci();
    std::cout << "Sledeći ([0.153kcal] 300g x Mleko - [uh: 2, ma: 3, pr: 4]): " << (*lista.dohvatiTekuci()) << std::endl;
    lista.naSledeci();
    std::cout << "Tekući ne postoji: " << lista.postojiTekuci() << std::endl;
    try {
        lista.dohvatiTekuci();
        std::cout << "Nije se desila greška!" << std::endl;
    } catch (std::exception &greska) {
        std::cout << "Greška prilikom dohvatanja tekućeg (tekući ne postoji): " << greska.what() << std::endl;
    }
    lista.naPrvi();
    std::cout << "Vraćeno na prvi element ([0.068kcal] 200g x Šećer - [uh: 1, ma: 2, pr: 3]): " << (*lista.dohvatiTekuci()) << std::endl;
    lista.isprazni();
    std::cout << "Prazna lista, tekući ne postoji: " << lista.postojiTekuci() << std::endl;
    return 0;
}
