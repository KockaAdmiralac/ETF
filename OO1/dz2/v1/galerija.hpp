#ifndef _galerija_hpp
#define _galerija_hpp
#include <iostream>
#include <vector>
#include "slika.hpp"

class Galerija {
    public:
        virtual Galerija &operator+=(const Slika &slika) {
            slike.push_back(&slika);
            return *this;
        }
        std::size_t brojSlika() const {
            return slike.size();
        }
        std::size_t brojBitova() const;
        const Slika &operator[](std::size_t indeks) {
            return (*slike[indeks]);
        }
        friend std::ostream &operator<<(std::ostream &it, const Galerija &galerija);
    protected:
        std::vector<const Slika*> slike;
    private:
        void pisi(std::ostream &it) const;
};

#endif
