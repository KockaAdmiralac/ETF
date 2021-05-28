# Packet Tracer komande
## Opšte
- Običan mod:
    - `en`: Uključi ruter
    - `show running-config`: Prikaži trenutnu konfiguraciju
    - `configure terminal`/`conf t`: Uđi u konfiguracioni mod
    - `show ip interface brief`: Prikaži interfejse
- Mod podešavanja:
    - `copy running-config startup-config`: Čuva trenutnu konfiguraciju kako bi se nakon restartovanja vratila
    - `hostname [naziv]`: Postavi hostname

## Podešavanje IP adresa rutera
- Običan mod:
    - `show ip route`: Prikaži ruting tabelu
- Mod podešavanja:
    - `interface [fa0/0]`/`int [fa0/0]`: Uđi u mod podešavanja interfejsa
    - Mod podešavanja interfejsa:
        - `ip address [addr/DHCP] [subnet mask]`: Dodeli IP adresu interfejsu
        - `no shutdown`: Uključi interfejs
        - `ip route [ruta] [maska] [next hop]`

## Rutiranje
- Običan mod:
    - `show ip ospf neighbor`: Prikaži OSPF susede
    - `show ip ospf database`: Prikaži OSPF bazu
- Mod podešavanja:
    - `no router rip`: Isključujemo RIP protokol
    - `no router ospf [id]`: Isključujemo OSPF sa zadatim brojem procesa
    - `router rip`: Ulazi u mod podešavanja RIP
    - `router ospf [id]`: Ulazi u mod podešavanja OSPF sa zadatim brojem procesa
    - `interface loopback [id]`: Pokreni loopback interface sa zadatim ID/uđi u mod podešavanja
    - Mod podešavanja interfejsa:
        - `bandwidth [kbps]`: Podešava bandwidth na interfejsu
        - `no ip ospf cost`: Zaključi cenu iz bandwidth
        - `ip ospf cost 20`: Podešava cenu na interfejsu
    - Mod podešavanja RIP:
        - `version [1/2]`: Definiše verziju RIP
        - `network [ip]`: Definiše interfejs koji će biti korišćen u protokolu
    - Mod podešavanja OSPF:
        - `network [ip] [wildcard] area [area]`: Definiše interfejs koji će biti korišćen u protokolu i u kojoj je oblasti
        - `area [area] stub`: Na jednom ruteru kaže da je oblast 1 stub
            - `area [area] stub no-summary`: Na jednom ruteru kaže da je oblast 1 totally stubby?
        - `redistribute rip subnets`: Podesi redistribuciju ruta sa RIP, koristi O E2
        - `redistribute rip metric-type [1/2] subnets`: Podesi redistribuciju ruta sa RIP, koristi O E[broj]
- Packet Tracer ponekad baguje sa OSPF, restart bi trebalo da pokaže dobro

## DHCP
- Desktop > IP configuration
- Services > DHCP
- Običan mod:
    - `show ip dhcp ?`: Informacije o DHCP podešavanju
- Mod podešavanja:
    - `ip dhcp pool [naziv]`: Uđi u konfiguracioni režim DHCP
    - `ip dhcp excluded-address [from] [to]`: Koje adrese ne treba dodeljivati
- Mod podešavanja DHCP:
    - `network [ip] [mask]`: Za koju mrežu se dodeljuje
    - `default-router [ip]`: Gde je default gateway

## ARP
- `arp -a` u terminalu
- Običan mod
    - `show arp`: Prikazuje sve ARP unose

## Telnet
- Console kabl
- Terminal
- Mod podešavanja:
    - `line console 0`: Ulazak u mod podešavanja konzolnog porta
    - `line vty 0 4`: Ulazak u mod podešavanja virtuelnog porta
    - `enable password [password]`: Postavljanje lozinke za `enable`
    - `banner motd [message]`: Postavljanje banera koji se ispisuje kad se uđe
- Mod podešavanja porta:
    - `login`: Uključivanje logovanja
    - `password [password]`: Podešavanja lozinke

## DNS
- Services > DNS

## HTTP
- Services > HTTP
- Desktop > Browser

## ACL
- Običan mod:
    - `show ip access-lists`: Prikaži pravila u ACL
- Mod podešavanja:
    - `ip access-list [standard/extended] [num] [name]`: Ulazak u mod podešavanja ACL
- Mod podešavanja interfejsa:
    - `ip access-group [num/name] [in/out]`: Primenjuje jednu ACL nad ulaznim ili izlaznim paketima
- Mod podešavanja ACL:
    - `[priority] [permit/deny] [any/address] [wildcard]`: Zabrani/dozvoli pristup
    - `[priority] [permit/deny] [protocol] [any/address] [dest condition] [port condition]`: Ovo gore ali komplikovanije
    - `no [rule]`: Ukida pravilo

## NAT
- Mod podešavanja:
    - `ip nat [inside/outside] source static [inside IP] [outside IP]`: Statički mapiraj unutrašnji IP u spoljašnji
    - `ip nat [inside/outside] source list [ACL list] pool [pool]`: Mapiraj ACL listu u pool
    - `ip nat [inside/outside] source list [ACL list] interface [interface] overload`: Podešavanje Overload NAT na interfejsu
    - `show ip nat translations`: Prikaži NAT spreslikavanja
    - `ip nat pool [name] [start IP] [end IP] netmask [mask]`: Definisanje pool-a za NAT
- Mod podešavanja interfejsa:
    - `ip nat [inside/outside]`: Gde je unutrašnjost a gde spoljašnjost za NAT
