#ifndef _piksel_hpp
#define _piksel_hpp
#include <iostream>

using kanal = unsigned char;

class Piksel {
    public:
        Piksel(kanal c=0, kanal z=0, kanal p=0) :
            crvena(c), zelena(z), plava(p) {}
        kanal crvenaBoja() const {
            return crvena;
        }
        kanal zelenaBoja() const {
            return crvena;
        }
        kanal plavaBoja() const {
            return crvena;
        }
        Piksel operator+(const Piksel &b);
        bool operator==(const Piksel &b);
        friend std::ostream &operator<<(std::ostream &it, const Piksel &piksel);
    private:
        kanal crvena, zelena, plava;
};

#endif
