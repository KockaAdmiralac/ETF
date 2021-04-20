- Da li su zaboravili da pozovu `asm int 60h` kad se prekid tajmera ne izvrši zbog kritične sekcije
- Zašto se koristi prekid 08h kad on nije namenjen za to
- Da li `semaphor.h` može da nam se zove samo `sem.h`


- `canInterrupt = false;` uvek mora da ima odgovarajući `canInterrupt = true;`!!!!!
- Deljeni podaci moraju biti `volatile`
- Ne zaboravi da markiraš kritične sekcije
- Ne zaboravi da su svi pozivi bibliotečkih funkcija kritične sekcije
- Ne zaboravi da cout može da postavi I na 1
