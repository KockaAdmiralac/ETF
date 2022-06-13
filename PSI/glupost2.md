# Principi softverskog inženjerstva
## Modeli
- Waterfall: svaka faza tačno jednom, redom
    - modifikacija: jedna osoba može da krene da radi sledeću fazu u prekretnicama
- V: nakon svake faze dolazi testiranje te faze
    - Zahtevi, dizajn, integracija, validacija, verifikacija, isporuka
    - Zahtevi, dizajn, implementacija, verifikacija
- Spiralni: ciklična analiza rizika
- Inkrementalni: razvija se po inkrementima, ne dobija se celokupna celina, radi se više slučajeva korišćenja istovremeno
- Iterativni: razvija se po iteracijama, dobija se celokupna celina
- Agile

## Upravljanje projektom
- "Najmanje jednočasovni sastanak nedeljno"
- Upravljanje konfiguracijom (i obuka)
    - "1 sat po članu projekta"
    - "konfiguracija 1 sat po članu projekta, 3 nedelje"

## Agile
- Manifest:
    - Pojedinci i interakcije imaju veću vrednost nego procesi i alati
    - Bez fokusa na dokumentaciju
    - Zajednički rad sa naručiocem
    - Fokus na promene umesto na plan
- Scrum:
    - 

## OO projektovanje
- OOA vs. OOD
- CRC kartice (Class, Responsibilities, Collaborators)
- SOLID principi:
    - Single responsibility principle: Klasa treba da ima samo jedan razlog za menjanje
    - Open-closed principle: Klase treba da budu zatvorene za menjanje, a otvorene za izvođenje
    - Liskov substitution principle: Objekti osnovne klase treba da budu zamenjivi objektima potklasa bez izmene u ponašanju
    - Interface segregation principle: Ne prisiljavati klasu da zavisi od metoda koje ne koristi
    - Princip inverzije zavisnosti: Implementacija treba da zavisi od apstrakcija, ne od konkretnih klasa nižeg nivoa

## Veb projektovanje
- Model 1 (glup) vs. model 2 (MVC)
- Projektni uzorci:
    - MVC
    - Page Controller (napravi model i prosledi mu podatke, onda to pošalje pogledu)
    - Front Controller (napravi komandu na osnovu podataka)
    - Template View
    - Dependency Injection
    - Query builder
    - Active record
    - Data mapper
        - Identity map
        - Unit of work
- Tipovi nasleđivanja:
    - Single table: Jedna tabela za polja svih podklasa
    - Class table: Po tabela za natklasu i potklase
    - Mapped superclass: Svaka podklasa nema vezu sa drugom

## Mikroservisi
- ACID: Atomicity, Consistency, Isolation, Durability
- CAP theorem
- BASE: Basically Available, Soft state, Eventual consistency
- Saga, CQRS. API Composition
- API gateway

## Procena napora
- Algoritamsko modelovanje troškova
- Ekspertska procena
- Procena po analogiji
- Parkinsonov zakon
- Pricing to win
- Poeni slučajeva korišćenja
    - UAW (1 - API, 2 - terminal, 3 - GUI)
    - UUCW (broj transakcija - koraka)
        - 1-3: 5
        - 3-7: 10
        - 8+: 15
    - UUCP (faktor tehničke kompleksnosti, faktori kompleksnosti okruženja): UUCP = UAW + UUCW
    - TCF (faktor tehnički kompleksnosti): TCF = 0.6 * (TSUM / 100)
        - TSUM se dobija na osnovu neke tabele, svakom fičeru se dodeli 0 ili 5 i množi sa težinom
    - ECF (uticaj faktora radnog okruženja): ECF = 1.4 - 0.03 * ESUM
        - ESUM je sličan kao TSUM
    - UCP: UUCP * TCF * ECF
    - PHM: Person-Hours multiplier, imaju neke tri magične brojke ili se mogu uzeti istorijski podaci
    - Effort = UCP * PHM
    - Months = 0.370 * Effort^0.328
    - AUCP
- Agilne:
    - Poker planiranja
        - Vade se neke glupe karte i onda objašnjavaju najviša i najniža
    - Procena afiniteta
