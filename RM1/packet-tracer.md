# Packet Tracer komande
## Opšte
- Običan mod:
    - `en`: Uključi ruter
    - `show running-config`: Prikaži trenutnu konfiguraciju
    - `configure terminal`/`conf t`: Uđi u konfiguracioni mod
    - `show ip interface brief`: Prikaži interfejse
- Mod podešavanja:
    - `copy running-config startup-config`: Čuva trenutnu konfiguraciju kako bi se nakon restartovanja vratila

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
        - `network [ip] [woldcard] area [area]`: Definiše interfejs koji će biti korišćen u protokolu i u kojoj je oblasti
        - `area [area] stub`: Na jednom ruteru kaže da je oblast 1 stub
            - `area [area] stub no-summary`: Na jednom ruteru kaže da je oblast 1 totally stubby?
        - `redistribute rip subnets`: Podesi redistribuciju ruta sa RIP, koristi O E2
        - `redistribute rip metric-type [1/2] subnets`: Podesi redistribuciju ruta sa RIP, koristi O E[broj]
- Packet Tracer ponekad baguje sa OSPF, restart bi trebalo da pokaže dobro
