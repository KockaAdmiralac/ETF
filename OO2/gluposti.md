## Pregled
- `char` je UTF-16 kodiran
- `>>>` šiftuje tako da 0 dođe na levu stranu a `>>` tako da dođe znak
- Labele služe za iskakanje iz petlji pomoću `break` i `continue`
- `niska = new String("niska")` eksplicitno instancira novi objekat niske dok `niska = "niska"` može da pokazuje i na konstantu
- Niske su immutable
- Aktivni objekti mogu ili naslediti Thread ili implementirati Runnable

## Klase
- Reference se prenose po vrednosti, a objekti po referenci
- Mogu postojati dve metode sa istim imenom ako imaju različit broj ili tipove argumenata
- Inicijalizacioni blok može da baci izuzetak samo ako su svi konstruktori definisani da bacaju taj izuzetak
- Inicijalizacioni blok mora imati `static` za statički inicijalizaciju i ne može pozivati metode koje su deklarisane kao da bacaju izuzetke
- U problemu ciklične statičke inicijalizacije može da se desi da ako jedan statički inicijalizator poziva statički metod druge klase i obrnuto da se jedan od inicijalizatora ne izvrši do kraja (neće doći do rekurzije)
- Metod `finalize()` se izvršava pre oslobađanja prostora kod mrtvih objekata ili pre gašenja programa kod živih i ima `throws Throwable`
- Neobrađeni izuzeci u `finalize()` se ignorišu
- Pri izlasku iz programa s nekim greškama poput OOM neke `finalize()` metode mogu da se ne izvrše
- `finalize()` može da oživi objekat ako postavi referencu na njega, ali će se pozvati samo jednom za taj objekat tako da može samo jednom da ga oživi

## Paketi
- Dozvoljen je uvoz statičkih imena preko `import static`
- Ako je klasa javna mora da bude definisana u sopstvenom fajlu
- "friendly" == "package-private"

## Izvođenje
- Automatsko pakovanje: `Object o = 100;` (primitivan tip se pakuje u objekat klase)
- Zaštićenom članu se može pristupiti iz izvedene klase direktnim imenovanjem ili reference na objekte tipa te izvedene klase ili neke od izvedenih klasa te izvedene klase
- Zaštićenom statičkom članu se može pristupiti preko osnovne i bilo koje izvedene
- protected je slabije od package-private
- `super()` mora biti prva naredba u konstruktoru ako se koristi
    - ako se ne koristi, biće pozvan podrazumevani konstruktor
    - ako ne postoji, mora da se koristi `super()`
- `this(...)` je poziv sopstvenog konstruktora, mora biti prva naredba u konstruktoru i tada se ne može zvati konstruktor osnovne klase (delegiranje)
- Podrazumevani konstruktor je javan samo ako je klasa javna
- Redosled izvršavanja konstruktora i inicijalizatora isti kao u C++
- Ako se pozove metod prilikom inicijalizacije, taj metod će biti pozvan nad neinicijalizovanim objektom
- Nadjačavanje je podrazumevano dinamički u Javi, sve ostalo isto kao u C++
- Statički metodi ne mogu da se polimorfno redefinišu i nemaju pristup `super`
- Ne može se smanjiti pravo pristupa nadjačanom metodu
- Kada se pristupa polju klase i kada se metoda poziva preko `super` koristi se tip reference (nepolimorfno)
- Ako se sužavanje može proveriti dolazi do greške prilikom prevođenja, ako ne može dolazi do `ClassCastException`
- Klase koje se kloniraju moraju da implementiraju Cloneable
- Naklonosti prema kloniranju:
    1. Bezuslovno: Klasa je Cloneable i ima javni `clone()` koji ne baca izuzetke
    2. Uslovno: Klasa je Cloneable i javni `clone()` može da baci izuzetak od objekata nad kojim je pokušano kloniranje
    3. Dopuštanje potklasi: Zaštićen `clone()` koji ako je potrebno klonira njena polja
    4. Nedopuštanje: Javni konačni `clone()` koji uvek baca izuzetak

## Interfejsi
- Modifikator `protected` nije dozvoljen, modifikator `private` je dozvoljen kad ima telo, podrazumevani modifikator je `public`
- `default` i `static` metodi u interfejsu mogu imati telo
- Polja interfejsa su uvek statička, javna i konačna
- Poenta podrazumevanih metoda jeste da se izbegne modifikovanje postojećih aplikacija nakon proširivanja interfejsa
- Ako se metodi dva implementirana interfejsa razlikuju samo po povratnom tipu to je greška, a samo po throws klauzuli to pravi metod koji "zadovoljava" obe klauzule (presek?)
- Greška je ukoliko se nasleđuju dva različita podrazumevana metoda sa istim potpisom i nisu implementirani u samoj klasi
- Nestatičke metode natklase sa istim potpisom kao podrazumevane metode interfejsa ih nadjačavaju
- Ako dva implementirana interfejsa imaju isti naziv konstante, naziv se mora kvalifikovati
- Nabrajanja se alociraju na hipu a konstante tipa nabrajanja su reference na njih

## Izuzeci
- Greška je ako je opštiji rukovaoc iznad konkretnijeg

## Ugnježđene klase
- Potpuno uzajamno poverenje sa okružujućom
- Klasa koja nasleđuje ugnežđenu ne nasleđuje prava pristupa
- Nestatičke ugnežđene klase moraju uvek biti u kontekstu njihove spoljašnje klase kako bi se znalo kojim poljima spoljašnje klase pristupaju neposredno
    - Izvedena ugnežđena klasa može biti u vezi sa objektom osnovne ili izvedene
- Klasa ugnežđena u interfejs kao i ugnežđeni interfejs su uvek statički
- Unutrašnja klasa ne sme da sadrži statičke članove osim konačnih inicijalizovanih konstantnim izrazom
    - Sekundarni `this`: `Spoljašnja.this.polje`
    - Ovo isto važi za lokalne klase
- Unutrašnje klase se mogu instancirati preko reference na objekat spoljašnje klase: `spolj.new Unut(...)`
- Pri konstrukciji objekta izvedene unutrašnje klase, prvo se poziva konstruktor osnovne spoljne (`IzvedenaSpoljna.this.super()`) a zatim konstruktor osnovne unutrašnje koji prima referencu do spoljne
- Ako je klasa koja nasleđuje unutrašnju samostalna, mora se pozvati `super()` nad objektom spoljne
- Anonimna klasa ne može da ima `extends` i `implements`
- Ako je potreban poziv specifičnog konstruktora nadklase, iza imena apstraktne klase dodaju se argumenti
- Lambda izrazi su u pozadini anonimne klase
- Parametri lambda izraza mogu nemati tipove ukoliko se mogu zaključiti iz konteksta, ali ako jedan nema svi moraju da nemaju
- Funkcijski interfejs je interfejs sa jednom apstraktnom metodom koji može imati `@FunctionalInterface`

## Niti
- Brava klase nema efekta na brave objekata klase
- `synchronized` se ne nasleđuje, ali se poziv metoda superklase računa kao poziv sinhronizovanog metoda
- `wait` i `notify` se pozivaju samo iz sinhronizovanih metoda

## Generici
- Kada se koriste sirovi tipovi vraća se na staro ponašanje (vraća se `Object`)
- Parametar generika se ne može koristiti u statičkom polju
- Statičkom članu se ne može pristupiti preko parametrizovanog imena tipa
- Nije dozvoljeno praviti nove objekte tipa T (ne zna se koji objekat da napravi, tip je izgubljen)
- Argumenti generika moraju biti tipovi do kojih se može napraviti referenca, tj. ne-primitivni tipovi
- U pozivu konstruktora se mogu izostaviti argumenti tipa ako se mogu zaključiti

# .NET
- U C# je ponovo dozvoljen `goto` (moguće skakanje na `switch` labele), ali labele u `break` i `continue` nisu
- `switch` ne dozvoljava propadanje
- Sa `goto` nije moguće uskakanje u neki blok ili iskakanje iz `finally`, a iskakanje iz `try`/`catch` poziva `finally`ć
- Izvođenje osim sa intefejsima nije dozvoljeno kod struktura
- Metodi se razlikuju po tome da li koriste `ref` i `out` ali se ne mogu razlikovati ako jedan koristi `ref` a drugi `out`
- Statički članovi su dostupni samo preko klase
- `internal` pristup samo iz trenutnog assembly-a
- Podrazumevano pravo pristupa je privatno
- Za `++`, `--` i kombinovane dodele potrebna je realizacija i `set` i `get` u svojstvima i indekserima
- Sintaksa nasleđenih indeksera: `tip I.this[...] {...}`

## Greške
- Može da baci izuzetak samo ako su svi konstruktori deklarisani da bacaju taj izuzetak
- "trusted" uopšte ne znači to što je navedeno na prezentaciji iz paketa
- Statički metod sa istim potpisom "sakriva" metod interfejsa koji se svakako mora pozvati preko `Interfejs.metod()`?
- Korisnički izuzeci su provereni izuzeci (nisu ako nasleđuju `RuntimeException`)
- Statički inicijalizator _može_ da baca izuzetak, ako je taj izuzetak neproveren:
```java
public class OO2 {
    static int a;
    static {
        a = 1;
        hmm();
    }
    static void hmm() {
        throw new RuntimeException();
    }
    public static void main(String args[]) {
    }
}
```
- Zar lambda izrazi nisu izrazi koji nakon izračunavanja daju lambda objekat (ne izvršava se sama funkcija, ali se pravi objekat preko kojeg ta funkcija može da se izvrši), i na koji način se to razlikuje od definicije izraza?
- (Niti:4) Metod `run` ne može da baca PROVERENE izuzetke
- (Niti:17) Zašto `citajStanje()` mora da bude `synchronized`?
- (Niti:37) Ako se promenljiva menja unutar tela petlje i koristi kao njen uslov, ali se takođe menja iz ostalih niti, da li je potrebno postaviti je kao `volatile` i zašto? (Jeste, zato što se tako ne kešira vrednost u registrima nego direktno čita iz memorije, što čini da se čita ažurna promenljiva u trenutnoj i ostalim nitima.)
- (Generici:14) Primer iz prezentacije se ne kompajlira:
```java
class G<T> {
	T t;
}

class Arg {
	public int a = 1;
}

public class OO2 {
	public static void main(String[] args) {
		G<Arg> [] gNiz = (G<Arg> []) new Object[10];
	}
}
```
- (C# Tipovi:24) Ne samo interfejsi, i obične klase mogu sadržati `get` i `set` bez tela pristupnika
- (C# Niti:6) `Start()` se poziva kada nit završi...?

## Pitanja
- Da li nam u prva dva ispitna roka može doći u kojoj je verziji Jave uvedeno nešto?
- Šta znači ovo za nadinterfejse i nadklase oko poziva statičke metode?
