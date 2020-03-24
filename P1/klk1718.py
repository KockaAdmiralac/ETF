# Napisati program na programskom jeziku Python koji vrši određenu obradu nad nizom
# pozitivnih celih brojeva dužine N (N ≤ 100). Program najpre učitava dužinu niza,
# a zatim i same elemente niza. Nakon toga program treba da formira novi niz koji će
# sadržati samo one elemente učitanog niza koji predstavljaju palindrom.
# Element niza predstavlja palindrom, ukoliko se isto čita sleva na desno i sdesna na
# levo u dekadnom brojnom sistemu, kada je ispisan bez vodećih nula. Nakon završene obrade,
# ispisati rezultujući niz. Program treba da ponavlja svoje izvršavanje dok god u ulaznom
# nizu postoji bar jedan element koji predstavlja palindrom. Smatrati da element niza ne
# sadrži više od 10 cifara, ne računajući vodeće nule.

# Napisati funkciju readArray(n) koja formira niz dužine n pozitivnih celih brojeva.
# Elementi niza se zadaju po jedan u posebnom redu. Povratna vrednost je formirani niz.
def readArray(n):
    return [int(input()) for x in range(n)]

# Napisati funkciju printArray(arr) koja ispisuje sadržaj zadatog niza niz pozitivnih
# celih brojeva u jednom redu odvojenih zarezom.
def printArray(arr):
    print(arr)

# Napisati funkciju add(arr, num) koja zadati broj dodaje u zadati niz na kraj.
def add(arr, num):
    arr.append(num)
    return arr

# Napisati funkcju reverse(num) koja obrće cifre zadatog pozitivnog celog broja broj.
# Povratna vrednost ove funkcije je novoformirani broj. Na primer, 123 postaje 321,
# ili 1234 postaje 4321. 
def reverse(num):
    l = list(str(num))
    l.reverse()
    return int(''.join(l))

# Napisati funkciju palindrom(num) koja koristi funkciju reverse(num) za proveru da li
# je zadati broj broj palindrom. Povratna vrednost funkcije je logička vrednost.
def palindrom(num):
    return num == reverse(num)

# Korišćenjem prethodno realizovanih funkcija napisati glavni program koji učitava broj
# elemenata niza, a zatim i same elemente, a potom za svaki element niza proverava da li
# je palindrom i ukoliko jeste, dodaje ga u novi niz koji je na početku prazan.
# Na kraju se ispisuje novokreirani niz palindroma.
# Program treba da ponavlja svoje izvršavanje dok se ne unese nekorektna dužina niza.
while True:
    try:
        n = int(input())
        if n < 1 or n > 100:
            break
        nova_lista = []
        for num in readArray(n):
            if palindrom(num):
                add(nova_lista, num)
        print(nova_lista)
    except ValueError:
        break
