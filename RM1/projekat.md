# RM1 Projekat
Ovaj vodič je napisan iz razloga što predmetni saradnici izgleda da nemaju nameru da postavku projekta menjaju iz godine u godinu, a i jer je mogućnost detekcije prepisivanja donekle manja zbog nečitkog formata Packet Tracer datoteka. Za svaki uređaj date su instrukcije za podešavanje ispod kako bi uslovi postavke bili ispunjeni. Linije podešavanja koje počinju sa `#` su komentari i ne treba ih pisati u komandnoj liniji.

## Osnovna podešavanja
1. Nacrtati šemu kao u postavci projekta jer se ostatak ovog vodiča zasniva na tim brojevima.
2. U svaki switch i ruter dodati FastEthernet ili GigabitEthernet module kroz Physical tab. Broj i tip su proizvoljni. Ovde će biti dodavani samo FastEthernet (`*-1CFE`) moduli kako bi komande bile jednostavnije. Pre ubacivanja modula morate isključiti uređaj, pa ga uključite čim ih ubacite.
3. Povežite uređaje kablovima. Oni koji se na slici prikazuju kao isprekidani su Copper Cross-Over kablovi dok su oni ostali Copper Straight-Through.
4. Podesite u Options > Preferences opciju "Show Port Labels When Mouse Over In Logical Workspace" ako već nije kako biste mogli da vidite broj porta kad pređete mišem preko trouglića na tom portu

## R1
```
en
configure terminal
hostname R1
# Podešavanje IP adrese prema R3
interface Fa0/0
ip address 192.168.13.1 255.255.255.0
no shutdown
exit
# Podešavanje IP adrese prema R2
interface Fa1/0
ip address 192.168.12.1 255.255.255.0
no shutdown
exit
# Podešavanje IP adrese prema mreži na Switch3
interface Fa2/0
ip address 192.168.0.1 255.255.255.0
no shutdown
exit
# Podešavanje OSPF
router ospf 1
network 192.168.0.0 0.0.0.255 area 0
network 192.168.12.0 0.0.0.255 area 0
network 192.168.13.0 0.0.0.255 area 0
exit
# Telnet
line vty 0 4
password pass_telnet
login
exit
line console 0
password pass_console
login
exit
enable password pass_enable
banner motd "
Lozinka za Telnet pristup je pass_telnet.
Lozinka za konzolni pristup je pass_console.
Lozinka za enable je pass_enable.
"
# Izađi iz moda podešavanja
exit
# Sačuvaj trenutna podešavanja (ovo radite često)
copy running-config startup-config
```

## R2
```
en
configure terminal
hostname R2
# Podešavanje IP adrese prema R1
interface Fa0/0
ip address 192.168.12.2 255.255.255.0
no shutdown
exit
# Podešavanje IP adrese prema R4
interface Fa2/0
ip address 192.168.24.1 255.255.255.0
no shutdown
exit
# Podešavanje IP adrese prema R5
interface Fa1/0
ip address 8.0.25.1 255.255.255.0
no shutdown
exit
# Podešavanje RIPv2
router rip
version 2
network 8.0.25.0
redistribute ospf 1 metric 1
exit
# Podešavanje OSPF
router ospf 1
network 192.168.12.0 0.0.0.255 area 0
network 192.168.24.0 0.0.0.255 area 0
redistribute rip metric 25 metric-type 2 subnets
exit
# Izađi iz moda podešavanja
exit
# Sačuvaj trenutna podešavanja (ovo radite često)
copy running-config startup-config
```

## R3
```
en
configure terminal
hostname R3
# Podešavanje IP adrese prema R1
interface Fa0/0
ip address 192.168.13.2 255.255.255.0
no shutdown
exit
# Podešavanje IP adrese prema mreži na Switch0
interface Fa1/0
ip address 192.168.1.1 255.255.255.0
no shutdown
exit
# Podešavanje OSPF
router ospf 1
network 192.168.13.0 0.0.0.255 area 0
network 192.168.1.0 0.0.0.255 area 1
area 1 stub no-summary
exit
# Izađi iz moda podešavanja
exit
# Sačuvaj trenutna podešavanja (ovo radite često)
copy running-config startup-config
```

## R4
```
en
configure terminal
hostname R4
# Podešavanje IP adrese prema R2
interface Fa0/0
ip address 192.168.24.2 255.255.255.0
no shutdown
exit
# Podešavanje IP adrese prema mreži na Switch1
interface Fa1/0
ip address 192.168.2.1 255.255.255.0
no shutdown
exit
# Podešavanje OSPF
router ospf 1
network 192.168.24.0 0.0.0.255 area 0
network 192.168.2.0 0.0.0.255 area 2
area 2 stub
exit
# Izađi iz moda podešavanja
exit
# Sačuvaj trenutna podešavanja (ovo radite često)
copy running-config startup-config
```

## R5
```
en
configure terminal
hostname R5
# Podešavanje IP adrese prema R2
interface Fa0/0
ip address 8.0.25.2 255.255.255.0
no shutdown
exit
# Podešavanje IP adrese prema mreži na Switch2
interface Fa1/0
ip address 8.0.0.1 255.255.255.0
no shutdown
exit
# DHCP
## Podešavanje DHCP pool-a
ip dhcp pool R5_DHCP
network 8.0.0.0 255.255.255.0
default-router 8.0.0.1
dns-server 8.0.0.3
exit
## Izbacivanje adresa iz dodeljivanja za DHCP
ip dhcp excluded-address 8.0.0.0 8.0.0.15
ip dhcp excluded-address 8.0.0.18 8.0.0.24
# Podešavanje RIPv2
router rip
version 2
network 8.0.0.0
network 8.0.25.0
exit
# Podešavanje ACL
ip access-list extended R5_ACL
permit udp any host 8.0.0.3 eq domain
deny ip any host 8.0.0.3
permit tcp any host 8.0.0.2 eq www
permit icmp any host 8.0.0.2 echo
deny ip any host 8.0.0.2
permit ip any any
exit
# Primenjujemo ACL nad ulaznim portovima iz R2
interface Fa0/0
ip access-group R5_ACL in
exit
# Izađi iz moda podešavanja
exit
# Sačuvaj trenutna podešavanja (ovo radite često)
copy running-config startup-config
```

## DNS local
1. U Desktop > IP Configuration podesiti:
    - IPv4 Address: 192.168.0.2
    - Subnet Mask: 255.255.255.0
    - Default Gateway: 192.168.0.1
    - DNS Server: 0.0.0.0
2. U Services > DNS podesiti:
    - DNS Service: On
    - Name: com
    - Type: NS Record
    - Server Name: ns.com
    - Kliknuti Add
    - Name: ns.com
    - Type: A Record
    - Address: 8.0.0.3

## DHCP
1. U Desktop > IP Configuration podesiti:
    - IPv4 Address: 192.168.1.2
    - Subnet Mask: 255.255.255.0
    - Default Gateway: 192.168.1.1
    - DNS Server: 0.0.0.0
2. U Services > DHCP podesiti:
    - Service: On
    - Default Gateway: 192.168.1.1
    - DNS Server: 192.168.0.2
    - Start IP Address: 192.168.1.5
    - Subnet Mask: 255.255.255.0
    - Kliknuti Save

## www.google.com
1. U Desktop > IP Configuration podesiti:
    - IPv4 Address: 8.0.0.2
    - Subnet Mask: 255.255.255.0
    - Default Gateway: 8.0.0.1
    - DNS Server: 0.0.0.0
2. U Services > HTTP podesiti sadržaj `index.html` kako bi bio prepoznatljiv (HTTP bi već trebalo da je uključen na svim serverima podrazumevano).

## DNS google.com
1. U Desktop > IP Configuration podesiti:
    - IPv4 Address: 8.0.0.3
    - Subnet Mask: 255.255.255.0
    - Default Gateway: 8.0.0.1
    - DNS Server: 0.0.0.0
2. U Services > DNS podesiti:
    - DNS Service: On
    - Name: google.com
    - Type: A Record
    - Address: 8.0.0.2
    - Kliknuti Add
    - Name: www.google.com
    - Type: CNAME
    - Host Name: google.com

## PC0, PC1
U Desktop > IP Configuration podesiti (nakon podešavanja DHCP servera u OSPF oblasti 1) da se IPv4 adrese dobijaju preko DHCP.

## PC2
U Desktop > IP Configuration podesiti:
- IPv4 Address: 192.168.2.2
- Subnet Mask: 255.255.255.0
- Default Gateway: 192.168.2.1
- DNS Server: 192.168.0.2

## PC3
U Desktop > IP Configuration podesiti:
- IPv4 Address: 192.168.2.3
- Subnet Mask: 255.255.255.0
- Default Gateway: 192.168.2.1
- DNS Server: 192.168.0.2

## PC4, PC5, PC6
U Desktop > IP Configuration podesiti (nakon podešavanja DHCP na R5) da se IPv4 adrese dobijaju preko DHCP.

## PC10
U Desktop > IP Configuration podesiti:
- IPv4 Address: 192.168.0.3
- Subnet Mask: 255.255.255.0
- Default Gateway: 192.168.0.1
- DNS Server: 192.168.0.2

## PC11
U Desktop > IP Configuration podesiti:
- IPv4 Address: 192.168.0.4
- Subnet Mask: 255.255.255.0
- Default Gateway: 192.168.0.1
- DNS Server: 192.168.0.2

## Testiranje
1. Komandom `show ip access-lists` možete prikazati broj puta koliko je neko pravilo u ACL korišćeno, pa na osnovu toga možete da vidite da li je dobro. Za gornja pravila u ACL testiranje je ovakvo:
    - `permit udp any host 8.0.0.3 eq domain`: Uđite u Command Prompt na nekom računaru i pokrenite `ping google.com`
    - `deny ip any host 8.0.0.3`: Uđite u Command Prompt na nekom računaru i pokrenite `ping 8.0.0.3`
    - `permit tcp any host 8.0.0.2 eq www`: Uđite u web browser na nekom računaru i posetite `google.com`
    - `permit icmp any host 8.0.0.2 echo`: Uđite u Command Prompt na nekom računaru i pokrenite `ping google.com`
    - `deny ip any host 8.0.0.2`: Uđite u Command Prompt na nekom računaru i pokrenite `telnet google.com`
    - `permit ip any any`: Uđite u Command Prompt na nekom računaru i pokrenite `ping 8.0.0.16`

## Modifikacije
### RX
```
en
conf t
hostname RX
# Podešavanje IP adrese
interface Fa0/0
ip address 192.168.1.4 255.255.255.0
no shutdown
exit
# Podešavanje OSPF kako bi se prihvatile rute
router ospf 1
network 192.168.1.0 0.0.0.255 area 1
area 1 stub
exit
# Čuvanje
exit
copy running-config startup-config
```
### R1
```
en
conf t
ip access-list extended R1_ACL
# Dozvoljava se DNS upit za DNS local
permit udp any host 192.168.0.2 eq domain
# Bez ovoga neće raditi pristup google.com osim ako se ne kešira na DNS local
permit udp host 8.0.0.3 host 192.168.0.2
# Dozvoljava se ping sa RX na DNS local
permit icmp host 192.168.1.4 host 192.168.0.2 echo
# Zabranjuje se sve ostalo sa DNS local
deny ip any host 192.168.0.2
# Dozvoljava se sve ostalo sa ostalim računarima
permit ip any any
exit
# Podešavanje ACL na ulaznim interfejsima (prema R2 i prema R3)
interface Fa0/0
ip access-group R1_ACL in
exit
interface Fa1/0
ip access-group R1_ACL in
exit
# Čuvanje
copy running-config startup-config
```
### DNS local
- Dodati NS unos za `rs` ka `ns.rs`
- Dodati A unos za `ns.rs` ka `8.0.0.3`

### DNS google.com:
- Dodati CNAME unos za `rm1.rs` ka `google.com`

### Testiranje
- Pristup `google.com` kroz web browser (prikazuje se)
- `ping ip 192.168.0.2` kroz RX (prihvata se)
- `ping 192.168.0.2` kroz bilo koji računar (odbija se jer ACL ne dozvoljava)
- Pristup `rm1.rs` kroz web browser (prikazuje isti sajt kao `google.com`)
