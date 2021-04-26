# wat
## Pažnja
- `canInterrupt = false;` uvek mora da ima odgovarajući `canInterrupt = true;`!!!!!
- Deljeni podaci moraju biti `volatile`
- Ne zaboravi da markiraš kritične sekcije
- Ne zaboravi da su svi pozivi bibliotečkih funkcija kritične sekcije
- Ne zaboravi da cout može da postavi I na 1

## Pitanja
- Šta raditi ako semafor, nit ili događaj ne uspeju da alociraju svoju implementaciju
- Da li je problem ako ID može da se ponovo iskoristi i koliko puta će moći da se ponovo iskoristi
- Da li je dozvoljeno da menjamo zaglavlja
- Zar nije `Event::signal` implementacioni detalj pa stoga nema potrebe da stoji u interfejsu?
- Da li više događaja može da čeka na jednoj prekidnoj rutini/da li se to odražava na implementaciju `IVTEntry`
- ...kada dobijamo javni test
- Zašto se koristi 08h umesto 1Ch (na velikim konsultacijama)

## Zaključci
- Garantuje da će `waitToComplete` biti pozvana od strane korisnika u destruktoru niti (verovatno pitati ponovo na velikim konsultacijama)
- Kad se `waitToComplete` pozove nad niti koja nije započeta ništa se ne dešava
- U redu je da glavnoj niti dodelimo kvant vremena 0 (možda pitati ponovo na velikim konsultacijama)
- Svejedno je kako se zovu zaglavlja
