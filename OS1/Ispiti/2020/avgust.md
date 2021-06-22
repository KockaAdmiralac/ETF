# Avgust 2020
## 1. zadatak
4, jer se u detetu petlja ne nastavlja (fork() == 0)

## 2. zadatak
1. P1 proveri uslov u petlji, vidi da je `flag2` false i prođe
2. Desi se promena konteksta
3. P2 proveri uslov u petlji, vidi da je `flag1` false i prođe
4. Desi se promena konteksta
5. P1 uđe u kritičnu sekciju
6. Desi se promena konteksta
7. P2 uđe u kritičnu sekciju
8. Oba su u kritičnoj sekciji

## 3. zadatak
Isto kao u u junu.

## 4. zadatak
Zato što alocirani segmenti mogu da budu različite veličine, dok su stranice uvek iste veličine i njima je moguć pristup u svakom delu.

## 5. zadatak
Isto kao u junu.

## 6. zadatak
Može da se desi da se promeni deo koji pokazuje na sledeći blok fajla, pa ostatak blokova ostane izgubljen dok je moguće da se taj blok nadoveže na neke druge blokove nekog drugog fajla i tako stavi fajl sistem u nekonzistentno stanje. Najbolji slučaj je kada se izmeni deo bloka sa sadržajem fajla, a ne pokazivačem, tako da je smetnja lokalizovana na taj fajl.

## 7. zadatak
Inkrementalni bekap jeste kada se bekapuju samo promene između poslednjeg bekapa i trenutnog, dok je totalni bekap zamena svih fajlova starog bekapa novim bez obzira na to da li su se promenili ili ne (ne mora da bude zamena, može da se odvojeno kopiraju, ali poenta je da se ne proveravaju razlike).
