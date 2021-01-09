#ifndef PAR_HPP
#define PAR_HPP
#include <iostream>

// KONSULTACIJE@Uroš: Rečeno je da se par može formirati sa dva različita
// tipa podatka.
// MEJL@Adrian: ...ali je onda rečeno da se par može formirati samo sa
// jednim tipom podatka. Pošto je Adrianov zadatak, uzimamo ovaj pristup.
template<typename T>
class Par {
    public:
        Par(T *prvi, T *drugi) : prvi(prvi), drugi(drugi) {}
        T *dohvatiPrvi() const {
            return prvi;
        }
        T *dohvatiDrugi() const {
            return drugi;
        }
        void postaviPrvi(T *prvi) {
            this->prvi = prvi;
        }
        void postaviDrugi(T *drugi) {
            this->drugi = drugi;
        }
        template<typename T1> friend bool operator==(const Par<T1> &par1, const Par<T1> &par2);
        template<typename T1> friend std::ostream &operator<<(std::ostream &it, const Par<T1> &par);
    private:
        T *prvi, *drugi;
        void pisi(std::ostream &it) const;
};

template<typename T>
bool operator==(const Par<T> &par1, const Par<T> &par2) {
    return (*par1.prvi) == (*par2.prvi) && (*par1.drugi) == (*par2.drugi);
}

template<typename T>
std::ostream &operator<<(std::ostream &it, const Par<T> &par) {
    par.pisi(it);
    return it;
}

template<typename T>
void Par<T>::pisi(std::ostream &it) const {
    it << "[" << (*prvi) << " - " << (*drugi) << "]";
}

#endif
