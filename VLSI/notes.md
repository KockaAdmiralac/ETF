## Verilog
- `z` i `x` se evaluiraju u `x` pri operacijama nad njima i najčešće evaluiraju u netačno
- Ne treba koristiti negativne brojeve zapisane sa određenim brojem bitova zbog konverzije u neoznačene (drugi komplement)
- `===` može da poredi `x` i `z`
- Ako je rezultat prvog operanda `?:` jednak `x`, računaju se i drugi i treći operand i na mestima na kojima nisu isti stoji `x`
- `initial` ne može da se sintetizuje
- `always` mora imati trajanje duže od nule (ili biti ograničen uslovom)
- `0` -> `{x,z}` i `{x,z}` -> `1` su posedge, analogno za negedge
- Sekvencijalna logika sa asinhronim set/reset mora da ima u sebi if...else tako da sekvencijalna logika dolazi na kraju
- Događaji:
    - Update event: desila se promena signala ili događaja
    - Evaluation event: uputstva za izračunavanje procesa
    - Scheduling event: stavljanje događaja u red
- Zone:
    1. Aktivni događaji: zakazani za trenutni trenutak i ciklus
    2. Neaktivni događaji: zakazani za trenutni trenutak posle aktivnih (#0)
    3. Neblokirajuće dodele: zakazani za trenutni trenutak u nekom ranijem ciklusu
    4. Monitori: $monitor i $strobe
    5. Budući događaji: neaktivni i neblokirajući

## Resursi procesora
- Sabirači:
    - Ripple Carry Adder
        - S = A ^ B ^ C
        - C = AB + C(A+B)
        - Kašnjenje: linearno od broja razreda
    - Conditional Sum Adder
        - Formiraju se S i C za slučaj da ima i nema ulaznog prenosa pa onda biraju po nivoima
        - Kašnjenje: logaritamski od broja razreda
        - Veliki broj elemenata
    - Carry Select Adder
        - Cifre se grupišu u veći broj bitova
        - Osakaćeni multiplekser: C3_0 + C0 * C3_1
    - Carry Lookahead Adder
        - Bitovi prenosa se računaju paralelno
        - Zbog toga što za više razreda kola mogu da imaju veći broj ulaza pravi se komponenta za generator prenosa
        - Formula: (3 + 2(2N - 3) + 3)t = 4t * log_r(n)
    - Carry Save Adder
        - Za veći broj sabiraka, možemo da povežemo sabirače tako da je na svakom sledećem nivou carry smaknut za po jedno mesto ulevo
- Pomerači:
    - Sekvencijalni (registar)
    - Funnel
        - Poslednji nivo smaknut za 1, pretposlednji za 2, pa 4... bira se preko multipleksera
    - Barrel
        - Kao funnel ali kada ne može više da se smačinje onda pređe na sledeću stranu
        - EAO: 1 pri rotaciji i pomeranju udesno
        - LSC: 1 pri pomeranju udesno
        - RSC: 1 pri pomeranju udesno ili rotaciji udesno
        - AR: Aritmetički
- Množači:
    - Butov algoritam:
        - Gledaš cifre u parovima sa desna na levo
        - 00 i 11: sredina niza, ignorisati
        - 01: kraj niza, dodaje se množilac
        - 10: početak niza, oduzima se množilac
        - Svakim korakom pomera se ulevo
        - Implicitna nula na početku!
    - Modifikovani Butov algoritam
        - Isti kurac ali se gledaju trojke i pomera za po dva bita
        - Formiraju se sa leva na desno i može se dodati 0 na kraju ako nedostaje
        - 000 i 111 ne rade ništa
        - 1 kao prvi bit znači -
        - 011 i 100 su 2x

## Verifikacija
- Šta sve postoji u UVM:
    - test: okružujuća klasa celog testa
        - env: okruženje za testiranje
            - agent: grupiše drajver, monitor i sequencer
                - driver: gura signale iz item u interfejs
                - monitor: čita signale iz interfejsa
                - sequencer: prihvata sekvencu item-a
            - scoreboard: ocenjuje rezultate dobijene iz agenata
        - generator: klasa za proizvodnju stimulusa
            - item: klasa za stimuluse
- Hijerarhija:
    - item i generator nasleđuju uvm_sequence_item/uvm_sequence
    - Svi ostali nasleđuju uvm_component
- UVM komponente prolaze kroz faze
- Makroi za objekte služe tome da odaberemo kako se određene bazne akcije izvršavaju nad njima
- Pasivan agent: samo monitor
