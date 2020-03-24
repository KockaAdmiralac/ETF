while True:
    # Unos.
    lista = []
    try:
        dužina_niza = int(input("Unesi dužina niza: "))
        if dužina_niza < 1:
            break
        validno = True
        for i in range(dužina_niza):
            element = int(input("Unesi element niza: "))
            if element < 1:
                validno = False
                break
            lista.append(element)
        if not validno:
            break
    except ValueError:
        break
    
    indeksi = []
    # Provera deljivosti
    for i in range(len(lista)):
        broj = lista[i]
        trocifre = []
        while broj != 0:
            trocifre.append(broj % 1000)
            broj //= 1000
        zbir = 0
        for j in range(len(trocifre)):
            if j % 2 == 0:
                zbir += trocifre[j]
            else:
                zbir -= trocifre[j]
        if zbir % 13 == 0:
            indeksi.append(i)
    
    # Ispis.
    if len(indeksi) > 0:
        for i in range(len(indeksi) - 1):
            print(indeksi[i], end=', ')
        print(indeksi[-1])
    
    # Modifikacija.
    nova_lista = []
    maksimum = max(lista)
    minimum = min(lista)
    for element in lista:
        if element != maksimum and element != minimum:
            nova_lista.append(element)
    
    # Drugi ispis.
    dužina_nove_liste = len(nova_lista)
    print(dužina_nove_liste)
    if dužina_nove_liste > 0:
        for i in range(dužina_nove_liste - 1):
            print(nova_lista[i], end=', ')
        print(nova_lista[-1])
