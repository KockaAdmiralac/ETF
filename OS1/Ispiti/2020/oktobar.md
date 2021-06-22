# Oktobar 2020
## 1. zadatak
```cpp
// Globalna
bool lock;

// Ulazak u kritičnu sekciju
while (test_and_set(&lock));
// Kritična sekcija
lock = false;
// ...
```

## 2. zadatak
```cpp
#include <iostream>

class Clock {
    public:
        Clock() : tickSem(0), tockSem(1) {}
        void tick();
        void tock();
    private:
        Semaphore tickSem;
        Semaphore tockSem;
};

void Clock::tick() {
    tockSem.wait();
    std::cout << "tick" << std::endl;
    tickSem.signal();
}

void Clock::tick() {
    tickSem.wait();
    std::cout << "tock" << std::endl;
    tockSem.signal();
}
```

## 3. zadatak
- Može da se desi da prevodilac više konstanti iste vrednosti alocira na istom mestu (kao što na primer postoji string pool u Javi) pa se upisom u jednu konstantu menjaju i sve ostale.
- Može da se desi da se te konstante čuvaju na stranici koja nije dozvoljena za upis (stranica sa kodom) pa se prilikom tog upisa generiše greška u pristupu stranici i operativni sistem ugasi proces.
- (Moguće je da procesor poseduje instrukciju koja dozvoljava neposredno adresiranje ali samo sa malim brojevima, a da se na to mesto upiše neki veći broj, pa se pregaze instrukcije koje se tu nalaze.)

## 4. zadatak
- VA(30): Page1(7) Page2(7) Offset(16)
- PA(30): Frame(14) Offset(16)
            PMT1
        /           \
 PMT2 PMT2          PMT2 PMT2
[128] [128]        [128] [128]
PMTsize = 2^7 * 2^5 = 2^12
Size = 5 * 2^12 = 5 * 4K = 20K

## 5. zadatak
Softverska komponenta koja može ali ne mora biti deo operativnog sistema (npr. mikrokernelski operativni sistemi) i služi za standardizovanu komunikaciju sa ulaznim i izlaznim uređajima. Drajvere obično proizvode proizvođači uređaja za koji su ti drajveri pravljeni i obično se pokreću u privilegovanom režimu (ali to ne mora biti slučaj).

## 6. zadatak
Tvrda veza je veza na datoteku koja služi tome da održava datoteku u fajl sistemu, dok god postoje tvrde veze na neku datoteku ona i dalje postoji, i kad se sve tvrde veze obrišu ona prestaje da postoji.

## 7. zadatak
Kod FAT fajl sistema se u FAT tabeli ulančavaju slobodni blokovi.
