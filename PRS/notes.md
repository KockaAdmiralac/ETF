## Operativna memorija
- `s`: veličina posla
    1. Model jednakih veličina (svi poslovi jednakih veličina)
    2. Sve veličine jednako verovatne (srednja veličina je `a`)
    3. Eksponencijalna raspodela
- `t`: vreme zadržavanja programa u memoriji
    1. `t = const`
    2. `t = f(s)`
- Monoprogramski sistem:
    - M = 1, normalizujemo
    - Prosečno iskorišćenje memorije: `(s1t1 + s2t2 + ...)/(t1 + t2 + ...)`
        - U slučaju `t = K * S`: $\overline{U} = \frac{\overline{S^2}}{\overline{S}}$
            - Ako je uniformna raspodela onda je $\overline{S} = a$, a $\overline{S^2} = \frac{1}{2a} \int_a^{2a} S^2 \cdot ds = \frac{s^3}{3}|_a^{2a} = \frac{4a^2}{3}$
            - Ovo znači da je maksimalno iskorišćenje u ovakvom sistemu 2/3
- Statičke particije:
    - Normalizujemo po veličini veće particije
    - Mali programi su oni koji mogu u malu particiju
    - Jednako verovatne veličine programa:
        - `x = xs/xb`, normalizujemo po veličini veće particije
        - Razmatramo za `t = const` i ako bafer poslova nikad nije prazan
        - $\overline{U_{bs}} = \frac{\frac{0 + x}{2} + \frac{x + 1}{2}}{1 + x}$
        - $\overline{U_{ss}} = \frac{\frac{0 + x}{2} + \frac{0 + x}{2}}{1 + x}$
        - $\overline{U_{be}} = \frac{0 + \frac{x + 1}{2}}{1 + x}$
        - SE ne može da se desi sa ovom pretpostavkom
        - Promene su trenutne i dešavaju se samo u diskretnim trenucima
        - $\overline{U} = p_{bs} \cdot U_{bs} + ...$
        - Gledaju se prelazi između stanja za određivanje verovatnoće
        - $p_s = x, p_b = 1 - x$, za svaki prelaz verovatnoća je proizvod verovatnoća veličina tih programa, obratiti pažnju na prelaze iz BE
    - Markovljevi lanci:
        - Za svako stanje mašine verovatnoća da se nađe u tom stanju jeste verovatnoća susednih stanja pomnožena sa verovatnoćom prelaza iz tog stanja
