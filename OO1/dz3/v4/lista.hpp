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
        void operator+=(T &podatak);
        int dohvatiBrojPodataka() const {
            return brojPodataka;
        }
        // MEJL@Vladimir: Podaci se ne dealociraju pre vraćanja.
        T *operator-();
        T *operator*();
        template<typename T1> friend std::ostream &operator<<(std::ostream &it, const Lista<T1> &lista);
    private:
        struct Elem {
            T *podatak;
            // MEJL@Vladimir: Poželjno je da lista bude dvostruko ulančana.
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
void Lista<T>::operator+=(T &podatak) {
    ++brojPodataka;
    T *kopija = podatak.kopija();
    if (prvi == nullptr) {
        prvi = poslednji = new Elem(kopija, nullptr);
    } else {
        poslednji->sledeci = new Elem(kopija, poslednji);
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
    brojPodataka = 0;
    Elem *trenutni = lista.prvi;
    while (trenutni != nullptr) {
        // MEJL@Vladimir: Lista će biti korišćena samo za čuvanje podataka sa
        // kopija() metodom.
        (*this) += *(trenutni->podatak);
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
