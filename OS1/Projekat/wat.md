# wat
## Pažnja
- `canInterrupt = false;` uvek mora da ima odgovarajući `canInterrupt = true;`!!!!!
- Deljeni podaci moraju biti `volatile`
- Ne zaboravi da markiraš kritične sekcije
- Ne zaboravi da su svi pozivi bibliotečkih funkcija kritične sekcije
- Ne zaboravi da cout može da postavi I na 1

## Pitanja
- Šta raditi ako semafor, nit ili događaj ne uspeju da alociraju svoju implementaciju
