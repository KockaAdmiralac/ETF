#include <iostream>
#include "piksel.hpp"
#include "pozicija.hpp"
#include "slika.hpp"
#include "crnobela.hpp"
#include "sarena.hpp"
#include "siva.hpp"
#include "uredjena.hpp"

int main(void) {
    /*
    // Piksel
    Piksel pxa(0, 0), pxb(3, 3, 3), pxc(128, 128, 128), pxd;
    std::cout << (pxa + pxb) << " "
              << (pxa == pxb) << " "
              << (pxa == pxd) << std::endl
              << int(pxa.crvenaBoja()) << " "
              << int(pxa.zelenaBoja()) << " "
              << int(pxa.plavaBoja()) << " "
              << pxa << std::endl;
    // Pozicija
    Pozicija pza(0, 0), pzb(1, 2);
    std::cout << pza.dohvatiKolonu() << " "
              << pza.dohvatiVrstu() << " "
              << (pza - pzb) << std::endl;
    // Slika
    Slika sa(3, 3);
    std::cout << sa.brojBitova() << " "
              << sa.dohvatiSirinu() << " "
              << sa.dohvatiVisinu() << std::endl
              << sa << std::endl;
    sa.postavi(pxb, pza);
    sa.postavi(pxc, pzb);
    std::cout << sa[pza] << " "
              << sa[pzb] << std::endl
              << sa << std::endl;
    // Crno-bela slika
    CrnoBelaSlika csa(3, 3);
    csa.postavi(pxb, pza);
    csa.postavi(pxc, pzb);
    std::cout << csa << std::endl;
    */
    UredjenaGalerija galerija;
    Slika slika(2, 2, {1, 2, 3});
    slika.postavi({0, 5, 8}, {1, 1});
    galerija += slika;
    CrnoBelaSlika crnobela(2, 2, {1, 2, 4});
    crnobela.postavi({128, 128, 128}, {0, 0});
    galerija += crnobela;
    SlikaUNijansamaSive siva(2, 2, {2, 0, 0});
    siva.postavi({7, 8, 9}, {0, 1});
    galerija += siva;
    SarenaSlika sarena(2, 2, {1, 1, 4});
    sarena.postavi({1, 1, 1}, {0, 0});
    sarena.postavi({1, 1, 1}, {0, 1});
    galerija += sarena;
    std::cout << galerija;

    SarenaSlika kombinovana(slika, crnobela);
    std::cout << kombinovana << std::endl;
    std::cout << (CrnoBelaSlika)siva << std::endl;
    return 0;
}
