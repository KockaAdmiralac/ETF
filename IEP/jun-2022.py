from math import ceil

# Postavka
broj_servera = 400
servera_po_reku = 40
broj_cpu = 2
broj_dram_gb_po_cpu = 64
broj_hd = 2
cena_kwh = 0.05
klima_btu = 12000
metara_po_reku = 4
cena_po_kvadratu = 25
cena_mreze = 3000
plata = 1500

cpu_potrosnja = 105
cpu_cena = 1200
dram_potrosnja = 3.5
dram_cena = 20
hd_afr = 0.5
hd_potrosnja = 6.5
hd_cena = 700
rek_ruter_potrosnja = 500
rek_ruter_cena = 2500
agregacioni_ruter_potrosnja = 3000
agregacioni_ruter_cena = 70000
klima_potrosnja = 1500
klima_cena = 800
kamatna_rata = 5
period_amortizacije_racunarske_opreme = 3
period_amortizacije_mrezne_opreme = 4
period_amortizacije_rashladne_opreme = 7

# 1. zadatak
hd_mttf = 100 / hd_afr * 24 * 365
period_testiranja = 24 * 365
broj_testiranih = broj_servera * broj_hd
broj_otkazalih = period_testiranja * broj_testiranih / hd_mttf
print(ceil(broj_otkazalih))

# 2. zadatak
potrosnja_serveri = broj_servera * (broj_cpu * cpu_potrosnja + broj_dram_gb_po_cpu * broj_cpu * dram_potrosnja + broj_hd * hd_potrosnja)
broj_rekova = ceil(broj_servera / servera_po_reku)
potrosnja_ruteri = broj_rekova * rek_ruter_potrosnja + agregacioni_ruter_potrosnja
potrosnja_za_rashladu = potrosnja_serveri + potrosnja_ruteri
btu_u_wh = 0.293
broj_klima = ceil(potrosnja_za_rashladu / (klima_btu * btu_u_wh))
print(broj_klima)

# 3. zadatak
cena_racunarske_opreme = broj_servera * (broj_cpu * cpu_cena + broj_dram_gb_po_cpu * broj_cpu * dram_cena + broj_hd * hd_cena)
cena_mrezne_opreme = broj_rekova * rek_ruter_cena + agregacioni_ruter_cena
cena_rashladne_opreme = broj_klima * klima_cena
CAPEX = cena_racunarske_opreme + cena_mrezne_opreme + cena_rashladne_opreme
print(CAPEX)

# 4. zadatak
K = kamatna_rata / 100 / 12
amortizacija_racunarske_opreme = K * cena_racunarske_opreme / (1-(1+K)**(-period_amortizacije_racunarske_opreme * 12))
amortizacija_mrezne_opreme = K * cena_mrezne_opreme / (1-(1+K)**(-period_amortizacije_mrezne_opreme * 12))
amortizacija_rashladne_opreme = K * cena_rashladne_opreme / (1-(1+K)**(-period_amortizacije_rashladne_opreme * 12))
broj_radnika = ceil(7 * 24 / 40)
plate = broj_radnika * plata
potrosnja_klime = broj_klima * klima_potrosnja
struja = (potrosnja_serveri + potrosnja_ruteri + potrosnja_klime) * cena_kwh / 1000 * 24 * 365 / 12
prostor = broj_rekova * metara_po_reku * cena_po_kvadratu
OPEX = amortizacija_racunarske_opreme + amortizacija_mrezne_opreme + amortizacija_rashladne_opreme + plate + struja + prostor + cena_mreze
print(OPEX)
