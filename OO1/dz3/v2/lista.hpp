#ifndef LISTA_HPP
#define LISTA_HPP
#include <exception>

class GNemaTekuceg : public std::exception {
    public:
        const char *what() const noexcept override {
            return "Nema tekućeg elementa!";
        }
};

template<typename T>
class Lista {
    struct Elem {
        T podatak;
        Elem *sledeci = nullptr;
        Elem(T podatak) : podatak(podatak) {}
    };
    public:
        Lista() = default;
        Lista(const Lista<T> &lista) = delete;
        Lista &operator=(Lista &) = delete;
        void dodaj(T novi);
        void naPrvi() const;
        void naSledeci() const;
        bool postojiTekuci() const {
            return tekuci != nullptr;
        }
        T &dohvatiTekuci() const;
        void isprazni();
        ~Lista() {
            isprazni();
        }
    private:
        Elem *prvi = nullptr,
             *poslednji = nullptr;
        mutable Elem *tekuci = nullptr;
};

template<typename T>
void Lista<T>::dodaj(T novi) {
    Elem *elem = new Elem(novi);
    if (prvi == nullptr) {
        prvi = poslednji = tekuci = elem;
    } else {
        poslednji->sledeci = elem;
        poslednji = elem;
    }
}

template<typename T>
void Lista<T>::naPrvi() const {
    tekuci = prvi;
}

template<typename T>
void Lista<T>::naSledeci() const {
    if (tekuci != nullptr) {
        tekuci = tekuci->sledeci;
    }
}

template<typename T>
T &Lista<T>::dohvatiTekuci() const {
    if (!postojiTekuci()) {
        throw GNemaTekuceg();
    }
    return tekuci->podatak;
}

template<typename T>
void Lista<T>::isprazni() {
    tekuci = prvi;
    while (tekuci != nullptr) {
        Elem *tmp = tekuci->sledeci;
        delete tekuci;
        tekuci = tmp;
    }
    prvi = poslednji = nullptr;
}

#endif
