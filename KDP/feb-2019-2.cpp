#include "common.h"

sem ulaz = 1;
sem prvi = 0;
int staraVrednost;
bool vrednostPostavljena;

int zameni(int vrednost) {
    int novaVrednost;
    ulaz.wait();
    if (vrednostPostavljena) {
        // Други процес
        novaVrednost = staraVrednost;
        staraVrednost = vrednost;
        prvi.signal();
    } else {
        // Први процес
        staraVrednost = vrednost;
        vrednostPostavljena = true;
        ulaz.signal();
        prvi.wait();
        novaVrednost = staraVrednost;
        vrednostPostavljena = false;
        ulaz.signal();
    }
    return novaVrednost;
}
