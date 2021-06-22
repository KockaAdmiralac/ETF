# Jun 2020
## 1. zadatak
- f(3) -> f(2) -> fork f(1) -> f(0): 2
- f(2) -> fork f(1) -> f(0): 2
- f(4) -> fork f(3) -> f(2) -> fork f(1) -> f(0): 3
- f(0): 1
- f(1) -> f(0): 1
floor(n/2) + 1  /  ceil((n+1)/2)

## 2. zadatak
1. P1 uradi proveru za `flag2` i vidi da je `false`, prođe i promeni kontekst
2. P2 postavi `flag2` na `true` i uradi proveru za `flag1` i vidi da je `false`, prođe i uđe u kritičnu sekciju
3. P1 postavi `flag1` na `true` i uđe u kritičnu sekciju
4. Oba su u kritičnoj sekciji

## 3. zadatak
Dinamičko učitavanje nam samo kaže da neki deo učitavamo kasnije kada je potreban, preklopi zahtevaju da se jedan isti segment memorije koristi za dve različite strukture u različitim vremenima (vremensko multipleksiranje)

## 4. zadatak
1MB -> VA(20): S(12) P(8)
Alocirano: 00000-00FFF i FF000-FFFFF
- 004CA: Alocirano u prvom logičkom segmentu, alociraće stranicu i u PMT ubaciti unos za tu stranicu
- FF745: Alocirano u drugom logičkom segmentu, ...
- F0745: Nije alocirano, generisaće signal procesu koji je tražio ovu memoriju i završiće ga

## 5. zadatak
```cpp
int sync_write(char* buffer) {
    int request = async_write(buffer);
    if (request < 0) {
        return request;
    }
    wait(request);
}
```

## 6. zadatak
Neće, jer njena grupa nema pristup pisanju u fajl, iako ostali imaju

## 7. zadatak
Za manji fajl se upotrebljava manji klaster a za veći fajl veći klaster pa je manja interna fragmentacija
