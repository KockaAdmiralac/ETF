## Postkvantni algoritmi za digitalno potpisivanje
- Zašto ovi algoritmi
- Zadatak sa datim x, y, d, odredi sigma (Lamport/Winternitz)
- Koji su problemi sa Lamport-Diffie
- Koje probleme je ispravio Winternitz
- Za date parametre izračunati veličinu ključeva u Lamport
- Kako radi MSS
- Koji su problemi sa MSS i kako ih je XMSS prevazišao
- Broj računanja u Merkleovom stablu vs. hiperstablu

## X.509
- Koje sve informacije imaju u jednom X.509 sertifikatu
- Nešto sa hijerarhijom CA
- Kako funkcioniše povlačenje sertifikata
- Koji su problemi sa povlačenjem sertifikata i kako su ih ljudi zaobilazili
- Čemu služe X.509 ekstenzije, šta sve sadrže i kako se kategorišu
- Nešto o PKI infrastrukturi (neće doći)

## Zaštita podataka u upotrebi
- Šta je homomorfna enkripcija
- Šta je hardver od poverenja
- Šta je udaljena atestacija, koji su joj glavni principi i načini implementacije
- Šta će nam to
- Ko učestvuje u atestaciji i kako izgleda njihov lanac ključeva
- Dat je format AMD SEV sertifikata i šta sve treba da se uradi radi verifikacije
- Kako se generiše glavna tajna u AMD Sev
- Procedure zaštite podataka, atestacije...

## Autentikacija korisnika
- Šta sve mogu da budu kredencijali
- Šta je nedostatak Needham-Schoeder protokola
- Kako su Denning i Neumann ovo rešili
- Čemu služe AS i TGS
- Šta fali onoj šemi sa tri poruke
- Šta fali onoj šemi sa pet poruka
- Kako funkcioniše svaki deo Kerberos v4
- Koliko često se dešavaju koraci u Kerberos v4
- Kako funkcioniše komunikacija između više realm-ova
- Šta je različito u Kerberos v5 (?)
- Koji su koraci autentikacije korišćenjem SAML
- Prepoznati SAML poruke u koracima 1, 3 i 5
- Kako SP zna kom IdP da pošalje zahtev
- Kako SP i IdP znaju da međusobno komuniciraju
- Kako funkcioniše proces autentikacije u OAuth
- Da li zahtev koji ide preko klijenta u OAuth mora da se potpisuje

## IPSec
- Koja je razlika između zaštite podataka da aplikacionom i mrežnom nivou
- Da li ima smisla zaštita podataka na sloju veze podataka
- Šta pružaju Secure VPN i IPsec
- Kako funkcioniše AH u transport i tunnel modu
- Kako funkcioniše ESP u transport i tunnel modu
- Koje su prednosti a koje mane AH u odnosu na ESP
- Kako idu koraci IKE algoritma i u kom se oni režimu izvršavaju
- Čemu služi IKE main a čemu quick mode

## S/MIME
- Koji su MIME tipovi
- Koje nove MIME tipove uvodi S/MIME
- Koja je procedura kako se određuje kojim algoritmom šifrovati podatke u S/MIME
- Kako funkcioniše MIME kodiranje za prenos
- Zašto postoji MIME kanonička forma
- Koje mogućnosti za šifrovanje nam pruža S/MIME
- Kako funkcioniše registracija sertifikata

## Zaštita sistema
- Prepoznaj tip malicioznog softvera
- Prepoznaj tip uljeza
- Koje su faze virusa
- Kako izgleda generalna struktura virusa
- Koji su tipovi virusa po meti napada i po strategiji sakrivanja
- Jednačina za model propagacije virusa
- Koje su tehnike zaštite od malvera
- Šta je DDoS napad
- Koja je razlika između direktnog i reflektovanog DDoS napada
- Šta su gazde a šta sluge kod DDoS napada
- Koje su strategije skeniranja kod DDoS napada
- Navesti tehnike zaštite od krađe fajla sa šiframa
- Navesti tehnike detekcije upada u sistem
- Šta su zapisi osluškivanja

## Web sigurnost
- Čemu služi TLS Alert protokol
- Čemu služi TLS Change Cipher Specification protokol
- Čemu služi TLS Heartbeat protokol
- Navesti poruke koje se razmenjuju kod TLS Handshake protokola sa i bez autentikacije
- Koje sve vrste razmene ključeva postoje kod TLS, navesti njihove prednosti i mane
- Kako se formira pre-master secret
- Kako se formira master secret
- Kako se formira ostali kriptografski materijal potreban za razmenu
- Šta je fora sa QUIC

## Blockchain
- Šta je uopšte fora sa decentralizacijom
- Šta sve sadrži jedna transakcija
- Kako se formira transaction hash
- Šta je potrebno sve da jedan rudar uradi kako bi izrudario blok
- Kako se razrešava problem kada se blockchain razgrana
