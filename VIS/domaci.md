---
title: VIS domaći
subtitle: školska godina 2022/2023
date: Jun 2023
geometry: margin=2cm
output: pdf_document
classoption: twoside
header-includes: \usepackage[croatian]{babel}\usepackage{subfig}\usepackage{float}\usepackage{fancyhdr}\usepackage{imakeidx}\usepackage{listings}\usepackage{svg}\makeindex[intoc]\graphicspath{{./}}
pdf-engine: pdflatex
---

# 1. zadatak
## Postavka
Kutija sadrži 10 kuglica numerisanih brojevima od 0 do 9. Izvlače se 2 kuglice (sa vraćanjem) i registruje se uređeni ~~trojka~~ par brojeva koji su izvučeni (elementrani^[sic]^ događaj). Pretpostavimo da su svi elementarni događaji jednakoverovatni. Koliko ima događaja čija je verovatnoća $\frac{2}{5}$?

## Rešenje
Ako se jedno izvlačenje dve kuglice smatra za elementarni događaj, svi elementarni događaji imaju jednaku verovatnoću. Elementarni događaji su sledeći (prva cifra označava broj na prvoj izvučenoj kuglici, druga na drugoj):

```
   01 02 03 04 05 06 07 08 09
10    12 13 14 15 16 17 19 19
20 21    23 24 25 26 27 28 29
30 31 32    34 35 36 37 38 39
40 41 42 43    45 46 47 48 49
50 51 52 53 54    56 57 58 59
60 61 62 63 64 65    67 68 69
70 71 72 73 74 75 76    78 79
80 81 82 83 84 85 86 87    89
90 91 92 93 94 95 96 97 98
```

Ovo je pod pretpostavkom da se prvo izvlači jedna pa druga kuglica i tek posle vraćaju. Ukoliko bi se prvo izvukla jedna, pa vratila, pa druga, pa vratila, elementarni događaji bi bili:

```
00 01 02 03 04 05 06 07 08 09
10 11 12 13 14 15 16 17 19 19
20 21 22 23 24 25 26 27 28 29
30 31 32 33 34 35 36 37 38 39
40 41 42 43 44 45 46 47 48 49
50 51 52 53 54 55 56 57 58 59
60 61 62 63 64 65 66 67 68 69
70 71 72 73 74 75 76 77 78 79
80 81 82 83 84 85 86 87 88 89
90 91 92 93 94 95 96 97 98 99
```

Ovi elementarni događaji čine elemente našeg skupa $\Omega = \{01, 02, 03... 98\}$ (odnosno $\Omega = \{00, 01, 02, 03... 99\}$), a događaji kao podskupi ovog skupa imaju verovatnoću $\frac{2}{5}$ samo ako imaju $\frac{2}{5} \cdot 90 = 36$ (odnosno $\frac{2}{5} \cdot 100 = 40$) elemenata. Broj događaja sa ovom verovatnoćom je onda broj podskupova veličine 36: $\binom{90}{36}$ (odnosno 40: $\binom{100}{40}$).

# 2. zadatak
## Postavka
Homogena kockica se baca 10 puta. Naći verovatnoću da će se pojaviti bar jedna jedinica, bar jedna dvojka i bar jedna šestica.

## Rešenje

- Broj svih ishoda je $6^{10}$.
- Broj svih ishoda u kojima nije pala nijedna jedinica jeste $5^{10}$, i isto važi za dvojke i šestice.
- Broj svih ishoda u kojima se nije pojavila nijedna jedinica i dvojka, ili jedinica i šestica, ili dvojka i šestica, jeste $4^{10}$.
- Broj svih ishoda u kojima se nije pojavila nijedna jedinica, dvojka niti šestica je $3^{10}$.
- Ishodi u kojima nije pala nijedna jedinica uključuje ishode u kojima nije pala nijedna jedinica ni dvojka, ishode u kojima nije pala nijedna jedinica ni šestica, i ishode u kojima nije pala nijedna jedinica, dvojka niti šestica.
- Ishodi u kojima nije pala nijedna jedinica ni dvojka takođe uključuju ishode u kojima nije pala nijedna jedinica, dvojka niti šestica.

S ovim u vidu, broj ishoda u kojima nije pala nijedna jedinica, dvojka ili šestica može se izračunati kao $3 \cdot (5^{10} - 4^{10} - 4^{10} + 3^{10}) + 3 \cdot (4^{10} - 3^{10}) + 3 \cdot 3^{10} = 3 \cdot 5^{10} - 6 \cdot 4^{10} + 3 \cdot 3^{10} + 3 \cdot 4^{10} - 3 \cdot 3^{10} + 3 \cdot 3^{10} = 3 \cdot 5^{10} - 3 \cdot 4^{10} + 3^{10}$. Iz ovoga dobijamo da je tražena verovatnoća događaja jednaka $\frac{6^{10} - 3 \cdot 5^{10} + 3 \cdot 4^{10} - 3^{10}}{6^{10}} \approx 0.5665$.

Skripta za simuliranje zadatka (ispisuje 0.566... nakon deset miliona iteracija):
```python
from random import randint

def iter() -> bool:
    d: dict[int, bool] = {}
    for _ in range(10):
        d[randint(1, 6)] = True
    return d.get(1, False) and d.get(2, False) and d.get(6, False)

n = 10000000
success = sum([iter() for _ in range(n)])
print(success / n)
```

# 3. zadatak
## Postavka
Kutija sadrži 2 žute, 3 crvene i 5 plavih kuglica. Izvlače se 3 kuglice bez vraćanja. Naći verovatnoću da treća kuglica nije plava, ako prva nije žuta i druga nije crvena.

## Rešenje
![Dijagram iz trećeg zadatka](dz-3.png)
Na osnovu crteža sa svim mogućnostima dobijamo da je ova verovatnoća da se dati događaj desi pod datim uslovima: $P(ABC) = \frac{3}{10} \left(\frac{2}{9} \cdot \frac{3}{8} + \frac{5}{9} \cdot \frac{1}{2}\right) + \frac{1}{2} \left(\frac{2}{9} \cdot \frac{1}{2} + \frac{4}{9} \cdot \frac{5}{8}\right) = \frac{3 \cdot (6 + 20) + 5 \cdot (8 + 20)}{10 \cdot 9 \cdot 8} = \frac{78 + 140}{720} = \frac{218}{720}$.

Verovatnoća da su dati uslovi ispunjeni jeste: $P(AB) = \frac{3}{10} \cdot \frac{7}{9} + \frac{1}{2} \cdot \frac{6}{9} = \frac{21}{90} + \frac{30}{90} = \frac{51}{90}$, pa je tražena verovatnoća $P(C|AB) = \frac{P(ABC)}{P(AB)} = \frac{\frac{218}{720}}{\frac{51}{90}} = \frac{218}{408} \approx 0.534$.

# 4. zadatak
## Postavka
Diskretna slučajna promenljiva $X$ uzima vrednosti -2, 0 i 2, pri čemu je $P(X = 0) = \frac{1}{3}$, $P(X = -2) > P(X = 2)$ i $VarX = \frac{20}{9}$. Odrediti $\rho(X, X^2)$.

## Rešenje
- $a = P(X = -2)$
- $P(X = 2) = \frac{2}{3} - a$
- $EX = 0 \cdot \frac{1}{3} + a \cdot (-2) + \left(\frac{2}{3} - a\right) \cdot 2 = \frac{4}{3} - 4a$
- $E(X^2) = 0 \cdot \frac{1}{4} + a \cdot 4 + \left(\frac{2}{3} - a\right) \cdot 4 = \frac{8}{3} = \frac{24}{9}$
- $VarX = E(X^2) - (EX)^2 = \frac{24}{9} - \frac{16}{9} + \frac{32}{3}a - 16a^2 = \frac{20}{9}$
- $-16a^2 + \frac{32}{3}a - \frac{12}{9} = 0$
- $48a^2 - 32a + 4 = 0$
- $12a^2 - 8a + 1 = 0$
- $a = \frac{8 \pm \sqrt{64 - 48}}{24} = \frac{8 \pm 4}{24}$
- $P(X = -2) > P(X = 2) \implies a = \frac{1}{2}$
- $EX = -\frac{2}{3}$
- $E(X^3) = -8 \cdot \frac{1}{2} + 8 \cdot \frac{1}{6} = -\frac{8}{3}$
- $Cov(X, X^2) = E(X^3) - EX \cdot E(X^2) = -\frac{8}{3} + \frac{2}{3} \cdot \frac{8}{3} = -\frac{8}{9}$
- $E(X^4) = 16 \cdot \frac{2}{3} = \frac{32}{3}$
- $Var(X^2) = E(X^4) - (E(X^2))^2 = \frac{32}{3} - \frac{64}{9} = \frac{32}{9}$
- $\rho(X, X^2) = \frac{-\frac{8}{9}}{\sqrt{\frac{20 \cdot 32}{9 \cdot 9}}} = -\frac{\frac{8}{9}}{\frac{8 \sqrt{10}}{9}} = -\frac{1}{\sqrt{10}}$

# 5. zadatak
## Postavka
Gustina slučajne promenljive $X$ je $f(x) = \begin{cases}
    a \cos 2x, & x \in \left(-\frac{\pi}{4}, \frac{\pi}{4}\right) \\
    0,         & x \notin \left(-\frac{\pi}{4}, \frac{\pi}{4}\right) \\
\end{cases}$. Odrediti:

1. vrednost realne konstante $a$,
2. funkciju raspodele slučajne promenljive $X$,
3. $E(X^2)$,
4. $P\left(|X| > \frac{\pi}{6}\right)$.

## Rešenje

1. $1 = \int_{-\frac{\pi}{4}}^{\frac{\pi}{4}} a \cos(2x) = \frac{a}{2} \sin(2x) \Big|_{-\frac{\pi}{4}}^{\frac{\pi}{4}} = \frac{a}{2} + \frac{a}{2} = a \implies a = 1$
2. $F(x) = \begin{cases}
    0,                          & x \leq -\frac{\pi}{4} \\
    \frac{1}{2} (\sin(2x) + 1), & x \in \left(-\frac{\pi}{4}, \frac{\pi}{4}\right) \\
    1,                          & x \geq \frac{\pi}{4}
\end{cases}$
3. $E(X^2) = \int_{-\infty}^{+\infty} x^2 f(x) dx = \int_{-\frac{\pi}{4}}^{\frac{\pi}{4}} x^2 \cos(2x) dx = \frac{x^2 \sin(2x)}{2} \Big|_{-\frac{\pi}{4}}^{\frac{\pi}{4}} - \int_{-\frac{\pi}{4}}^{\frac{\pi}{4}} \frac{x \sin(2x)}{2} dx = \frac{x^2 \sin(2x)}{2} \Big|_{-\frac{\pi}{4}}^{\frac{\pi}{4}} - \frac{x \cos(2x)}{2} \Big|_{-\frac{\pi}{4}}^{\frac{\pi}{4}} - \frac{1}{2} \int_{-\frac{\pi}{4}}^{\frac{\pi}{4}} \cos(2x) dx = \frac{1}{2} \cdot \frac{\pi^2}{16} \left(\sin\left(\frac{\pi}{2}\right) - \sin\left(-\frac{\pi}{2}\right)\right) - \frac{1}{2} \cdot \frac{\pi}{4} \left(\cos\left(\frac{\pi}{2}\right) + \cos\left(-\frac{\pi}{2}\right)\right) - \frac{1}{4} \left(\sin\left(\frac{\pi}{2}\right) - \sin\left(-\frac{\pi}{2}\right)\right) = \frac{\pi^2}{16} - \frac{1}{2}$
4. $P\left(|X| > \frac{\pi}{6}\right) = P\left(X > \frac{\pi}{6}\right) + P\left(X < -\frac{\pi}{6}\right) = 1 - F\left(\frac{\pi}{6}\right) + F\left(-\frac{\pi}{6}\right) = 1 - \frac{\sin\left(\frac{\pi}{3}\right) + 1}{2} + \frac{\sin\left(-\frac{\pi}{3}\right) + 1}{2} = 1 - \frac{\sqrt{3}}{4} - \frac{1}{2} - \frac{\sqrt{3}}{4} + \frac{1}{2} = 1 - \frac{\sqrt{3}}{2}$

# 6. zadatak
## Postavka
Fabrika proizvodi 80% proizvoda prve klase. Izabran je uzorak od 400 proizvoda.

1. Naći verovatnoću da je u uzorku broj prvoklasnih proizvoda između 310 i 360.
2. Odrediti najmanje $m \in \mathbb{N}$ takvo da je verovatnoća da se broj prvoklasnih proizvoda u uzorku razlikuje od očekivane vrednosti za više od $m$ manja od 5%.

(Zadatak pod 2) uraditi na 2 načina.)

## Rešenje

1. $X \sim Bin\left(400, \frac{4}{5}\right)$
    - $EX = np = 320$
    - $VarX = npq = 64$
    - $\frac{X - 320}{8} \sim \mathcal{N}(0, 1)$
    - $P(310 < X < 360) = P\left(\frac{310 - 320}{8} < Z < \frac{360 - 320}{8}\right) = P(-1.25 < Z < 5) = \Phi(5) - \Phi(-1.25) = 1 - 1 + 0.8944 = 0.8944$
2. 
    1. način (Čebišev):
        - $P(|X - EX| \geq m) \leq \frac{VarX}{m^2} = 0.05$
        - $m^2 = \frac{64}{0.05} = 1280$
        - $m \approx 36$
    2. način (centralna granična teorema):
        - $P(|X - EX| \geq m) = 1 - P(|X - EX| < m) = 1 - P(-m < X - EX < m) = 1 - P\left(-\frac{m}{8} < \frac{X - EX}{\sqrt{VarX}} < \frac{m}{8}\right) = 1 - \left(\Phi\left(\frac{m}{8}\right) - \Phi\left(-\frac{m}{8}\right)\right) = 2 - 2\Phi\left(\frac{m}{8}\right) < 0.05$
        - $1.95 < 2\Phi\left(\frac{m}{8}\right)$
        - $0.975 < \Phi\left(\frac{m}{8}\right)$
        - $1.95 < \frac{m}{8}$
        - $15.6 < m \implies m \approx 16$

# 7. zadatak
## Postavka
Uzorak obima 10 uzet je iz populacije čije obeležje ima normalnu raspodelu $\mathcal{N}(\mu, \sigma^2)$. Na osnovu uzorka konstatovano je da je $\hat{\mu} = 17,57$, a $s = 2,95$. Testirati hipotezu $H_0: \mu = 20$ protiv $H_1: \mu < 20$ sa nivoom značajnosti 0,01. Ponoviti testiranje koristeći interval poverenja, a zatim još jednom, koristeći $p$-vrednost.

## Rešenje

1. način
    - $C = (-\infty, c]$
    - $\frac{\hat{\mu} - 20}{\frac{2.95}{\sqrt{10}}} \sim t(9)$
    - $P\left(T \leq \frac{c - 20}{\frac{2.95}{\sqrt{10}}}\right) = F_T\left(\frac{c - 20}{\frac{2.95}{\sqrt{10}}}\right) = 0.01$
    - $F_T\left(\frac{20 - c}{\frac{2.95}{\sqrt{10}}}\right) = 0.99$
    - $\frac{20 - c}{\frac{2.95}{\sqrt{10}}} = 2.821$
    - $c \approx 17.368$
    - $17.57 > 17.368 \implies$ ne odbacujemo hipotezu
2. način: interval poverenja
    - $\mu \in \left(-\infty, 17.57 + \varepsilon_{0.99} \frac{2.95}{\sqrt{10}}\right] = (-\infty, 20.2016]$
    - $\mu = 20$ jeste u ovom intervalu, te ne odbacujemo hipotezu
3. način: $p$-vrednost
    - $p = P_{H_0}(\hat{\mu} \leq 17.57) = P\left(\frac{\hat{\mu} - 20}{\frac{2.95}{\sqrt{10}}} \leq \frac{17.57 - 20}{\frac{2.95}{\sqrt{10}}}\right) = F_T(-2.605) = 1 - F_T(2.605) \approx 1 - 0.985 = 0.015$
    - $p > 0.01 \implies$ ne odbacujemo hipotezu

# 8. zadatak
## Postavka
U tablici su predstavljeni podaci dobijeni iz uzorka obima 60:

| Vrednost promenljive | 0-0,75 | 0,75-1,25 | 1,25-1,75 | 1,75-2,25 | 2,25-2,75 | >2,75 |
| -------------------- | ------ | --------- | --------- | --------- | --------- | ----- |
| Broj slučajeva       | 11     | 24        | 13        | 2         | 6         | 4     |

Na osnovu datih podataka testirai^[sic]^ hipotezu da posmatrano obeležje ima $Exp(\lambda)$ raspodelu koristeći $\chi^2$ test, sa nivoom značajnosti 0,05.

## Rešenje

- $X \sim Exp(\lambda)$
- Pri oceni parametara metodom momenata uzimane su sredine intervala kao očekivane vrednosti, osim u poslednjem intervalu gde je uzeto 3 (za ovo nema matematičko objašnjenje).
- $EX = \frac{1}{\lambda} = \frac{\frac{3}{8} \cdot 11 + 24 + 1.5 \cdot 13 + 2 \cdot 2 + 2.5 \cdot 6 + 3 \cdot 4}{60} \approx 1.31$
- $\lambda \approx 0.763$
- $\chi^2_{5-1-1;0.95} = 7.815$

| Vrednost promenljive                | 0-0,75  | 0,75-1,25 | 1,25-1,75 | 1,75-2,25 | 2,25-2,75 | >2,75  |
| ----------------------------------- | ------  | --------- | --------- | --------- | --------- | ------ |
| Broj slučajeva                      | 11      | 24        | 13        | 2         | 6         | 4      |
| $p_{j0}$                            | 0.436   | 0.179     | 0.122     | 0.083     | 0.057     | 0.123  |
| $np_{j0}$                           | 26.145  | 10.738    | 7.332     | 5.007     | 3.419     | 7.36   |

Odavde možemo videti da pretposlednju kolonu treba spojiti sa nekom drugom, tako da je spajamo sa poslednjom.

| Vrednost promenljive                | 0-0,75  | 0,75-1,25 | 1,25-1,75 | 1,75-2,25 | >2,25 |
| ----------------------------------- | ------  | --------- | --------- | --------- | ------ |
| Broj slučajeva                      | 11      | 24        | 13        | 2         | 10     |
| $np_{j0}$                           | 26.145  | 10.738    | 7.332     | 5.007     | 10.779 |
| $(N_j - np_{j0})^2$                 | 229.363 | 175.89    | 32.125    | 9.04      | 0.607  |
| $\frac{(N_j - np_{j0})^2}{np_{j0}}$ | 8.773   | 16.381    | 4.382     | 1.806     | 0.056  |

Kako je zbir poslednjeg reda 31.397, što je veće od 7.815, dobijamo da ovi podaci nemaju eksponencijalnu raspodelu na datom uzorku.

Skripta za generisanje vrednosti iz tabele iznad:
```python
from math import exp

f = lambda x: 1 - exp(-0.763 * x)
# intervals = [0, 0.75, 1.25, 1.75, 2.25, 2.75, 10000000000000]
intervals = [0, 0.75, 1.25, 1.75, 2.25, 10000000000000]
# frequencies = [11, 24, 13, 2, 6, 4]
frequencies = [11, 24, 13, 2, 10]
n = 60
pj0 = []
npj0 = []
freq_diffs = []
scaled_freq_diffs = []

for i in range(1, len(intervals)):
    diff = f(intervals[i]) - f(intervals[i-1])
    pj0.append(diff)
    npj0.append(diff * n)
    freq_diff = (frequencies[i-1] - diff * n) ** 2
    freq_diffs.append(freq_diff)
    scaled_freq_diffs.append(freq_diff / (diff * n))

print([round(i, 3) for i in pj0])
print([round(i, 3) for i in npj0])
print([round(i, 3) for i in freq_diffs])
print([round(i, 3) for i in scaled_freq_diffs])
print(round(sum(scaled_freq_diffs), 3))
```

