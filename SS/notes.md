# Asembler
## Tabela simbola

| SymbolValue     | Type  | Bind  | Section | Size/Alignment | SymbolName    |
|-----------------|-------|-------|---------|----------------|---------------|

- `Bind`: `LOC`, `GLOB`
- `Type`: `SCTN`, `NOTYP`
- `Section`: Indeks sekcije, ako je nedefinisan onda je spoljašnji simbol

## Tabela sekcija

| Name     | BaseAddress     | Length  |
|----------|-----------------|---------|


## Tabela relokacija

| Offset           | Type        | Symbol   | Addend |
|------------------|-------------|----------|--------|

## Tabela literala

| Value            | Size             | Location         |
|------------------|------------------|------------------|

## Tabela obraćanja unapred

| SymbolIdentifier | SymbolValue | flink                   |
|------------------|-------------|-------------------------|

## Tabela direktiva
(opciono) Mapira mnemonik asemblerske direktive na potprogram za obradu te direktive.

## Ispravnost relokacije
- Apsolutni simbol i literal se menja nulom (`0`)
- Relokativni simbol se menja jednom jedinicom sekcije kojoj pripada (`1.section`)
- Eksterni simbol se menja jednom jedinicom jedinstvene sekcije (`1.unique()`)
- Krajnja vrednost:
    - 0: apsolutan izraz
    - jedna jedinica jedne sekcije: relokativan izraz
    - inače: nije relokativan izraz

## Tipovi relokacije
[Docs](https://www.ucw.cz/~hubicka/papers/abi/node19.html):

- `R_X86_64_32`: Za određivanje konačne vrednosti na simbol se doda addend
- `R_X86_64_32S`: Isto ali linker ima zadatak da proveri da li je rezultat moguće smestiti u 32 bita
- `R_X86_64_PC32`: PC-relativno adresiranje, za određivanje konačne vrednosti izračuna se razlika između trenutne lokacije i lokacije simbola i na to se doda addend (može da se desi da je lokacija usred instrukcije pa se oduzima broj bajtova u instrukciji kroz addend)

## Napomene

- Kada je simbol lokalan, asembler ne sme da ostavlja linkeru reference na njega, i zato je relokacioni zapis u odnosu na sekciju a ne simbol
- `.rela` -> addend, `.rel` -> nema addend (u memorijskoj lokaciji se čuva addend)
