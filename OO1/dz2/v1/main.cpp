#include <iostream>
#include "piksel.hpp"
#include "pozicija.hpp"
#include "slika.hpp"
#include "crnobela.hpp"

int main(void) {
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
    return 0;
}
