#ifndef LISTA_HPP
#define LISTA_HPP
#include <exception>
#include <iostream>

class GPrazna : public std::exception {
    public:
        const char *what() const noexcept override {
            return "Lista je prazna!";
        }
};

template<typename T>
class Lista {
    public:
        Lista() = default;
        Lista(const Lista &lista) {
            kopiraj(lista);
        }
        Lista(Lista &&lista) {
            premesti(lista);
        }
        ~Lista() {
            brisi();
        }
        Lista &operator=(const Lista &lista);
        Lista &operator=(Lista &&lista);
        // Na vežbama 12 oko 40:30 se priča o tome kako očekujemo da ovoj
        // metodi bude prosleđena polimorfna kopija, što znači da mi ne moramo
        // sami da pozivamo tu metodu ovde.
        void operator+=(T *podatak);
        int dohvatiBrojPodataka() const {
            return brojPodataka;
        }
        // PRETPOSTAVKA: Podaci se ne dealociraju prilikom vraćanja. Kada bismo
        // ih dealocirali, morali bismo da vraćamo njihove kopije iz ove metode
        // po vrednosti, čime oni gube svoja polimorfna svojstva. Pošto je
        // baš poenta ove liste da čuva polimorfne kopije podataka, to ne smemo
        // da dopustimo.
        T *operator-();
        T *operator*();
        template<typename T1> friend std::ostream &operator<<(std::ostream &it, const Lista<T1> &lista);
    protected:
        struct Elem {
            T *podatak;
            // PRETPOSTAVKA: Lista je dvostruko ulančana. Ovo olakšava izbacivanje
            // sa početka i sa kraja.
            Elem *prethodni, *sledeci;
            Elem(T *podatak, Elem *prethodni) : podatak(podatak),
                prethodni(prethodni), sledeci(nullptr) {}
        };
        int brojPodataka = 0;
        Elem *prvi = nullptr, *poslednji = nullptr;
        void kopiraj(const Lista<T> &lista);
        void premesti(Lista<T> &lista);
        void brisi();
        void pisi(std::ostream &it) const;
};

template<typename T>
Lista<T> &Lista<T>::operator=(const Lista<T> &lista) {
    if (&lista != this) {
        brisi();
        kopiraj(lista);
    }
    return *this;
}

template<typename T>
Lista<T> &Lista<T>::operator=(Lista<T> &&lista) {
    if (&lista != this) {
        brisi();
        premesti(lista);
    }
    return *this;
}

template<typename T>
void Lista<T>::operator+=(T *podatak) {
    ++brojPodataka;
    if (prvi == nullptr) {
        prvi = poslednji = new Elem(podatak, nullptr);
    } else {
        poslednji->sledeci = new Elem(podatak, poslednji);
        poslednji = poslednji->sledeci;
    }
}

template<typename T>
T *Lista<T>::operator-() {
    if (prvi == nullptr) {
        throw GPrazna();
    }
    --brojPodataka;
    T *podatak = poslednji->podatak;
    Elem *prethodni = poslednji->prethodni;
    delete poslednji;
    poslednji = prethodni;
    if (poslednji == nullptr) {
        prvi = nullptr;
    } else {
        poslednji->sledeci = nullptr;
    }
    return podatak;
}

template<typename T>
T *Lista<T>::operator*() {
    if (prvi == nullptr) {
        throw GPrazna();
    }
    --brojPodataka;
    T *podatak = prvi->podatak;
    Elem *sledeci = prvi->sledeci;
    delete prvi;
    prvi = sledeci;
    if (prvi == nullptr) {
        poslednji = nullptr;
    } else {
        prvi->prethodni = nullptr;
    }
    return podatak;
}

template<typename T>
std::ostream &operator<<(std::ostream &it, const Lista<T> &lista) {
    lista.pisi(it);
    return it;
}

template<typename T>
void Lista<T>::kopiraj(const Lista<T> &lista) {
    brojPodataka = lista.brojPodataka;
    Elem *trenutni = lista.prvi;
    while (trenutni != nullptr) {
        // PRETPOSTAVKA: Radi se ne-polimorfna kopija podatka. Ovo je jako
        // čudno, pošto je cela poenta ove klase da čuva polimorfne kopije, ali
        // se u Izraz klasi koja očigledno nasleđuje ovu klasu pominje da mora
        // da postoji metod polimorfne kopije, što implicira da se,
        // podrazumevano, u ovoj klasi ta polimorfna kopija ne radi.
        // Još jedan moguć razlog jeste to da nam niko ne garantuje naziv
        // metode za pravljenje polimorfne kopije.
        (*this) += new T(*trenutni->podatak);
        trenutni = trenutni->sledeci;
    }
}

template<typename T>
void Lista<T>::premesti(Lista<T> &lista) {
    brojPodataka = lista.brojPodataka;
    prvi = lista.prvi;
    poslednji = lista.poslednji;
    lista.prvi = nullptr;
    lista.poslednji = nullptr;
}

template<typename T>
void Lista<T>::brisi() {
    brojPodataka = 0;
    Elem *trenutni = prvi;
    while (trenutni != nullptr) {
        delete trenutni->podatak;
        Elem *tmp = trenutni->sledeci;
        delete trenutni;
        trenutni = tmp;
    }
}

template<typename T>
void Lista<T>::pisi(std::ostream &it) const {
    Elem *trenutni = prvi;
    while (trenutni != nullptr) {
        it << (*trenutni->podatak);
        trenutni = trenutni->sledeci;
        if (trenutni != nullptr) {
            it << " ";
        }
    }
}

#endif
