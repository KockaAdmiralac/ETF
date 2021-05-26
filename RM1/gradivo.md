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
- STP je protokol trećeg nivoa?
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
    - Čeka se DIFS, pa se čeka $R = rand(0, CW) \cdot ST$ (slot time, 20us, vreme između dve najudaljenije tačke u mreži?), CW se eksponencijalno povećava sa pokušajima
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

# Protokoli rutiranja
- Interni (unutar jednog AS):
    - Distance Vector: RIP, IGRP
    - Link State: OSPF, IS-IS
    - Hibridni: EIGRP
- Eksterni: BGP
- Uspostavljanje ruting tabele mora da bude: potpuno, konzistentno, optimalno, adaptivno
- Autonomni sistem: organizaciona celina koja je na tehničkom nivou usaglašena, obično jedan ruting domen ali može i više
- Distance Vector:
    - Ruteri saznaju distancu do neke mreže (metrika) i next-hop do te mreže
    - Poznaju samo susedne rutere
    - Rute se periodično razmenjuju (na 30s čak iako nema promena)
    - Konvergencija:
        - Uspostavljanje stabilnog (tabele se ne menjaju) i konzistentnog (rute su ispravne) stanja
        - Zavisi od brzine propagacije routing update i računanja ruta u ruting tabelama
        - Tokom konvergencije može nastati nekonzistentno stanje (odsečene veze, petlje)
        - Count-to-Infinity: Mreža se otkači, ruter sa kojeg nije otkačena javi da ima rutu, ruter sa koga jeste ponovo emituje tu vrednost pa se na B poveća metrika itd.
            - Maksimalna, nevalidna, vrednost metrike je 16
        - Metode zaštite od petlji:
            - Route Poisoning: routing update kad postane nedostupna sa beskonačnom metrikom
            - Split horizon: nikada se ne oglašava ruta na interfejs sa koga je pristigla
                - Poison Reverse: Ako se desi Route Poisoning ipak šaljemo nazad tu istu rutu
                - U Poison Reverse se vraćaju podaci preko Triggered update
                - Redudantne veze neće odstupiti od ovog pravila ali neće ga baš ni sprovesti
            - Holddown Timer: čeka određeno vreme dok se propagira kroz mrežu nevalidna ruta, ako za to vreme stigne nova ruta ignoriše se
- Link State:
    - Saznaje se cela topologija mreže (preko Link-State Advertisements)
    - Rute se razmenjuju samo pri promeni topologije
    - Nakon pravljenja Link-State Database rekonstruiše se mreža, Shortest Path First računa putanju i pravi ruting tabelu
    - Link state = informacije o interfejsima rutera
    - LSA razmenjuje informacije o povezanim linkovima i susedima
    - Flooding = intenzivna razmena LSA
    - Deljenje na oblasti kako bi se flooding dešavao samo na tom ograničenom nivou, sve periferne povezane na centralnu
    - Konvergencija je brza, ali zahteva više memorije, CPU vremena i propusnog opsega
    - U stabilnom stanju prenose se poruke za održavanje susedstva
- Classful ruting protokoli:
    - Ne sadrže maske, dužina na osnovu konfiguracije
    - Autosumarizacija: agregira sve IP mreže u /24, /16 ili /8 (A, B ili C)
    - Classless ruting protokoli imaju promenljivu dužinu maske, oni se zapravo koriste
- Metrike:
    - Hop count
    - Bandwidth
    - Cost (proizvoljna cena)
    - Delay
    - Load
    - Reliability
- Load Balancing:
    - Više putanja do određene mreže sa istom metrikom pa se obe čuvaju u ruting tabeli
    - Koriste se radi raspoređivanja opterećenja i boljeg iskorišćenja propusnog opsega
- Administrativna distanca:
    - Kad se porede metrike različitih ruting protokola
    - Svaki protokol ima svoju AD, koristimo rutu sa najmanjom AD
- RIP (L4? L5?):
    - RIPv1:
        - AD: 120
        - Classful
        - Metrika: Hop count, max: 16
        - RIP poruke se prenose kao UDP poruke na portu 520
        - Dva koraka:
            - RIP Request: navodi se mrežna adresa za koju se traže rute i šalje se na broadcast
            - RIP Response: obično se odgovara celom ruting tabelom, sa po 25 ruta u jednoj poruci, šalje se na unikast adresu rutera
    - RIPv2:
        - Classless
        - RIP Request šalje na multikast na kojem slušaju svi RIPv2 ruteri
        - Zajednički ključ ili niz ključeva (razmenjuju se sa MD5, periodično menjaju indeks)
    - Format:
        - Version
        - Address Family Identifier (= 2 za IP adrese)
        - IP Address: adresa na koju se odnose rute
        - Subnet mask: koristi se samo u RIPv2
        - Next-hop: samo u RIPv2
        - Metric: hop-count 1-16
    - Prednosti: jednostavni, nisu zahtevni po performanse, malo zauzeće linka za male mreže
    - Mane: Metrika je loša, propagacija nije brza, spora konvergencija
- IS-IS AD je 115
- OSPF (L4?):
    - AD: 110
    - OSPF podaci idu u IP poruku sa protokolom 89, na multikast za AllSPFRouters ili AllDRouters (slušaju samo OSPF ruteri)
    - Hello protokol:
        - Da bi se uspostavila veza mora da bude ista IP mrežna adresa i da pripadaju istoj oblasti
        - Na svakih 10s (preko Ethernet) se oglašavaju Hello poruke, nakon 4 propuštene veza se prekida
        - Autentikacija i flegovi
        - Koraci:
            - Down: početno stanje
            - Init: spremni za slanje
            - 2-way: uspostavljeno susedstvo, u Seen polju je vraćen RID i usaglašeni parametri - u ovom stanju nisu OSPF susedi
            - Veći nivo bliskosti: Adjacency
        - ExStart: Ruter sa većim RID je master, koji zadaje sequence number
        - Exchange: šalju se Database Description paketi sa opisom podataka, sequence number se povećava
        - Loading stanja:
            - LSR: Master kaže koji mu podaci fale
            - LSU: Slave odgovara sa tim podacima
            - LSAck: Master kaže hvala
            - Full: Gotovo
    - Loopback interfejs je logički interfejs sa proizvoljnom IP adresom i maskom koji je uvek aktivan i učestvuje u oglašavanju
    - Router ID: Najveća IP adresa loopback interfejsa ili ako ne postoji fizičkog interfejsa
    - Susedstvo:
        - Nije dobro da bude svako sa svakim sused (Adjacency) pa se bira designated router i njegov backup
        - Prioritet 0-255, 255 je najbolje, 0 ne učestvuje u izboru, razmenjuje se kroz Hello poruke
        - Ako dva rutera imaju isti prioritet gleda se ruter sa većim RID
        - Novododati ruteri ne menjaju DR i BDR da bi se smanjio flooding, već se DR i BDR menjaju samo kad prestanu da rade (ruter, interfejs ili OSPF)
    - AllDRouters služi da LSA paket prvo stigne do DR i BDR a AllSPFRouters kada DR šalje svim ostalim
    - Cena veze se izvodi kao 10^8/bandwidth, cena putanje je zbir svih cena na putanji
    - Serijske veze imaju 1544kbps, iako pravi bandwidth može da bude manji, zato moramo da postavimo pravu metriku na ruteru
    - Oblasti:
        - Area 0 (Transita Area, Backbone Area)
        - Ruteri:
            - Area Border Router (između oblasti)
            - Autonomous System Boundary Router (između OSPF i nečeg drugog)
            - Internal Router (pripada samo jednoj oblasti)
            - Backbone Router (pripada centralnoj oblasti)
        - LSA:
            - Router (1): generišu svi ruteri, daju informacije o svim interfejsima
            - Network (2): generiše DR, oglašava ostalim ruterima mrežu
            - Summary (3, 4): agregira sve IP mreže jedne oblasti i kroz Area 0 šalje drugim ABR, a može i da bude LSA koji ASBR oglašava za svoje interfejse
            - External (5): dolazi spolja, može da se na metriku drugog ruting domena dodaje OSPF metrika ili da se ne dodaje
        - Vrste oblasti:
            - Standard Area: prihvata sve LSA, unutar je Router i Network LSA, Backbone je uvek Standard
            - Stub Area: ne prima External LSA, sadrži samo Router i Network LSA, ima podrazumevanu rutu ka ostatku, na ruterima je Stub fleg
            - Totally Stubby Area: ne prima ni External ni Summary LSA, ostalo kao Stub
        - Ako je jedna periferna oblast povezana na drugu a ne na centralnu, dodajemo virtuelni link ka centralnoj
            - Može i između dva dela centralne oblasti ako ne postoji fizička veza između njih
- Redistribucija ruta:
    - Connected rute su obuhvaćene konfiguracijom ruting protokola, sve ostale su eksterne
    - Na graničnim ruterima se konfiguriše redistribucija ruta, tako da RIP domenu javlja OSPF a OSPF RIP

## Transportni sloj
- Port:
    - Identifikuje aplikaciju na uređaju, kao što Protocol Type identifikuje protokol 3 ili 4 nivoa
    - Well-known: 0-1023
    - Registered: 1024-49151
    - Private: 49152-65535
- Socket: Identifikuje aplikaciju na mreži, sadrži IP, identifikaciju protokola i port
- Dodatne funkcije:
    - Uspostavljanje veze
    - Pouzdan prenos
    - Održavanje redosleda segmenata
    - Kontrola toka

## UDP
- Samo osnovne funkcije, connectionless message-stream
- Zaglavlje:
    - Source i Destination port
    - Length
    - Checksum: Prvi komplement sume UDP zaglavlja, podataka i pseudo-header
    - Pseudo-header: Izvorišna i odredišna IP adresa (donekle se krši princip razdvajanja slojeva), identifikacija UDP protokola (17) i dužina UDP paketa
- Jednostavne aplikacije kad nije bitna pouzdanost, real-time aplikacije, malo kašnjenje i mala varijacija kašnjenja (jitter)
- RTP: Real-Time Trasport Protocol, dodatne mogućnosti podsloja UDP, serijalizacija, baferovanje, kontrola jitter

## TCP
- Sve dodatne funkcije, veće opterećenje, byte-stream
- Point-to-Point: Uvek između dva uređaja
- Full-Duplex: U dva smera, čak i kada se aplikativni podaci prenose u jednom smeru u drugom idu kontrolni
- Segmentacija: Deli veće celine ili spaja manje u segmente maksimalne veličine MMS (podrazumevano 536B, definiše se pri uspostavljanju)
- Zaglavlje:
    - Source port, destination port, Checksum kao kod UDP
    - HLEN: 4 bita (ukupna dužina u jedinicama od 4B)
    - Window Size: broj bajtova koji se mogu poslati pre nego što se čeka na potvrdu
    - Options
    - Sequence Number: inicijalno slučajno izabran, inkrementira se
    - Acknowledgement Number: potvrda prijema niza bajtova, jednak sledećem SEQ koji se očekuje
    - Flags:
        - SYN: inicijalizuje SEQ
        - ACK: AN je validno
        - FIN: poslednji segment, završetak konekcije
        - PSH: momentalna predaja aplikaciji bez baferovanja
        - URG: Urgent Pointer polje je validno
        - RST: resetovanje konekcije
- Three-way handshake:
    - Šalje se SYN i prvi SEQ (Active Open)
    - Šalje se ACK, ACK = SYN+1, u istoj poruci šalju se i SEQ i SYN kako bi uspostavio sesiju i u drugom smeru (Established)
    - Potvrda u drugom smeru
- Raskidanje: FIN, ACK
- Timeout potvrde je round trip time koji se procenjuje na osnovu starog RTT i formule, puta uvećanje b
- Radimo višestruki ACK ako nam fali neki paket
- Window:
    - Ukupan broj bajtova koji se šalje pre čekanja na potvrdu
    - U njega se uračunavaju bajtovi koji čekaju na potvrdu i oni koji su spremni za slanje
    - Veličina se dogovara pri uspostavljanju veze, može da se smanjuje na zahtev primaoca ili povećava ako nema grešaka
- Kontrola zagušenja:
    - Algoritmi: Slow Start, Congestion Avoidance, Fast Retransmit, Fast Recovery
    - Advertised Window: Inicijalna vrednost prozora
    - Congestion Window: Postepeno se povećava prozor do maksimalne vrednosti (AD), ako se potvrđuje svaki segment onda je eksponencijalno
    - Slow Start: Ako dođe timeout, ponavljamo CW=1
    - Congestion Avoidance: Ograničavamo eksponencijalni rast a posle toga idemo linearno, sshtresh se smanjuje za polovinu poslednje vrednosti kad dođe timeout
    - Fast Retransmit: Ponovno slanje segmenta pre timeout, tek ako dođe 3 dupla ACK
    - Fast Recovery: Ako su najmanje 3 segmenta uspešno stigla, idemo direktno u Congestion Avoidance bez Slow Start
- QUIC: HTTP preko QUIC, koristi UDP, može da multipleksira veze, zadržava se veza i prilikom promene IP

## Aplikativni sloj
- HTTP: Persistent i Non-Persistent, Stateless i Stateful
- FTP: Kontrolna konekcija i konekcija za podatke, 7-bitni ASCII tekst za zadavanje komandi

## DNS
- Zona: Deo stabla domena, pripada jednoj celini, delegacija zona
- Primarni DNS server: Definisana zona za neki domen
- Sekundarni DNS server: Periodično preuzima zonu od primarnog
- Autoritativni DNS server: Primarni i svi sekundarni DNS serveri
- Rekurzivni upit: Klijent pita servera, dobija pun odgovor
- Iterativni upit: Pita root gde je rs, pita rs gde je ac, ... ako ne znaju celu domenu da razreše
- Record: Name, TTL, Class (uvek IN), Type (SOA, NS, MX, A, AAAA, PTR, TXT...), Value
    - SOA: Start of authority (naziv primarnog DNS servera, email adresa admina (@ se zamenjuje tačkom), serijski broj zone (za diff), refresh, retry, expire, minimum TTL)
    - NS: DNS server domena
    - A: Glue record, ako se koristi naziv za NS mora da postoji i IP adresa koja taj naziv razrešava
    - CNAME: Canonical name
    - PTR: Inverzna dotted-decimal notacija, `4.3.2.1.in-addr.arpa`

## IPv6
- L2 identifikacija IPv6 je 0x86dd umesto 0x800
- Efikasnije agregiranje zbog hijerarhijske strukture mrežnih adresa
- Podrška za automatsku konfiguraciju računara, IPSec za bezbednost podataka, mobilne uređaje, alokaciju resursa i kvalitet servisa, povećan broj multicast adresa
- Zaglavlje:
    - HLEN: Izbačen jer nema opcionih polja
    - Header Checksum ne postoji jer se proverava od TCP/UDP
    - Fragmentacija je potpuno izbačena:
        - Sprovodi se na izvorištu, ne u ruterima
        - Garantuje Maximum Transmission Unit od 1280 bajtova, a može i da se radi Path MTU Discovery
        - Ako je paket veći od MTU on se uništava i šalje se ICMPv6 poruka Packet Too Big (na ovome se zasniva Path MTU Discovery)
        - Path MTU Discovery ima problem što se putanja može promeniti ali to se retko dešava
    - Traffic Class: Preimenovan Type of Service, različite klase sa različitim prioritetima
    - Flow Label: Oznaka jednog toka komunikacije, kešira se Flow Label i ne mora da se gleda ruting tabela
    - Payload Length: Dužina podataka u bajtovima
    - Hop Limit: Isto što i TTL
    - Hext Header: Umesto Protocol, označava koji je tip sledećeg zaglavlja pa se tako mogu ubaciti opciona zaglavlja
- Routing Extension opcija: Definiše se sekvenca adresa rutera i koliko je još međutačaka preostalo
- Anycast: Isporučuje bilo kom interfejsu koji sluša na jednoj adresi
- Unicast adrese:
    - Global Unicast: javne adrese, 2000::/3, počinje 001
        - Prefix: mrežni deo adrese
            - Global Routing Prefix: Dodeljuje se organizacijama, RIR dobija 23, ISP dobija 32 bita...
            - Subnet ID: Organizaciona podmreža
        - Interface ID: adresa interfejsa u IPv6 mreži (obično 64 bita)
            - Može da se dodeljuje statički, dozvoljene su sve jedinice i sve nule, a može i dinamički (EUI-64 ili nasumično)
            - EUI-64: MAC adresa i umetne se FFFE u sredinu, sedmi bit prvog bajta je 0 ako je univerzalna i 1 ako je lokalna
    - Unique Local: privatne adrese, fc00::/7, sedmi bit je jedino dozvoljen da bude 1
        - Ne smeju da se oglašavaju na internetu
        - Global ID: Pseudo-slučajna vrednost sa algoritmom za generisanje, povezuje više mreža sa Unique Local adresama
    - Link Local: samo unutar lokalne IP mreže, fe80::/10
        - Ruteri ne prosleđuju pakete sa ovim adresama
        - 54 bita posle prefiksa su samo nule
        - Interface ID: EUI-64, manuelno, nasumično
    - Loopback: ::1/128, kao 127.0.0.1
    - Unspecified: Nepostojeća, ::/128, samo kao izvorišna adresa
    - Embedded IPv4: ::/80, na početku 80 nula i 16 jedinica, IPv4 poslednja adresa
- Multicast adrese: ff00::/8
    - Flags:
        - T fleg:
            - 0: Well-Known, dodeljeno od IANA
            - 1: Transient, dodeljeno od multicast aplikacija
    - Scope: Opsezi korišćenja
        - 2: Samo na lokalnom L2 segmentu
        - 8: Na nivou organizacije
        - E: Globalni opseg
    - Solicited-Node multicast adrese:
        - Automatski generisane iz GUA, ULA i LLA
        - Za Neighbor Discovery Protocol, koji se koristi za Address Resolution i Duplicate Address Detection
        - Fiksan prefiks: ff02:0:0:0:0:1:ff00::/104, na poslednja 24 bita iz Interface ID
- Anycast adrese: paketi stižu do najbližeg uređaja
- Konfigurisanje adresa:
    - Statički: ili cele adrese ili samo mrežnog dela
    - Dinamički:
        - Stateful DHCPv6
        - Stateless Address Autoconfiguration (SLAAC):
            - Uređaji automatski saznaju mrežni deo, default gateway i DNS server a Interface ID se postavlja automatski
- ICMPv6: Novi tipovi poruka
    - Neighbor Discovery Protocol:
        - Stateless Address Autoconfiguration je NDP u dva koraka:
            1. Uređaj šalje upit svim ruterima na lokalnoj mreži preko Router Solicitation poruke, izvorište je link-local adresa a odredište All IPv6 Routers
            2. Ruter odgovara Router Advertisement porukom, izvorište je LL adres rutera a odredište uređaja, sadržaj je mrežna adresa i opciono DNS, za default gateway se uzima izvorišna IP adresa
        - Ruteri i sami oglašavaju RA poruke
        - Dodela DNS: NDP, Stateless DHCPv6 (svima iste informacije), Stateful DHCPv6 (dodeljuje se i adresa, maska, default gateway i DNS server sa pamćenjem)
        - Address Resolution:
            1. Uređaj šalje Neighbor Solicitation poruku izvorišna adresa je unikast adresa uređaja koji zahteva MAC adresu a odredišna Solicited-Node multikast adresa za poznatu IP adresu, odredišni MAC je multikast
            2. Neighbor Advertisement: Izvorišna adresa je unikast adresa uređaja koji šalje, odredišna je unikast uređaja koji je poslao a sadržaj zahtevana MAC adresa
        - Duplicate Address Detection: Address Resolution pa ako neko odgovori onda je dupla
- Tranzicija:
    - IPv4/IPv6 Dual stack: Dvostruki IP sloj
    - IPv6 tunelovanje: IPv6 paketi se zapakuju u IPv4 pakete
    - NAT-PT

## RARP
- Nalazi se MAC adresa na osnovu IP adrese
- RARP server mapira MAC adrese u IP adrese
- Koristilo se na diskless računarima
- Operation polje u L3 zaglavlju
- Sve ostalo isto kao ARP
- Nedostatak: nema default gateway, ne možemo da izađemo

## BOOTP
- Kao RARP ali aplikativnog nivoa i šalje i default gateway, masku, DNS itd.
- Aplikativnog nivoa, koristi UDP
- Na UDP nivou podešeni portovi, na IP broadcast, na Ethernet broadcast

## DHCP
- Dinamičko dodeljivanje adresa iz predefinisanog opsega
- Može da postoji više DHCP servera
- Četiri koraka:
    - DHCP-DISCOVER: Otkrivamo DHCP servere
    - DHCP-OFFER: DHCP server dodeljuje adresu i šalje nazad
    - DHCP-REQUEST: Odgovara koju IP adresu sada koristi
    - DHCP-ACK: Korisnik može da koristi dobijene parametre

## NAT
- Prevodi privatne adrese na internet
- Adrese:
    - Inside Local Address: Privatna adresa unutar mreže
    - Inside Global Address: Adresa u koju se pretvara Inside Local adresa
    - Outside Global Address: IP adresa na spoljašnjoj mreži
- Statički NAT:
    - Ako bi se svaka adresa mapirala u globalnu ne postiže se puna ušteda adresa
- Dinamički NAT:
    - Dodeljuje se IP adresa za svaku konekciju (timeout)
- Overload NAT:
    - Koriste se portovi
    - Port forwarding
- Dozvole pristupa portu: Symmetric, Full-Cone, Restricted-Cone, Port-Restricted-Cone
- Mapiranje ICMP:
    - Query: Imaju Query ID pa se preko toga radi mapiranje
    - Error: Potrebno promeniti lokalne adrese i portove u originalnom paketu
- Application Level Gateway: Menja IP adrese i u aplikativnim podacima

## ACL
- Implicitno odbacivanje
