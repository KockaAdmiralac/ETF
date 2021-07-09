# Jul 2020
## 1. zadatak
- Memorija se prenosi sa adrese 1000h
- Ulazno/izlazni i adresni prostor su razdvojeni
- Kontrolni registar uređaja je na FF00h, registar podataka na FF01h a statusni registar na FF02h
- Adresiranje je bajtovsko
- Blok je veličine 100h bajtova
- Registri su veličine 16 bita i kad se čita ili piše iz memorije ili na uređaj koristi se najnižih 8 bita
- Najniži bit kontrolnog registra je bit Start, najniži bit statusnog registra je bit Ready
```asm
        load r0, #1000h             ; adresa
        load r1, #100h              ; brojač
        load r2, #0                 ; nula
        load r3, #1                 ; privremeni registar
        out FF00h, r3               ; pokrećemo periferiju
loop:   in FF02h, r3                ; čitamo statusni registar
        and r3, r3, #1              ; proveravamo ready bit
        jz loop                     ; ako je ready = 0 čitamo ponovo
        load r3, (r0)               ; učitavamo podatak iz memorije
        out FF01h, r3               ; šaljemo podatak na periferiju
        inc r0                      ; inkrementiramo adresu
        dec r1                      ; dekrementiramo brojač (postavlja se PSW)
        jnz loop                    ; ako brojač != 0 vraćamo se na čekanje
        load r3, #0                 ; gasimo periferiju
        out FF00h, r3
```

## 2. zadatak
```cpp
const unsigned N = ...;
class ForkThread : public Thread {
    public:
        ForkThread(unsigned n) : n(n) {}
        virtual void run();
    private:
        unsigned n;
};

void ForkThread::run() {
    while (n % 2 && !fork()) {
        --n;
    }
}
```

## 3. zadatak
AAAAAAAABBCCCCCCCCCCCCCCCCDDDD--
--------BBCCCCCCCCCCCCCCCCDDDD--
--------BBCCCCCCCCCCCCCCCCDDDDE-
FFFF----BBCCCCCCCCCCCCCCCCDDDDE-
FFFF------CCCCCCCCCCCCCCCCDDDDE-
- 2 slobodna fragmenta
- Najmanji 16K
- Najveći 96K

## 4. zadatak
VA(32): Page1(8) Page2(12) Offset(12)
- 2^8 * 2^12 * 2^4 + 2^8 * 2^4 = 2^24 + 2^12 = 16M + 4K
- 2^8 * 2^4 + 2^12 * 2^4 = 2^12 + 2^16 = 4K + 64K = 68K

## 5. zadatak
Proces se blokira dok čeka da pošalje zahtev štampaču, a za to vreme je mogao nešto korisnije da radi

## 6. zadatak
```cpp
int main(void) {
    FHANDLE file = open("proba.txt");
    seek(file, size(file));
    char buf[2];
    buf[1] = '\0';
    while (true) {
        buf[0] = getchar();
        if (buf[0] == 'X') {
            break;
        }
        append(file, 1);
        write(file, buf);
    }
    close(file);
    return 0;
}
```

## 7. zadatak
1. n
2. 2
