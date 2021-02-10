## Proširenja jezika C
- Operandi nepreklopljenih `&`, `++` i `--` moraju da budu lvrednosti
- Rezultati nepreklopljenih `*`, `[]`, `++`, `--` i operatora dodele su lvrednosti
- Dosezi promenljivih deklarisanih u `for` i `if` su do kraja tih blokova
- `objekat.Klasa::polje` sintaksa za pristup poljima
- Statički, automatski, dinamički i privremeni životni vek
- Tip `decltype` zadržava referencu ukoliko je to povratna vrednost, ali `auto` to ne radi
- `enum struct`/`enum class` sakrivaju imena iza naziva nabrajanja, mora se razrešiti doseg
- Referenca na dvrednost je lvrednost

## Klase i objekti
- Podrazumevani konstruktor se briše pri definisanju bilo kog drugog konstruktora
- Kopirajući konstruktor se briše pri definisanju premeštajućeg konstruktora ili operatora dodele
- `friend Klasa;` je greška ako Klasa nije deklarisana, `friend class Klasa;` će tu raditi
- Lokalna klasa ne može da ima statičke atribute
- Potpuna glupost:
  ```cpp
  int Klasa::*pc;
  pc = &Klasa::polje;
  objekat.*pc = 1;
  pokazivac->*pc = 2;
  ```
- Konstruktori i operatori dodele se implicitno brišu ukoliko polja klase nemaju podrazumevane konstruktore ili su reference.

## Preklapanje operatora
- Ne mogu se preklopiti: `.`, `.*`, `::`, `?:`, `sizeof`, `alignof`, `typeid`, `throw`
- Predefinisani za korisničke tipove: `=`, `&`, `.`, `,` i za pokazivače `*`, `->`, `[]`
- Operatorske funkcije ne smeju da imaju podrazumevane vrednosti parametara
- `operator=`, `operator[]`, `operator()`, `operator->` i `operator T` moraju biti nestatičke metode
- `operator new` i `operator delete` moraju biti statičke metode čak iako nisu tako deklarisane, i ne mogu biti virtuelne (ali se nasleđuju)
- Postfiksni operatori imaju jedan dodatan `int` argument
- Modifikator `explicit` ukoliko želimo da se operator konverzije primenjuje samo eksplicitno
- Ugrađeni `new` i `delete` za objekat tipa `T` sa preklopljenim `operator new`/`operator delete` mogu se pozivati sa `::new` i `::delete`.
- Od operatora u nabrajanjima su podrazumevani `=` za isti tip nabrajanja i `(T)` u celobrojnu vrednost i iz celobrojne vrednost (ali samo eksplicitno)
    - Mogu se preklopiti samo operatori koji se ne preklapaju kao metodi
- Ugrađena kopirajuća dodela se briše prilikom definisana PK i PD, a premeštajuća prilikom definisanja KK, PK, KD

## Izvođenje
- Višestruko = jedna klasa se izvodi iz više, u više koraka = izvedena klasa se ponovo izvodi
- Pri izvođenju se ne nasleđuju konstruktori, destruktor i operator dodele, već postoje podrazumevani (mogu se uvesti)
- Modifikator `final` na klasi sprečava nasleđivanje a na virtuelnoj metodi dalje nadjačavanje
- `override` i `final` nisu deo potpisa metoda niti ključne reči
- Neslaganje povratnog tipa na virtuelnim metodama vraća grešku, osim ako neslaganje potiče od reference/pokazivača na osnovnu klasu koja u izvedenoj vraća pokazivač/referencu na izvedenu klasu (pri javnom izvođenju)
- Statički metodi i globalne prijateljske funkcije ne mogu biti virtuelni
- Virtuelni destruktor osnovne klase se implicitno poziva
- Niz objekata izvedene klase nije niz objekata osnovne klase
- Apstraktni destruktor mora biti definisan i to van tela klase
- `dynamic_cast` služi za kastovanje osnovne u izvedenu klasu (pokazivač)
    - Ako joj se prosledi ne-apstraktna klasa, greška u kompilaciji
    - Ako joj se prosledi klasa koja nije izvedena iz osnovne, ako je pokazivač vraća `nullptr` a ako je referenca baca `std::bad_cast` iz `<typeinfo>`
- Ako se `typeid` prosledi polimorfna klasa prvo se odredi koja prava klasa stoji iza nje

## Izuzeci
- Rukovaoc prihvata izuzetak ako:
    1. su istog tipa
    2. se prihvata osnovna klasa bačenog izuzetka
    3. se prihvata pokazivač/referenca i izuzetak može standardno da se konvertuje u rukovaoca
- Funkcijski `try` u konstruktoru ide pre liste inicijalizatora
- Rukovaoc u funkcijskom `try` u konstruktoru ne treba da pristupa poljima klase jer su dealocirani
- `unexpected` -> `terminate` (osim ako se ne promeni sa `set_unexpected`) -> `abort` (osim ako se ne promeni sa `set_terminate`)
- Kopirajući konstruktor mora da postoji kako bi se izuzetak klasnog tipa bacio
- Dinamički ugnežđen try je kada funkcija iz try bloka pozove drugu funkciju u kojoj je isto try blok a statički kada je samo try blok u try bloku

## Šabloni
- Implicitnim generisanjem na osnovu stvarnih argumenata funkcije nije moguće konvertovati argumente
- Ako prethodno postoji ne-generička funkcija sa istim parametrima, ona će biti pozvana umesto generičke osim ako parametri šablona nisu eksplicitno zadati prilikom poziva
- Ako se pri pisanju konstantnog izraza u stvarnim argumentima šablona pojavi `>`, on se mora ubaciti u zagrade: `(>)`
- Konstante u parametrima šablona moraju biti celobrojne ili pokazivačke
- Parcijalne specijalizacije ne smeju imati podrazumevane vrednosti parametara
- Generičke funkcije se mogu samo potpuno specijalizovati
- Virtuelni metodi i destruktor ne mogu da budu generički
- Poziv generičke metode može da ima i ključnu reč `template` pre imena metoda

## Greške
- Levi operand izraza kod poziva statičkog metoda **se izračunava**
- Ne treba pozivati `terminate()` iz zamene za `abort()`
- Nejasno je šta znači da su podrazumevane vrednosti argumenata šablona nebitne, jer ako se misli na to da se sve podrazumevane vrednosti u potpunosti ignorišu to je netačno, a ako se misli na to da se podrazumevane vrednosti ne koriste kada je iz poziva funkcije mogao da se odredi tip to je trivijalno (podrazumevane vrednosti argumenata funkcije se ne koriste kada se zadaju pravi argumenti)
- Specijalizacija je loše definisana
