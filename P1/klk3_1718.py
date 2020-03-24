from typing import Dict

def readExchangeRate() -> Dict[str, float]:
    lista = {}
    with open('kursnaLista.csv', 'r', encoding='utf-8') as f:
        for line in f.readlines():
            valuta, vrednost = line.split(',')
            lista[valuta.strip()] = float(vrednost)
    return lista

def convertToRSD(rates: Dict[str, float], value: float, currency: str) -> float:
    return rates[currency] * value

def readOffers(rates: Dict[str, float]) -> Dict[str, float]:
    prodavnice = {}
    with open('prodavnice.csv', 'r', encoding='utf-8') as f:
        for line in f.readlines():
            ime, cena, valuta = line.split(',')
            prodavnice[ime.strip()] = convertToRSD(rates, float(cena), valuta.strip())
    return prodavnice

def findMinShop(offers: Dict[str, float]) -> str:
    shop = ''
    min_value = None
    for name, value in offers.items():
        if min_value is None or min_value > value:
            min_value = value
            shop = name
    return shop

def findMaxShop(offers: Dict[str, float]) -> str:
    shop = ''
    max_value = None
    for name, value in offers.items():
        if max_value is None or max_value < value:
            max_value = value
            shop = name
    return shop

kursna_lista = readExchangeRate()
prodavnice = readOffers(kursna_lista)
min_prodavnica = findMinShop(prodavnice)
max_prodavnica = findMaxShop(prodavnice)
print('{}, {}, {:.2f}'.format(min_prodavnica, max_prodavnica, prodavnice[max_prodavnica] - prodavnice[min_prodavnica]))
