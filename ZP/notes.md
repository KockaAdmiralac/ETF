## Matematika
- Fermaova teorema: $a^{p-1} \equiv 1 \pmod{p}$
- Ojlerova teorema: $a^{\Phi(n)} \equiv 1 \pmod{n}$ za uzajamno proste $a$ i $n$
- $\Phi(pq) = (p-1) (q-1)$ za uzajamno proste $p$ i $q$
- Miler-Rabinov algoritam:
    1. Generiše se slučajan broj $a$
    2. $n - 1 = 2^k q$
    3. Ako je $a^q \mod n = 1$ onda je možda prost
    4. Ako je neki od $a^{2^j q} \mod n = n - 1$ onda je možda prost (za $j = 0 ... k - 1$)
    5. Inače nije
    6. Pokrenuti više puta kako bismo bili sigurniji da broj zaista nije prost

## Simetrični algoritmi
- Supstitucija
    - Cezarova šifra
    - Monoalfabetska šifra
        - Ključ je 26! dugačak
        - Nije otporna na statistiku
    - Gausova metoda: česta slova kodirati sa više kodova
        - Učestalosti kombinacija slova ostaju
    - Playfair
        - 5x5 matrica koja počinje ključem a zatim se nastavlja slovima
        - I i J su jedno slovo
        - Originalni tekst se podeli na dva slova
            - Ako se ponovi slovo, kao drugo slovo staviti X
        - Ako su slova u istom redu, šiftovati udesno
            - U istoj koloni šiftovati nadole
        - Ako formiraju kutiju onda ih zameniti sa suprotnim ćoškovima (u istom redu)
    - Vigenere: `chr((ord(key[i]) + ord(key[j])) % 26)`
        - Neke grupe slova nastavljaju da se ponavljaju
        - Autokey: ključ dopunjuj plaintext-om
    - Hill: `c[i] = (k[0][i] * P[0] + k[1][i] * P[1] + ... + k[i][i] * P[i]) % 26`
        - Odrediti inverznu matricu: K^-1 = det(K)^-1 adj(K) mod 26
        - Adjungovana matrica 2x2 je zamena polja na glavnoj i negacija na sporednoj dijagonali
        - det(K)^-1 se određuje tako što se odredi determinanta pa se onda traži $x$ tako da $det(A) x \mod 26 = 1$
        - Validni ključevi su samo oni gde determinanta po modulu 26 (ili kojem već) daje 1
    - Vernam: XOR sa ključem koji se ponavlja
    - One-time pad: `c[i] = m[i] + k[i]`
- Transpozicija
    - Rail fence: ključ je broj redova
    - Row transposition: ključ određuje red kojim se redovi čitaju prilikom šifrovanja
- Produkcioni
    - Rotor mašine: ključ je redosled povezivanja ulaza rotora na izlaze
        - Najniži rotor rotira pri svakom unosu, viši pri punoj rotaciji prethodnog
    - Feistel struktura: B[i+1] = A ^ F(K, B)
        - Konfuzija: supstitucija, statistički neprepoznatljiv rezultat
        - Difuzija: svaki bit izlaza zavisi od svakog bita ulaza i ključa
    - DES:
        1. Generisanje ključa
            1. Odbaci se svaki osmi bit
            2. Permutuje se 56 bita pomoću PC1
            3. Podeli se u dve polovine
            4. Polovine se rotiraju za 1 ili 2 mesta ulevo u svakoj rundi, i onda se od njih bira 24 bita koji se permutuju sa PC2
        2. Inicijalna permutacija
        3. 16 rundi
        4. Zamena blokova
        5. Inverzna inicijalna permutacija
    - SDES
        1. Generisanje ključa
            1. Ima 10 bita
            2. PC1 (10 bita)
            3. Levi i desni se rotiraju za 1 ili 2 ulevo
            4. PC2 (8 bita)
            5. Korak 3 opet
            6. Korak 4 opet
        2. Inicijalna permutacija
        3. Funkcija iteracije
            1. E (4 -> 8 bita)
            2. XOR sa ključem
            3. Podeli se na dva dela pa u S-box (biraju se 0 i 3 kao i 1 i 2 bitovi)
            4. Konkateniraju se pa u permutaciju
        4. Jednostavna permutacija
        5. Funkcija iteracije
        6. Inverzna inicijalna permutacija
    - AES
        1. Generisanje ključa i formiranje stanja
            1. Stanje je 4x4 matrica formirana po kolonama
            2. Ključ od 128 bita postaje 44x32
        2. Inicijalna transformacija
        3. Funkcije iteracije
            1. Byte substitution (S-box)
            2. Shift rows (i-ti red numerisano od 0 se pomera za i redova u levo)
            3. Arithmetic operations over a finite field (nedostaje u poslednjoj rundi)
                - Množi se svaki red sa nekom glupom matricom
                - Množenje sa 2 se radi kao šift samo što ukoliko je ispao bit 1 onda radimo XOR sa 00011011
                - Množenje sa 3 je prvo šift pa XOR sa ovom vrednošću
                - Dodavanje ovih vrednosti se radi kao XOR
            4. XOR with a key
                - Radi se po kolonama
    - SAES
        1. Generisanje ključa
            - Levi nibble sledećeg ključa je L xor g(R) a desni je to ^ R
            - g: zameni levi i desni nibble, primeni S-box na oba i onda xor sa konstantom iteracije
        2. Add round key
        3. Nibble substitution
            - Jedan S-box
        4. Shift row
            - Drugi red rotira ulevo za 1
        5. Mix columns
            - Uzme se svaka kolona i množe se matrice
            - Kada se množi sa 4 prvo se šiftuje za 1 pa proveri pa opet šiftuje za 1 pa proveri
            - Kada se sabira samo se radi XOR
        6. Add round key
        7. Nibble substitution
        8. Shift row
        9. Add round key

## Asimetrični algoritmi
- Jednostrana funkcija: `y = 2^x mod p`
- Post-kvantni algoritmi: problemi matematičkih rešetki, shortest vector problem, closest vector problem
- RSA nije otporan na chosen ciphertext napad, štitimo se tako što nasumično dopunimo poruku pre šifrovanja

## Upravljanje ključevima
- Metode razmene:
    1. Direktna razmena između A i B
    2. KDC daje ključeve
    3. Master-session ključevi - direktno A i B
        - A: N1
            - Ovo nam ne služi ničemu?
        - B: E(Km, Ks || f(N1) || N2)
            - N2 nam služi kako bismo prosto imali neki broj da modifikujemo?
        - A: E(Ks, f(N2))
            - Potvrda da je veza uspešno uspostavljena
    4. Master-session ključevi - KDC
        - A: IDb || N1
            - N1 protiv replay, inače bi napadač mogao da vrati isti ključ kao prošli put
        - KDC: E(Ka, Ks || N1 || E(Kb, Ks || IDa))
            - Ovaj kasniji payload se prosleđuje B
            - Može i KDC da šalje ka A i B
        - A: E(Kb, Ks || IDa)
        - B: E(Ks, N2)
            - N2 nam služi kako bismo prosto imali neki broj da modifikujemo?
        - A: E(Ks, f(N2))
- Trivijalna šema Ralfa Merklea:
    - A: PUa
    - B: E(PUa, Ks)
    - Pošto nema veze između identiteta i javnog ključa, ovo nije otporno na MITM
- Distribucija javnih ključeva:
    1. Javno objavljivanje
        - Povoljno kad ima dosta ljudi koji ovo mogu da provere da li je promenjen
    2. Direktorijum
        - Ista mana kao gore
    3. PKA
    4. CA
        - Sertifikat = E(PRauth, T1 || IDa || PUa)
- Diffie-Hellman:
    1. $q$ je prost broj, $\alpha$ je primitivni koren od $q$
    2. A bira svoj privatni ključ $X_A < q$ i računa $Y_A = \alpha^{X_A} mod q$
    3. B radi to isto
    4. Razmene $Y_A$ i $Y_B$ i izračunaju $K = (Y_A)^{X_B} mod q$ i obrnuto
    - Sigurnost leži u težini diskretnog logaritma
    - MITM: uspostavi komunikaciju sa odvojenim ključevima između A i B

## Algoritmi toka podataka
- RC4:
    - Prvo se S ispuni vrednostima od 1 do 255, onda se uradi shuffle tako što se svaki element zameni nekim od sledećih na osnovu ključa i onda se iz njega biraju vrednosti u svakoj iteraciji sa kojima se radi XOR ulaznog bajta i onda rade zamene u S
    - Način generisanja ključeva u WEP nije bio dovoljno siguran za RC4
    - Ne koristi se jer je otkrivena jedna fundamentalna slabost
- Salsa20:
    - Prvo se radi transformacija ključa pa se onda tim ključem šifruje poruka
        - U generisanje ključa ulazi 256b ključ, 64b nonce, 64b brojač i konstante, a izlazi blok ključa
        - 20 rundi:
            - Blok ključa se rasporedi na određeni način
            - Runde su parne i neparne, parne idu po vrstama a neparne po kolonama, počev od konstante
            - Runda koristi sabiranje, XOR i rotiranje nad 32b rečima
    - Algoritam je efikasan, optimizovan za najčešće arhitekture
- ChaCha20:
    - Drugačija struktura bloka ključa (sigurnost)
    - Drugačije izgleda runda, iste operacije ali različit redosled (sigurnost) i broj rotacija (efikasnost)
    - Parne runde gledaju po dijagonalama
- Generatori slučajnih brojeva:
    - Koristimo seed generisan pravim generatorom slučajnih brojeva (TRNG), koji ulazi u deterministički algoritam nakon toga (PRNG)
    - LKG: $X_{n+1} = (aX_n + c) mod n$
    - BBS: p i q kongruentni sa 3 po modulu 4, $n = pq$, inicijalna vrednost $s$ uzajamno prosta sa $n$ i zatim u svakoj iteraciji $X_i = (X_{i-1})^2 mod n$ i $B_i = X_i mod 2$
        - Spor, pa se koristi za generisanje ključa
    - ANSI X9.17 PRNG: koristi datum, vreme i tri 3DES šifrovanja

## Autentikacija poruka
- Kriptografske heš funkcije:
    - Primene:
        - Lozinke
        - Hashcash/proof of work
            - Merkleovo stablo
        - Detekcija virusa
        - Generisanje pseudoslučajnih brojeva
        - Postkvantne šeme potpisivanja: XMSS, SPHINCS+
    - Osobine:
        1. Nebitna dužina poruka
        2. Izlaz fiksne dužine
        3. Lako izračunljivo unapred
        4. Teško izračunljivo unazad (weak collision resistance)
        5. Teško pronaći koliziju (strong collision resistance)
    - Birthday paradox: treba ti sqrt(365) ljudi da bi imao 50% šansi kolizije rođendana
        - Ako je heš dužine 160 bita, treba $2^{80}$ operacija za pronalaženje kolizije
    - Koji kurac je ovaj SHA algoritam
- MAC:
    - Rešava probleme:
        - Lažnog predstavljanja
        - Izmene sadržaja
        - Izmene redosleda
        - Promene vremena
    - Šifrovanje ne rešava problem detekcije promene poruke niti poricanja slanja

## Modovi funkcionisanja
- Meet-in-the-middle
    - Known plaintext napad: sa jedne strane šifrujemo plaintext a sa druge dešifrujemo ciphertext, pa ih uporedimo
    - 3DES sa K1 i K2, gde se K2 koristi za dekripciju, EDE
- ECB
    - Glup, jer se ponavljaju blokovi
- CBC
    - Izlaz enkripcije povezuje se na XOR iza plaintext-a
    - U prvi XOR ulazi IV
- CFB
    - Prvo se šifruje IV, pa C1, C2...
    - Razlika je u tome da se ne radi enkripcija nad plaintext već nad ciphertext pa se onda radi XOR
    - Postoji jedan šift registar pre enkripcije i birač bitova posle tako da veličina bloka plaintext može da bude različita od veličine bloka koji se enkriptuje
- OFB
    - Izlaz enkripcije se povezuje na ulaz sledeće, za plaintext se radi XOR
    - Ovo nam omogućava nezavisno računanje od primanja teksta
    - Valjda se samo enkripcija radi
- CTR
    - Kao OFB ali se šiftuje vrednost brojača umesto output
- CCM
    - n: dužina nonce
    - q: 15 - n, dužina predstave poruke
    - B0:
        - Prvi bajt: 0 | AData | (len(MAC) - 2) / 2 | q - 1
        - Nonce
        - Dužina poruke
            - Ako povećamo nonce smanjuje se dužina poruke
    - B1..n:
        - Enkodovana veličina pridruženih podataka (2B, ili FFFE 4B, ili FFFF 8B)
        - Pridruženi podaci
        - Nule
        - Sledeći blok ide poruka
    - B0...Bn idu kao OFB povezani tako da se na kraju formira MAC odvajanjem viših k bita
    - CTR0..n:
        - Prvi bajt: q - 1
        - Nonce
        - Brojač (inkrementira se za 1 svaki blok)
    - CTR0..n se enkriptuju odvojeno, MSB iz prvog bloka idu na XOR sa MAC a ostali se spajaju pa idu na XOR sa plaintext
    - Na kraju se spoje ciphertext i MAC
- GCM
    - Proizvoljna dužina IV
    - CTR0 se generiše na osnovu IV i vrednosti 1, ostali se inkrementiraju po modulu 2^s
    - CTR1..n se enkriptuju, XOR sa plaintext, pa onda još jednom XOR sa prethodnim izlazom mult H
    - Poslednji ulaz u mult H je len(Additional data) || len(Ciphertext) (svaki na 8 bajtova)
    - CTR0 se na kraju XORuje sa poslednjim izlazom mult H
    - mult H je množenje sa H u Galois polju, inicijalna vrednost H se dobija enkriptovanjem 0000

## Postkvantni algoritmi potpisivanja
- Lamport/Diffie:
    - f: jednosmerna funkcija
    - g: heš funkcija
    - x: ključ za potpisivanje od 2n vektora
    - y: verifikacioni ključ kao f(x)
    - d: heš poruke g(M)
    - sigma: digitalni potpis kao x[d]
- Winternitz:
    - f, g
    - w: Winternitz parametar za računanje t
    - x: dužine t vektora
    - y: f(x)
    - d: heš
    - b: t delova heša
- MSS:
    - generiše se n privatnih ključeva i iz njih se izvedu verifikacioni pa se nad njima radi stablo heševa
    - javni ključ: koren Merkle stabla
    - d: heš
    - sigma: digitalni potpis Lamport-Diff ili Winternitz
    - i: indeks privatnog ključa
    - potpis: (i, sigma, y, autentikaciona putanja)
    - verifikacija: verifikuje se sigma, y kombinacija, a onda se verifikuje stablo autentikacionom putanjom
    - problemi: veliki ključevi (koristiti PRNG), veličina stabla, pamćenje koji ključevi su iskorišćeni
- XMSS:
    - definitivno se koriste PRNG i seed
    - hiperstablo: više ulančanih stabala, koreni dubljih stabala potpisani prethodnim
        - MSS: 2^256 listova, 256 nivoa stabla, 2^256 + 2^256 - 1 heširanja, kolizija kao sqrt(2^256)
        - XMSS: 16 nivoa od 16 nivoa, 16(2^16 + 2^16 - 1) heširanja, ista verovatnoća kolizije
- SPHINCS+:
    - veliko stablo kako bi mogli da heš funkciju koriste za adresiranje ključeva za potpisivanje ali se kreira samo deo
    - optimizacije ako je potrebno manje potpisa

## X.509
- Sertifikati sadrže:
    - verziju (1, 2, 3)
    - serijski broj sertifikata
    - algoritam za digitalno potpisivanje
    - ime izdavača
    - ime vlasnika
    - vreme važenja
    - informacije o javnom ključu vlasnika (algoritam, parametri, ključ)
    - (v2) jedinstveni identifikator izdavača
    - (v2) jedinstveni identifikator vlasnika
    - (v3) dodatna polja
    - potpis (heš svih polja)
- Povezivanje CA se radi tako što međusobno sebi potpišu javne ključeve
- Certificate Revocation List:
    - Nije toliko skalabilno
    - OCSP, lightweight OCSP
- Ekstenzije:
    - sadržaj: identifikator, kritičnost, vrednost
    - tipovi: informacije o ključevima i polisama, atributi izdavaoca i vlasnika, ograničenja
- PKI infrastruktura:
    - krajnji korisnici
    - repozitorijum sertifikata
    - registracioni autoriteti
    - CRL izdavači
    - sertifikacioni autoriteti (ova dva iznad)

## Zaštita podataka u upotrebi
- Fully Homomorphic Encryption: operacije nad šifrovanim podacima bez poznavanja ključa za enkripciju, nisu još uvek dovoljno efikasne
- Trusted Execution environment:
    - autentičnost izvršnog koda
    - integritet izvršnog stanja
    - tajnost koda, podataka i stanja
    - udaljena atestatacija
- Tehnologije:
    - ARM TrustZone: razdvaja zaštićeni i normalni svet
    - Intel SGX: hardverski zaštićen kontejner na udaljenom računaru
    - Intel TDX: virtuelna mašina
    - AMD SEV: šifruje se VM, pogodno za HPC
    - AMD SEV-SNP: ispravlja slabosti SEV, proizvoljna atestacija
- Udaljena atestacija:
    - vremenski ažurni dokazi
    - opsežne informacije o meti
    - mehanizam od poverenja
    - ne postoji standard (RATS)
- Secure Multi-Party Computation
- Proces atestacije:
    - Proizvođač čipa
    - Vlasnik platforme
    - Vlasnik gosta
- Lanac poverenja:
    - ARK (RSA): potpisuje ASK, sertifikat u KDS
    - ASK (RSA): potpisuje CEK, sertifikat u KDS
    - CEK (ECDSA): jedinstven za svaki čip, omogučava verifikaciju da je od AMD i da ima SEV
    - PEK (ECDSA): generisan od SEV, trajanje određeno vlasništvom nad platformom, povezuje AMD i vlasnika platforme
    - PDH (DH): služi za uspostavljanje master secret između vlasnika platforme i gosta, trajanje kao PEK
- Generisanje master secret:
    - PO šalje PDH
    - GO šalje svoj javni ključ i nonce N
    - Kombinacijom svojih ključeva dobijaju Z
    - Računaju M kao KDF(Z, N) i brišu Z
- Verifikacija sertifikata:
    - VERSION: mora da bude podržan
    - PUBKEY_USAGE: mora da bude postavljen na taj ključ koji očekujemo
    - SIGx_USAGE: mora da bude postavljen na ključ koji ga potpisuje
    - SIGx_ALGO: mora da bude jednak PUBKEY_ALGO od tog ključa što potpisuje
    - SIGx mogu da budu obrnuto
    - SIGx: verifikovati da je potpis ispravan
    - PUBEXP_SIZE i MOD_SIZE moraju da budu 4096 ili 2048 kod ASK i ARK
    - ARK KEY_ID = ASK CERTIFYING_ID

## TLS
- Obezbeđuje tajnost (handshake protokol) i integritet (HMAC sa deljenim tajnim ključem) poruka
- Odvojeni ključevi za šifrovanje od klijenta i servera
- Mogućnost kompresije izbačena u kasnijim verzijama
- Change Cipher Spec protokol: poruka koja kaže da su naredne poruke šifrovane
- Alert protokol: jedna strana obaveštava drugu o neregularnostima
- Vrste razmene ključeva:
    - RSA
    - Fixed DH: javne vrednosti su fiksne i potpisane od CA, pa se dobija isti simetričan ključ (izbačen)
    - Ephemeral DH: javne vrednosti se potpisuju sa RSA ili DSS, dobija se različit ključ
    - Anonymous DH: bez autentikacije i zaštite od MITM (izbačen)
- Handshake poruke:
    - ClientHello (predlog parametara)
    - ServerHello (prihvaćeni parametri)
    - Sertifikat
    - Ako se koristi autentikacija: CertificateRequest
    - ServerKeyExchange (samo ako se koristi DH, šalje javne vrednosti)
    - ServerHelloDone
    - Ako se koristi autentikacija: Sertifikat klijenta
    - ClientKeyExchange (šalje se premaster secret šifrovan javnim ključem ili DH vrednosti, svakako posle može da krene sa šifrovanjem)
    - Ako se koristi autentikacija: CertificateVerify
    - ChangeCipherSpec
    - Finished
    - ChangeCipherSpec
    - Finished
- Generisanje ključeva:
    - master-secret = PRF(pre-master-secret, "master secret", client-random, server-random)
    - sekvenca HMAC-ova koja nam obezbeđuje generisanje svega ostalog (server/client write key/MAC secret/IV)
- Heartbeat protokol: proverava da li je drugi učesnik komunikacije aktivan
- QUIC: postoji

## Autentikacija korisnika
- Replay napad kod Needham-Schreder
- Token, ticket: podaci enkriptovani ključem servera koji se šalju klijentima koji ne mogu da ih čitaju
- TGS: Ticket Granting Server
- Kerberos tiketi sadrže početno vreme i lifetime
- Paziti na to da napadač ne može ponavljanjem neke poruke da dobije pristup servisima
- Svaki korak ima timestamp osim 6, koji vraća TS5 + 1, a tiketi imaju i lifetime
- Koraci komunikacije:
    1. Klijent šalje AS da želi da se autentikuje, kaže mu koji TGS hoće da koristi i timestamp mu služi za inicijalnu proveru vremenske sinhronizacije
    2. AS odgovara sa ticket koji sadrži ključ za komunikaciju između klijenta i TGS, identifikator i adresu klijenta, identifikator TGS i trajanje, i sve to isto van ticket osim identifikatora i adrese klijenta, sve je enkriptovano ključem C
    3. Klijent TGS šalje kojem servisu hoće da pristupi, tiket, i autentikator (svoje ID i AD zajedno sa timestamp protiv replay, enkriptovano)
    4. TGS mu vraća isto kao u poruci 2 samo bez lifetime, IDtgs je IDv, ključ je za komunikaciju sa V i ticket je odgovarajuće izmenjen
    5. Korisnik V šalje ticket i autentikator
    6. V vraća enkriptovano TS5+1 za međusobnu autentikaciju
- Ako postoji više realm-ova, korisnik svom TGS umesto V kaže da hoće da koristi drugi TGS
- Kerberos v5:
    - Nije vezan za DES
    - Authentication forwarding
    - Skalabilna interrealm komunikacija
    - Uklonjeno dvostruko šifrovanje ticket u porukama 2 i 4
    - Uveden renew time
    - Nonce pored timestamp
- SAML:
    - IdP, Principal (klijent), attribute service, data consumer
    - Klijent može da bude MITM pa se radi neko potpisivanje
- OAuth:
    - Klijent pristupa servisu, servis traži od IdP token, radi preusmerenje, traži novi token nakon autentikacije i onda može da pristupa informacijama
    - Nema baš smisla da korisnik radi MITM u ovom slučaju, ali može da se radi i potpisivanje
- RADIUS: ovako radi eduroam, prosleđuje autentikacione zahteve odgovarajućem IdP

## IPSec
- Zaštita na aplikacionom sloju: više šifrovanih sesija
- Zaštita na mrežnom sloju: siguran tunel kroz koji se prosleđuje više mrežnih zahteva
- Zaštita na data link sloju: nema smisla jer je na nivou jednog mrežnog segmenta
- Sesija se zove sigurnosna asocijacija i određena je sa
    - Security Parameters Index (jedinstveno određuje asocijaciju),
    - destinacionom IP, i
    - Security Protocol Identifier (Authentication Header ili ESP)
- SA je jednosmerna
- SPDB: baza sa pravilima koje se primenjuju na SA, a onda se rezultati tih pravila proveravaju u SADB da bi proverili kakvi se sigurnosni parametri koriste
- Authentication Header:
    - U transportnom režimu se ubacuje posle IP zaglavlja, u tunel se dodaje novo IP zaglavlje sa AH iza
    - Next Header kao kod IPv6
    - Payload (izlaz HMAC) i Payload Length
    - SPI
    - Sequence Number kao zaštita od replay napada
    - Zaštićeno je sve desno od AH i nepromenljivi delovi IP zaglavlja
- Encapsulating Security Payload:
    - ESP ima i trejler
    - Zaglavlje ima SPI i Sequence number
    - Payload i Next header su u završetku, s tim što je sledeće zaglavlje originalno IP/TCP/UDP a payload je originalni paket
    - Vrši enkripciju
    - Na kraju je Authentication Data kao izlaz HMAC od šifrovanih podataka
- Za razmenu ključeva u IPsec koristi se IKE
    - Zasnovano na DH, autentikacija pomoću digitalnih potpisa, sertifikata ili unapred razmenjenih ključeva
    - Razmena:
        - HDR, koje sve protokole podržavaju
        - HDR, DH vrednosti, nonce
        - HDR* (zaštićen DH ključem), identifikacija, heš
        - Quick mode: tri poruke sa novim DH vrednostima
            - Ovo se vrši prilikom zamene ključeva
    - IKEv2 je smanjio broj poruka na 4+2

## Blockchain
- Wallet ima heš javnog ključa u base58 kao ID, dnevnik transakcija i par asimetričnih ključeva
- Transakcija: javni ključ, prethodna transkacija, index, koliko se plaća, primalac, digitalni potpis prethodna 4 podatka
- Jedan blok sadrži heš zaglavlja prethodnog bloka, čime se vrši ulančavanje
- Miner računa heševe za blok do određenog broja nula, ako uspe dodaje ga na blockchain i dobija neku kompenzaciju
- Može da dođe do grananja blockchain, ali to se vremenom reši

## Zaštita sistema
- Uljezi:
    - Masquerader: korišćenjem tuđeg naloga pristupa resursu
    - Misfeasor: korišćenjem svog naloga pristupa resursu koji mu nije dozvoljen
    - Clandestine user: zauzima supervizorsku kontrolu pa može da zaobiđe detekciju
- Tehnike upada:
    - Fajl sa šiframa zaštititi heš funkcijama/kontrolom pristupa
    - Različiti načini za isprobavanje šifara... trebalo bi da je logično, verovatno mogu do 5 njih da traže (lako zaustavljivo)
- Detekcija upada:
    - Zašto je dobro... zato što možemo da ih izbacimo, prikupimo informacije i zastrašimo
    - Detekcija neregularnog ponašanja korisnika
        - Ovo slabo radi za misfeasor, a nikako za clandestine user
        - Preko statističkih anomalija, bilo za sve bilo za pojedinačnog korisnika (normalno ponašanje)
        - Preko unapred postavljenih pravila (ispravno ponašanje)
        - Kompromis lažni pozitivi vs. lažni negativi
    - Audit logovi
        - Sistemski ili custom
    - Mera sumnje...
- DDoS:
    - SYN flood, ping of death
    - Direktni ili reflektovani
    - Strategije skeniranja: random, hit list (imamo spisak mašina), topological (hijerarhijska hit lista), local subnet (tražimo mašinu koju možemo da zarazimo iza firewall)
    - Prevencija (polise za iskorišćenje resursa), detekcija i filtriranje, identifikacija izvora radi budućeg sprečavanja
- Maliciozni softveri:
    - virus: zaražava druge programe, pravi kopije sebe
    - crv: izvršava se nezavisno, propagira se drugim računarima
    - logička bomba: okida pri određenim uslovima
    - trojanski konj: deluje korisno ali ima malicioznu funkcionalnost
    - zadnja vrata: dozvoljava neautorizovani pristup nečemu (mogu da budu namerni, debagovanje)
    - eksploatator: koncentriše se na jednu slabu tačku
    - downloader: instalira stvari na mašinu
    - auto-rooter: the fuck
    - kit: kolekcija alata za generisanje virusa
    - spamer: spamuje mejlove
    - flooder: zatrpava računare
    - zombi: biva kontrolisan od gazde
    - keylogger
    - rootkit: dobija administratorski pristup
    - adware: reklamira
    - ransomware
- Faze virusa i crva:
    - neaktivan
    - propagacija: kopira se i podmeće
    - okidanje: čeka na neki događaj
    - izvršavanje
- Struktura virusa:
    - oznaka zaraženosti
    - prvo propagira, izvršava, pa nastavlja
- Klasifikacija virusa:
    - Meta:
        - boot sector
        - file infektor
        - makro
        - multipartiate
    - Strategija:
        - enkriptovani
        - nevidljivi
        - polimorfni
        - metamorfni
- Tehnike zaštite: prevencija, detekcija, identifikacija, uklanjanje (bruh), GD skener
- dI/dt = bIS
    - slow start, fast spread, slow finish

## S/MIME
- Zaglavlja i sadržaj (odvojen od zaglavlja jednom praznom linijom)
- RFC 822 - MIME - S/MIME
- Obavezna MIME zaglavlja: Content-Type, MIME Version, Content-Transfer-Encoding
- Tipovi: text, image, video, audio, application, multipart, message
    - text: plain, rich
    - multipart: mixed (poštuje se redosled pri slanju), paralelni (ne), alternativni, zapakovana RFC 822 poruka
    - message: rfc822, partial, spoljašnje telo
- Kodiranje za prenos: 7 bit, 8 bit (ne moraju biti ASCII), binary (ne moraju biti 80 karaktera), quoted-printable, base64, x-token
- S/MIME funkcije:
    - enveloped data (application/pkcs7-mime; smime-type=envelopedData)
    - signed data (application/pkcs7-mime; smime-type=signedData)
    - clear-signed data (samo potpis se base64 da bi korisnici bez S/MIME mogli da vide; multipart/signed s tim što je potpis application/pkcs7-signature; smime-type=signedData)
    - signed and enveloped data
- Koraci:
    1. Pripremi se MIME entitet
    2. MIME entitet se šifruje, potpiše ili oba i od toga nastane PKCS #7 objekat
        - Šifrovanje se radi isto kao za PGP, priprema se RecepientInfo blok za svakog primaoca, i to sve base64
        - Potpisivanje isto tako
    3. PKCS #7 objekat se formatira u MIME entitet i kanonicizuje
- Sertifikati:
    - Zahtev ide preko CertificationRequestInfo bloka (application/pkcs10-mime)
    - Odgovor može da bude application/pkcs7-mime;smime-type=degenerate
    - Koristi se X.509 hijerarhija sertifikata
- Postupak izbora algoritma:
    1. Ako se zna koji algoritmi su podržani, uzima prvi
    2. Ako je primio neku poruku, uzima iz algoritma korišćenog u poslednjoj poruci
    3. Ako je voljan da rizikuje, onda šalje korišćenjem algoritma koji je bolji
    4. Inače šalje algoritmom koji mora da podrži
