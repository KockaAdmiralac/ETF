# 1. zadatak
racks = 2 * 1000
ups = 6 * 1500
sasije = 5 * 4000
servers = 50 * 4500
firewalls = 8800 * 2
balancers = 7000 * 2
switches = 2300 * 2
storage = 9100
CAPEX = racks + ups + sasije + servers + firewalls + balancers + switches + storage

# 2. zadatak
kwh = 0 * 2 + 0.25 * 6 + 0.40 * 5 + 0.30 * 50 + 0.40 * 2 + 0.25 * 2 + 0.10 * 2 + 0.45 * 1
struja = kwh * 24 * 30 * 1.41 * 0.05
K = 0.05 / 12
N = 3 * 12
otplata = K * CAPEX / (1 - (1+K)**(-N))
plate = 5 * 1500 # ceil(24 * 7 / 40) = 5
prostor = 2 * 4 * 25
internet = 3000
OPEX = struja + otplata + plate + prostor + internet

# 3. zadatak
# Bottlenecks:
#   - Vreme za opsluživanje zahteva od veb servera, aplikativnog servera ili baze
#   - Protok tokom opsluživanja zahteva od firewall ili baze
#   - Balanser
staticki_zahtevi_po_stranici = 17
dinamicki_zahtevi_po_stranici = 10
vreme_obrade_statickih_zahteva_ms = 0.25
vreme_obrade_dinamickih_zahteva_ms = 1.5
vreme_obrade_zahteva_ka_bazi_ms = 5.5
zahteva_ka_bazi_po_dinamickom_zahtevu = 1.4
zahteva_ka_bazi_po_stranici = dinamicki_zahtevi_po_stranici * zahteva_ka_bazi_po_dinamickom_zahtevu
vreme_obrade_veb_servera_po_stranici_ms = staticki_zahtevi_po_stranici * vreme_obrade_statickih_zahteva_ms
vreme_obrade_aplikativnog_servera_po_stranici_ms = dinamicki_zahtevi_po_stranici * vreme_obrade_dinamickih_zahteva_ms
vreme_obrade_baze_po_stranici_ms = zahteva_ka_bazi_po_stranici * vreme_obrade_zahteva_ka_bazi_ms
# sps = stranice po sekundi
broj_sps_veb_server = 1000/vreme_obrade_veb_servera_po_stranici_ms
broj_sps_aplikativni_server = 1000/vreme_obrade_aplikativnog_servera_po_stranici_ms
broj_sps_baza = 1000/vreme_obrade_baze_po_stranici_ms

# Određujemo broj potrebnih servera za svaku vrstu u zavisnosti od brzine procesiranja zahteva
reciprocni_zbir_sps = 1/broj_sps_veb_server + 1/broj_sps_aplikativni_server + 1/broj_sps_baza
broj_servera = 50
broj_veb_servera = round((1/broj_sps_veb_server) / reciprocni_zbir_sps * broj_servera)
broj_aplikativnih_servera = round((1/broj_sps_aplikativni_server) / reciprocni_zbir_sps * broj_servera)
broj_baza = round((1/broj_sps_baza) / reciprocni_zbir_sps * broj_servera)
# print(broj_veb_servera, broj_aplikativnih_servera, broj_baza) #-> 2 8 40

broj_sps_procesor = min(
    broj_veb_servera * 10 * broj_sps_veb_server,
    broj_aplikativnih_servera * 10 * broj_sps_aplikativni_server,
    broj_baza * 10 * broj_sps_baza
)
# print(broj_sps_procesor * zahteva_ka_bazi_po_stranici * 6.1 / broj_baza / 1024 / 1024 * 8) #-> baza nije bottleneck, ovo je manje od 1Gbps
balancer_sps = 20000 / (staticki_zahtevi_po_stranici + dinamicki_zahtevi_po_stranici) * 2
firewall_sps = 40 * 1024 / ((staticki_zahtevi_po_stranici * 18 + dinamicki_zahtevi_po_stranici * 2) * 0.15)
print(balancer_sps, firewall_sps, broj_sps_procesor) #-> Balanser je bottleneck! ~740 zahteva po sekundi
sps = min(balancer_sps, firewall_sps, broj_sps_procesor)
broj_korisnika = sps / 8 * 10 * 60 / 3.5
print(broj_korisnika)
