#ifndef NUT_HPP
#define NUT_HPP
#include <iostream>

class NutritivnaVrednost {
    public:
        NutritivnaVrednost(double uh, double masti, double proteini) :
            uh(uh), masti(masti), proteini(proteini) {}
        double dohvatiUgljeneHidrate() const {
            return uh;
        }
        double dohvatiMasti() const {
            return masti;
        }
        double dohvatiProteine() const {
            return proteini;
        }
        double brojKalorija() const {
            return (uh + proteini) * 4 + masti * 9;
        }
        friend NutritivnaVrednost operator+(const NutritivnaVrednost &nv1, const NutritivnaVrednost &nv2);
        friend std::ostream &operator<<(std::ostream &it, const NutritivnaVrednost &nv);
    private:
        double uh, masti, proteini;
        void pisi(std::ostream &it) const;
};

#endif
