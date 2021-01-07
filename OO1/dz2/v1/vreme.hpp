#ifndef _vreme_hpp
#define _vreme_hpp
#include <iostream>
#include <utility>

using namespace std::rel_ops;

class Vreme {
    public:
        Vreme(int sat, int minut, int sekund) :
            sat(sat), minut(minut), sekund(sekund) {}
        bool operator<(const Vreme &vreme2) const;
        bool operator==(const Vreme &vreme2) const;
        friend std::ostream &operator<<(std::ostream &it, const Vreme &vreme);
    private:
        int sat, minut, sekund;
        void pisi(std::ostream &it) const;
};

#endif
