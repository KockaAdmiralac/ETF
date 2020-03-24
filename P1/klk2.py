# Napisati funkciju pascalsTriangle ( n ) koja za zadati broj redova n formira i vraća
# listu čiji su elementi prirodni brojevi Paskalovog trougla grupisani u liste.
"""
def pascalsTriangle(n):
    if n == 0:
        return []
    ret = [[1]]
    if n == 1:
        return ret
    for i in range(1, n):
        nova_lista = []
        prosla_lista = ret[i-1]
        for j in range(i + 1):
            levi = (0 if j == 0 else prosla_lista[j-1])
            desni = (0 if j == i else prosla_lista[j])
            nova_lista.append(levi + desni)
        ret.append(nova_lista)
    return ret
"""

# Napisati funkciju binomialCoefficient ( n, k ) koja računa binomni koeficijent po formuli:
# \binom {n} {k} = \Pi_{i=1}^{k} \frac{n+1-i}{i}  
"""
def binomialCoefficient(n, k):
    p1 = 1
    p2 = 1
    for i in range(k):
        p1 *= n - i
        p2 *= k - i
    return p1 // p2
"""

# Napisati funkciju binomialCoefficient ( n, k ) koja računa binomni koeficijent po formuli:
# \binom {n} {k} = \binom{n-1}{k-1} + \binom{n-1}{k}  
def binomialCoefficient(n, k):
    if n == k:
        return 1
    if k > n:
        return 0
    if k == 1:
        return n
    if k == 0:
        return 1
    return binomialCoefficient(n - 1, k - 1) + binomialCoefficient(n - 1, k)

# Pod pretpostavkom da je realizovana funkcija binomialCoefficient ( n, k ) koja računa
# binomni koeficijent   \binom {n} {k}  , napisati funkciju pascalsTriangle ( n ) koja
# za zadati broj redova n formira i vraća listu čiji su elementi prirodni brojevi
# Paskalovog trougla grupisani u liste korišćenjem realizovane funkcije.
def pascalsTriangle(n):
    ret = []
    for i in range(n):
        ret.append([])
        for j in range(i + 1):
            ret[i].append(binomialCoefficient(i, j))
    return ret

# Napisati funkciju printPascalsTriangle ( pascalsTriangle, width ) koja na širini width
# ispisuje Paskalov trougao, zadat parametrom pascalsTriangle, u obliku piramidalne šeme.
def printPascalsTriangle(pascalsTriangle, width):
    for row in pascalsTriangle:
        print(('{:^' + str(width) + '}').format(' '.join([str(x) for x in row])))

# Pod pretpostavkom da su realizovane funkcije pascalsTriangle ( n ) koja za zadati broj
# redova n formira Paskalov trougao i  printPascalsTriangle ( pascalsTriangle, width )
# koja na širini width ispisuje Paskalov trougao, zadat parametrom pascalsTriangle,
# u obliku piramidalne šeme, napisati glavni program koji učitava broj n, formira i
# potom ispisuje Paskalov trougao. Program zatim treba da u petlji učitava broj
# x (0 ≤ x ≤ n ) i ispisuje broj 2x korišćenjem formiranog Paskalovog trougla.
# 
# Iz glavne petlje programa se izlazi u slučaju ulaza koji ne ispunjava uslove.
n = int(input(''))
pt = pascalsTriangle(n + 1)
printPascalsTriangle(pt, len(' '.join([str(x) for x in pt[-1]])) + 1)
while True:
    try:
        x = int(input(''))
        if x < 0 or x > n:
            break
        print('2^{0} = {1}'.format(x, sum(pt[x])))
    except ValueError:
        break
