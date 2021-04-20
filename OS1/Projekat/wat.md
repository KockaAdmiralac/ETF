# wat
## Pažnja
- `canInterrupt = false;` uvek mora da ima odgovarajući `canInterrupt = true;`!!!!!
- Deljeni podaci moraju biti `volatile`
- Ne zaboravi da markiraš kritične sekcije
- Ne zaboravi da su svi pozivi bibliotečkih funkcija kritične sekcije
- Ne zaboravi da cout može da postavi I na 1

## Pitanja
- Da li nam se garantuje da će waitToComplete biti pozvan iz destruktora niti u kojima se takvo ponašanje očekuje
- Šta se desi ako se pozove waitToComplete nad niti nad kojom nije pozvan start
- Da li su zaboravili da pozovu `asm int 60h` kad se prekid tajmera ne izvrši zbog kritične sekcije
- Zašto se koristi prekid 08h kad on nije namenjen za to
- Da li `semaphor.h` može da nam se zove samo `sem.h`
- Da li svejedno koliki kvant vremena dodeljujemo glavnoj niti
- Kada dobijamo javni test
