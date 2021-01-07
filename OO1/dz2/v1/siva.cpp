#include "siva.hpp"

void SlikaUNijansamaSive::postavi(const Piksel &piksel, const Pozicija &pozicija) {
    double sredina = (
        piksel.crvenaBoja() + piksel.zelenaBoja() + piksel.plavaBoja()
    ) / 3;
    kanal sredinaK = sredina;
    Slika::postavi({sredinaK, sredinaK, sredinaK}, pozicija);
}
