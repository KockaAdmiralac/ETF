# wat
## Pažnja
- `canInterrupt = false;` uvek mora da ima odgovarajući `canInterrupt = true;`!!!!!
- Deljeni podaci moraju biti `volatile`
- Ne zaboravi da markiraš kritične sekcije
- Ne zaboravi da su svi pozivi bibliotečkih funkcija kritične sekcije
- Ne zaboravi da cout može da postavi I na 1

## Pitanja

## Zaključci
- `exit()` treba da gasi bez čekanja na ostale niti kad se izlazi iz glavne niti
- 08 poziva 1C na kraju pa se koristi 08 (ima neki komplikovan razlog ali ne koristiti 1C)
- Garantuje da će `waitToComplete` biti pozvana od strane korisnika u destruktoru niti (verovatno pitati ponovo na velikim konsultacijama)
- Kad se `waitToComplete` pozove nad niti koja nije započeta ništa se ne dešava
- U redu je da glavnoj niti dodelimo kvant vremena 0
- Nije svejedno kako se zovu zaglavlja
- Ako ne uspe da alocira svoju implementaciju ne moramo da signaliziramo nikakvu grešku već samo da kernel ne umre
- ID mrtvih niti može ponovo da se iskoristi
- `PREPAREENTRY` mora da stoji u `evt.h`
- Zaglavlja ne smemo da menjamo
- `Event::signal` može da se poziva iz prekidne rutine ali ne mora
