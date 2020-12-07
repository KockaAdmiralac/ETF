#include "crnobela.hpp"

void CrnoBelaSlika::postavi(const Piksel &piksel, const Pozicija &pozicija) {
    double sredina = (
        piksel.crvenaBoja() + piksel.zelenaBoja() + piksel.plavaBoja()
    ) / 3;
    if (sredina > 127) {
        Slika::postavi({255, 255, 255}, pozicija);
    } else {
        Slika::postavi({0, 0, 0}, pozicija);
    }
}
