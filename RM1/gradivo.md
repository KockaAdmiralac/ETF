# Uvod
- OSI slojevi:
    1. Physical: Habovi, ripiteri
    2. Data Link: Ethernet, Wireless, PPP - MAC adrese - Svičevi, bridževi - okviri
    3. Network: IP - Ruteri - paketi
    4. Transport: TCP, UDP - poruke
    5. Session: RPC, SQL
    6. Presentation: Predstavljanje i konverzija podataka (JPEG, ASCII, MPEG, HTML)
    7. Application: Razmena podataka između aplikacija (HTTP, SSH, FTP)
- TCP/IP: 5, 6 i 7 su isti sloj (Application)

# Data Link
- Funkcije:
    - Framing
    - Media Access Control
    - Detekcija i korekcija grešaka
    - Pozdanost (potvrda prijema)
- Detekcija greške:
    - Parity bit
    - CRC
    - Internet Checksum
- Korekcija greške:
    - 2D bitska parnost
    - Hamingov kod
- Topologije:
    - point-to-point
    - ring
    - bus
    - star
- TDMA, FDMA, CSMA/CD, CSMA/CA
- Slotted ALOHA: Svako šalje u određenom vremenskom intervalu
- Pure ALOHA: Svako šalje kad god hoće

# Ethernet
- Podslojevi:
    - Logical Link Control: Multipleksiranje i enkapsulacija protokola višeg nivoa (zajedničko za sve L2 LAN i MAN tehnologije)
    - Media Access Control: Pristup medijumu (CSMA/CD), adresiranje, kontrola greška (CRC)
- Kolizija:
    - Kada dođe do kolizije, uređaji emituju JAM signal
    - Backoff:
        - Maksimalni broj slanja paketa: $N = 16$
        - Slučajan broj $K$ iz skupa $0, 1, 3, 7, 15, ... 2^N-1$
        - Čeka se $K \cdot t_s$
    - Kolizija se može detektovati samo dok se okvir šalje na mrežu
    - Propisuje se minimalna veličina okvira ($L_{min}$) i maksimalno rastojanje u mreži jer okvir mora da ode do najudaljenijeg uređaja u mreži i da se vrati kako bi se detektovala kolizija
- Bitsko vreme ($t_b$): recipročna vrednost protoka ($B$)
- Ripiter: sadržaj na jednom prosleđuje na drugi port kako bi se povećalo maksimalno rastojanje mreže (ograničenje zbog kolizije i dalje postoji)
- Slot-time ($t_s$): Vreme potrebno da se okvir minimalne veličine pošalje na mrežu ($t_s = L_{min} t_b = \frac{L_{min}}{B}$)
- Za veće protoke, manje je bitsko vreme pa bi minimalna veličina okvira morala da bude prevelika, zato se umesto toga smanjuje maksimalna veličina mreže
- Adresiranje: unicast, multicast, broadcast
- MAC adresa: 3 bajta za Organizational Unique Identifier, 3 bajta jedinstveno dodeljenih od strane proizvođača
- Format okvira:
    - Preamble (7B): Naizmenične nule i jedinice
    - Start of Frame Delimiter (1B): 10101011
    - Destination (6B)
    - Source (6B)
    - Type/Length (2B): Tip L3 paketa ili dužina podataka, vrednosti do 1500 su dužina, od 600h su tip
    - Data (46B-1500B): Popunjava se praznim bajtovima ako je kraće
    - Frame Check Sequence (4B): Zbog CRC
- Razmak između okvira: $96 t_b$, jer okviri ne smeju da se spoje i jer elektronika mora da pređe u stanje prijema
- Princip rada bridža:
    - Forwarding: Okvir se propušta ukoliko bridž zna na osnovu bridžing tabele da se on nalazi na drugom portu
    - Filtering: Okvir se ne propušta ukoliko bridž zna na osnovu bridžing tabele da se on ne nalazi na drugom portu
    - Learning: Bridž pamti u bridžing tabelu na kom se portu nalazi računar sa MAC adresom na osnovu izvorišnog dela paketa
    - Flooding: Ako bridž ne zna na kom se portu nalazi računar sa MAC adresom odredišta, prosleđuje ga na sve ostale portove
    - Aging: Posle nekog vremena (tipično 2 minuta), MAC adrese iz bridžing tabele se zaboravljaju jer su računari mogli da pređu na drugi segment u međuvremenu
- Zbog tog što greška na koaksijalnom kablu ili samo jednom konektoru može da celu mrežu prekine na bus topologiji, prelazi se na zvezdastu topologiju i ripiteri bivaju zamenjeni habovima (višeportnim ripiterima)
- Svi ti uređaji se ne koriste, jer postoji pametan hab i višeportni bridž pod imenom svič
- Ethernet standardi:
    - 10BASE-T: UTP kablovi do 100m
- Full Duplex, za razliku od Half Duplex, dozvoljava slanje okvira u oba smera jer su razdvojene parice za slanje i primanje
- Učitavanje okvira:
    - Store and Forward: Prima se ceo okvir i proverava se FCS
    - Fragment Free: Počinje se prosleđivanje nakon prvih 64 bajtova (zbog kolizije pri radu u Half Duplex modu)
    - Cut-Though (Fast Forward): Prosleđivanje čim se primi odredišna MAC adresa
- Auto-negotiation: Svič i povezan uređaj uspostavljaju vezu na najvećoj mogućoj brzini koju podržavaju
- Simetrično prosleđivanje je kad su izvorišni i odredišni port okvira iste brzine, ako nisu, mora da se koristi Store and Forward

# Spanning Tree Protocol
- Bridge ID(8B): Priority(2B) MAC(6B)
- Port Cost: Što je veća brzina, to je manja cena
- Path Cost: Suma svih Port Cost
- Bridge Protocol Data Unit poruke:
    - Configuration BPDU: Emituje se kad se određuje root bridge i Path Cost (na osnovu koga se određuju root portovi)
    - Topology Change Notification
    - Topology Change Acknowledgement
- Pri određivanju root portova, ako više portova dobiju istu vrednost Path Cost bira se onaj port koji je dobio Configuration BPDU od sviča sa manjim ID
- U stacionarnom stanju Configuration BPDU (Hello BPDU) se emituju svake dve sekunde
- Konvergencija (dodavanje ili uklanjanje veza):
    - Kad se detektuje da Path Cost na tom portu više nije najbolji, port prelazi u blocking stanje
    - Max Age tajmer je 10 Hello BPDU što je vreme čekanja dok ne krene ponovno uspostavljanje STP
    - Forward Delay je 15 sekundi što je dodatno vreme čekanja da sve informacije propagiraju svuda
    - Tajmeri se sinhronizuju preko Configuration BPDU poruka
- Stanja portova:
    - Blocking: Ne prenose se podaci, prihvataju se BPDU
    - Listening: Čeka se Forward Delay, ne prenose se podaci, BPDU se prihvataju i šalju
    - Learning: Čeka se ponovo Forward Delay, podaci se koriste samo kako bi se popunila bridžing tabela jer nije dobro da dođe do flooding tik nakon uspostavljanja mreže, BPDU idu normalno
    - Forwarding: Sve okej
- Prekid na uređaju:
    - Šalje se TCN BPDU root sviču
    - Root svič šalje Configuration BPDU sa TCN flegom
    - Svi svičevi preračunavaju stanje portova i smanjuju Aging vreme na 15 sekundi
    - Nema konvergencije
- Prekid na sviču:
    - Može da se detektuje preko prekida veze ili nedostatka Hello BPDU (20 sekundi)
    - Listening + Learning (+ 10 Hello BPDU) = 30 (50) sekundi konvergencije
- STP opcije:
    - EtherChannel: Više paralelnih veza između svičeva
    - PortFast: Konfiguriše se na portovima sa kranjim uređajima kako ne bi dolazilo do TCN BPDU
    - BPDU Guard: Na pristupnim portovima se ne očekuju BPDU okviri, zabranjuje se ako se prime
    - Root Guard: Na portu se zabranjuje BPDU sa boljim Bridge ID
- RSTP:
    - Tipovi veza: link (P2P - između svičeva, Shared - preko deljenog segmenta), edge (između svičeva i hostova)
    - Nove vrste portova: alternate (zamena za root port), backup (zamena za designated port, ne koristi se)
    - Izbačeno Listening stanje
    - Povećan Port Cost
    - Koristi PortFast mehanizam na edge vezama
    - Koristi 3xHello
    - Proposal i Agreement (šalje RP)
    - Learning je kratkotrajno

# VLAN
- Statička konfiguracija (hardkoduje se na sviču) ili dinamička (na osnovu nekog parametra)
- Trunk link:
    - Na trank vezama dodaje se VLAN ID (0 do 4095)
    - Access port i trunk port, poklapaju se na obe strane veze
- Različiti VLANovi se povezuju preko rutera
- Posebno STP za svaki VLAN

# WLAN
- Ne može se detektovati kolizija, zahteva se slanje potvrde za uspešan prijem okvira (Positive Acknowledgement), CSMA/CA
- Ad-hoc (IBSS) i infrastrukturni rešim (BSS, ESS)
- Beacon okvir: SSID i MAC adresa AP kako bi mreža postala vidljiva
- Povezivanje:
    - Usaglašavanje podržanih standarda: Probe Request, Probe Response
    - Autentikacija: Authentication Req/Res
    - Učlanjivanje: Association Req/Res
- Power over Ethernet: 12V preko UTP kablova preko kojeg može da se napaja AP
- Frekvencijski domen širine 20/40MHz, kanali razdvojeni za 5MHz
- Susedni AP moraju da koriste različite i međusobno udaljene kanale
- Skeniranje:
    - Pasivno: Čeka se beacon
    - Aktivno: Šalje se Probe Request za sve AP
- Okvir:
    - Control (2B): Sadrži "To DS" i "From DS" polja
    - Duration (2B): Network Allocation Vector
    - Adr1, Adr2, Adr3 (6B)
        - Source Address: izvorište
        - Transmitter Address: izvorište || AP
        - Receiver Address: odredište || AP
        - Destination Address: odredište
- CSMA/CA:
    - Centralizovana koordinacija: AP proziva uređaje (može samo u infrastrukturnim mrežama)
    - Distribuirana koordinacija: Uređaji se nadmeću
- DCF:
    - Ako je medijum slobodan, čeka se DIFS (50us) pa se šalje okvir
    - Čeka se DIFS, pa se čeka $R = rand(0, CW) \cdot ST$ (slot time, 20us), CW se eksponencijalno povećava sa pokušajima
    - Ako se medijum zauzme tokom backoff, backoff se pauzira dok se ne oslobodi ponovo, tada se čeka DIFS pa nastavlja
- Prenos u dva koraka:
    1. Data
        - Čeka se Short Inter Frame Space, 10us
    2. Acknowledgement
- Prenos u četiri koraka
    1. Request To Send
        - Čeka se SIFS
    2. Clear To Send
        - Čeka se SIFS
    3. Data
        - Čeka se SIFS
    4. Acknowledgement
- Sigurnost:
    - Wired Equivalent Privacy
        - 64 bita kljuć. 40 se koristi za šifrovanje
        - Proizvođači pribegli rešenjima poput sakrivanja SSID i filtriranje MAC
    - Wi-Fi Protected Accesss (2)
        - Dinamička razmena ključeva, username/password (802.1x)
        - WPA2 uvodi AES

## WAN
- Circuit Switched
    - Zakup i eksluzivno korišćenje permanentnih veza
- Packet Switched
    - Stare: ATM, Frame Relay
    - Nove: L2VPN, L3VPN
    - Povezivanje na pristupnu tačku ISP
- Modemi se koriste za DA i AD transformacije
    - voiceband: povezivani preko telefonske linije, male brzine, prebacivali su bitove u zvuk
    - broadband: modulišu signal
        - Digital Subscriber Line: SHDSL (2/2), ADSL (8/1), VDSL (52/16), splitter
        - Kablovski modemi: preko kablovskih operatora, brzine slične DSL
- Channel/Data Service Unit: Telekom produži svoju mrežu do CSU/DSU i tu ima veća brzina, skupo
- WiiMAX 802.16 za bežično povezivanje na širokim rastojanjima
- PPP: Point-to-Point Protocol
    - L1: prenos signala preko serijske veze, sinhrona ili asinhrona
    - L2: Link Control Protocol (uspostavljanje veze, pregovaranje o konfiguraciji), Network Control Protocols (interfejs prema L3, pregovaranje o konfiguraciji mrežnog sloja)
    - Okvir:
        - Flag(1): Uvek 01111110, zbog ovoga se veštački dodaje jedna nula na svakih pet jedinica u podacima a prijemnik ih izbacuje
        - Address(1): Ne koristi se, uvek 11111111
        - Control(1): Ne koristi se, uvek 00000011
        - Protocol(2): Identifikacija L3 protokola, ako se dogovore može i 1 bajt
        - Data(?): Podrazumevani maksimum je 1500 bajta
            - Dalje se u LCP deli na
                - Code(1): tip okvira
                - Identifier(1): uparivanje Request/Reply
                - Length(2): Ukupna dužina okvira
                - Data: ostalo
            - Može još da se deli
        - FCS(2/4): CRC
    - LCP: nezavisan od L3 protokola
        - uspostavljanje, održavanje i raskidanje
        - pregovori
        - kontrolne opcije
        - usklađuje ograničenja u veličini okvira
        - detektuje greške u konfiguraciji i linku
        - Configure Request/Ack, NCP konfiguracija, Echo Request/Reply, razmena podataka pa Terminate Request/Ack
    - Opcije: autentikacija, kompresija, multi-link povezivanje, detekcija grešaka, callback podrška
    - Autentikacija: Password Authentication Protocol i CHAP
        - PAP šalje lozinku u čistom tekstu na početku sesije, druga strana proverava lozinku i korisničko ime
        - CHAP: Challenge (vreme i slučajni podaci), Response (dodata lozinka pa primenjen MD5), Accept/Reject
    - Kompresija: Predictor (predviđa se sekvenca, tabela čestkih sekvenci), STAC (LZ tip), problem prenosa komprimovanih podataka
    - Multilink: Više fizičkih se spajaju u jednu logičku vezu, datagram se deli na delove fiksne veličine
    - Link Quality Monitoring: Ako ima backup veza, ona se aktivira kad je procenat grešaka veći od konfigurisanog
    - Callback: Klijent inicira poziv, zahteva povratni poziv, server inicira povratni poziv prema klijentu na bazi konfigurisanih parametara
    - NCP
        - Drajveri za svaki od mrežnih protokola, slična uspostava veze kao LCP
        - Kompresija TCP/IP zaglavlja, moguće smanjenje na samo 3 bajta

# IP
- Ruteri gledaju okvire na L3 i menjaju adrese na L2 nivou
- Connectionless: Pošiljalac ne zna da li primalac postoji, da li je paket stigao i da li može da ga pročita, primalac ne zna kad će paket da stigne
- Media Independent, Best Effort (Unreliable), ne garantuje se redosled
- IP paket:
    - VERS(0.5): IPv4 ili IPv6
    - HLEN(0.5): Dužina zaglavlja u rečima od 4B
    - Type of Service(1):
        - IP Precedence: 3 bita za prioritet, ostali za način tretiranja
        - DiffServ Code Point: 6 bita za klasu saobraćaja i prioritet
    - Total Length (2): Ukupna veličina IP paketa u bajtovima, uključujući zaglavlje
    - Identification(2): Jedinstveni identifikator paketa
    - Flags(0.5): MF (postavljen kad fragment nije poslednji), DF (postavljen kad se zabranjuje fragmentacija)
    - Fragement Offset(1.5): Redosled fragmenta za defragmentaciju
    - Time to Live(1): Petlje su tehnički moguće, pa se postavlja TTL, i smanjuje na svakom hopu
    - Header Checksum(2): Prvi komplement sume reči od 16b celog zaglavlja
    - Protocol(1): L4 protokol
    - Options i Padding: Eventualno testiranje, dopuna do pune reči
- Fragmentacija:
    1. Dužina svakog dela na koji se niz bajtova deli mora biti umnožak od 8 bajtova osim poslednjeg
    2. Dodaju se zaglavlja pred svaki podatak, menjaju se Fragment Offset, MF, HLEN, Packet Length i Checksum
    3. Fragmentirani IP paket se može ponovo fragmentirati
    4. Pri ponovnom spajanju fragment se prepoznaje po Fragment Offset != 0 || MF
- Klase: Dele se na A, B, C (korisnici), D (multikast), E (eksperimentalno), svaka zauzima po pola ostatka (AAAAAAAABBBBCCDE)
- Adrese dodeljuje IANA (nasleđuje InterNIC) prema regionima: RIPE, ARIN, APNIC, LACNIC, AfriNIC
- Privatni opsezi:
    - 10.0.0.0/8
    - 172.16.0.0/12
    - 192.168.0.0/16
- Ostali rezervisani:
    - 0.0.0.0/8 (default)
    - 127.0.0.1/8 (loopback)
- Subnet: Izjednačava neravnotežu u klasama
- Maska: Da bi se dobio subnet iz IP adrese, uradi se AND sa maskom (takođe dostupna CIDR notacija)
- Adresa podmreže je prva adresa u opsegu, brodkast adresa je poslednja
- Variable Length Subnet Mask: Korišćenje maski različitih dužina u jednoj mreži
- Jedan LAN, VLAN, itd. moraju da pripadaju jednoj IP mreži
- Supernetting: Agregacija susednih mreža u jednu

# Rutiranje
- Statičke rute su ručno podešeni redovi u tabeli rutiranja
- Podrazumevana ruta se koristi kad nijedna druga ruta nije pronađena u tabeli
- Pri rutiranju koristi se najspecifičnija ruta (najveća maska koja odgovara)
- ARP:
    - Request: Ko ima IP, nek pošalje MAC - šalje se na broadcast MAC
    - Reply: Ja imam IP, evo ti MAC - šalje se na unicast MAC pošiljaoca
    - Identifikuju se preko Protocol polja Ethernet okvira
    - Sadrži IP i MAC pošiljaoca i IP primaoca, iako se možda ti podaci mogu izvući iz ostalih nivoa
- ICMP:
    - Grupe: Error, Query (Request/Reply)
    - Vrste:
        - Destination Unreachable:
            - Can't fragment: Neki ruter ne može da fragmentira paket zbog Don't Fragment flega
            - Network Unreachable: Ruter nema mrežu u tabeli
            - Host unreachable: Ruter mreže nema MAC adresu u kešu i preko ARP se niko ne odaziva
            - Protocol unreachable: L4 protokol kome treba proslediti poruku nije ispravno konfigurisan
            - Port unreachable: Aplikacija na portu ne postoji
        - Time Exceeded: Istekao TTL
        - Redirect: Ruter obaveštava uređaj da postoji bolja ruta (od, recimo, podrazumevane)
        - Echo Request/Reply: Ping
