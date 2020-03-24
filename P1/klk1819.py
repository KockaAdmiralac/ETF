# Napisati funkciju readArray(n) koja formira niz pozitivnih celih brojeva dužine n.
# Elementi niza se zadaju po jedan u zasebnim redovima.
# Povratna vrednost funkcije je formirani niz.
def readArray(n):
    return [int(input()) for x in range(n)]

# Napisati funkciju printArray(arr) koja ispisuje sadržaj zadatog niza pozitivnih celih brojeva
# u jednom redu odvojenih zarezom.
def printArray(arr):
    print(arr)

# Napisati funkcju sortArray(arr) koja sortira zadati niz pozitivnih celih brojeva u
# neopadajućem redosledu. Povratna vrednost funkcije je sortirani niz.
def sortArray(arr):
    arr.sort()
    return arr

# Napisati funkciju isArithmeticProgression(arr) koja za zadati sortirani niz pozitivnih
# celih brojeva proverava da li sadrži elemente aritmetičke progresije.
# Elementi niza čine aritmetičku progresiju ukoliko je razlika između uzastopnih elemenata
# niza ista. Smatrati da su elementi zadatog niza sortirani u neopadajućem redosledu.
def isArithmeticProgression(arr):
    if len(arr) == 0 or len(arr) == 1:
        return True
    diff = arr[1] - arr[0]
    for i in range(len(arr) - 1):
        if arr[i + 1] - arr[i] != diff:
            return False
    return True

while True:
    try:
        n = int(input())
        if n < 0:
            break
        arr = readArray(n)
        sortArray(arr)
        printArray(arr)
        if isArithmeticProgression(arr):
            print('MOZE')
            break
        else:
            print('NE MOZE')
    except ValueError:
        break
