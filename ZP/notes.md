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
    - ...
- OFB
- CTR
- CCM
- GCM
