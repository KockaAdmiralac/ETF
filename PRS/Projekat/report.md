---
title: Domaći zadatak iz Performansi računarskih sistema
author: Luka Simić
date: Jun 2023
geometry: margin=2cm
output: pdf_document
classoption: twoside
header-includes: \usepackage[croatian]{babel}\usepackage{subfig}\usepackage{float}\usepackage{fancyhdr}\usepackage{imakeidx}\usepackage{listings}\usepackage{svg}\makeindex[intoc]\graphicspath{{./}}
pdf-engine: pdflatex
urlcolor: blue
---

# Uvod
Korak pre rešavanja ovog problema jeste skicirati kako izgleda ceo sistem opisan postavkom domaćeg zadatka. Dijagram ovog sistema može se videti na slici 1.

![Dijagram sistema opisanog u postavci domaćeg zadatka.](diagram.svg)

Možemo pokušati da ručno rešimo ovaj problem za $K = 2$:

$$\lambda_p = \alpha + 0.3\lambda_{d1} + 0.3\lambda_{d2} + 0.3\lambda_{d3} + 0.3\lambda_p$$
$$\lambda_{d1} = 0.15\lambda_p + 0.2\lambda_{d1}$$
$$\lambda_{d2} = 0.1\lambda_p + 0.2\lambda_{d2}$$
$$\lambda_{d3} = 0.05\lambda_p + 0.2\lambda_{d3}$$
$$\lambda_{dk} = \lambda_{dk1} + \lambda_{dk2} = 0.5\lambda_p + 0.5\lambda_{d1} + 0.5\lambda_{d2} + 0.5\lambda_{d3} = \alpha$$

Iz ovog sistema jednačina dobijamo:

$$\lambda_p \approx 1.45\alpha$$
$$\lambda_{d1} \approx 0.27\alpha$$
$$\lambda_{d2} \approx 0.18\alpha$$
$$\lambda_{d3} \approx 0.09\alpha$$
$$\lambda_{dk1} = \lambda_{dk2} = 0.5\alpha$$

Ova rešenja nam mogu poslužiti za upoređivanje sa analitičkom implementacijom projekta. Jedno važno zapažanje koje možemo napraviti u ovom trenutku jeste da nam parametar $K$ utiče samo na deo sistema sa korisničkim diskovima, u koji ulazi protok $\alpha$, i iz kog isti taj protok izlazi, tako da ne očekujemo da se ostatak sistema menja u zavisnosti od ovog parametra.

# Analitičko rešenje
Matrična jednačina koja predstavlja način na koji možemo dobiti protoke, čije se izvođenje može pronaći na domaćem iz otvorenih mreža, glasi:

$$\Lambda = \left(I - P^T\right)^{-1} A$$

gde:

- $\Lambda$ označava matricu sa traženim protocima,
- $I$ označava jediničnu matricu odgovarajuće veličine,
- $P$ označava matricu verovatnoća prelaza posla sa jednog na drugi server, i
- $A$ označava matricu ulaznog toka za svaki server (izražen u procentima toka $\alpha$, kojeg u ovom trenutku još uvek ne poznajemo).

Matrica $P$ za parametar $K = 2$ je prikazana u tabeli 1. U samom programu, gornja leva $4 \times 4$ podmatrica biće uvek ista, dok se desna kolona za korisničke diskova mora popuniti vrednostima $\frac{1}{2K}$, a donji redovi za korisničke diskove nulama (jer se nakon korisničkih diskova izlazi iz sistema). Sa ovom matricom izgenerisanom, spremni smo da odredimo sve protoke u sistemu.

| od/do     | $P$ | $D_1$ | $D_2$ | $D_3$ | $D_{k_1}$ | $D_{k_2}$ |
| --------- | --- | ----- | ----- | ----- | --------- | --------- |
| $P$       | 0.2 | 0.15  | 0.1   | 0.05  | 0.25      | 0.25      |
| $D_1$     | 0.3 | 0.2   | 0     | 0     | 0.25      | 0.25      |
| $D_2$     | 0.3 | 0     | 0.2   | 0     | 0.25      | 0.25      |
| $D_3$     | 0.3 | 0     | 0     | 0.2   | 0.25      | 0.25      |
| $D_{k_1}$ | 0   | 0     | 0     | 0     | 0         | 0         |
| $D_{k_2}$ | 0   | 0     | 0     | 0     | 0         | 0         |
: Matrica $P$ u analitičkom rešenju zadatka za parametar $K = 2$.

Sledeći zadatak, određivanje $\alpha_{max}$ u zavisnosti od $K$, obavlja se tako što za svaku vrednost $K$ proverimo koliki je maksimalni kapacitet svakog servera kao $\frac{1}{S\lambda}$ gde je $S$ serverovo vreme obrade posla a $\lambda$ vrednost iz izračunate matrice $\Lambda$ koja odgovara tom serveru. Rezultati ovog podzadatka nam kažu da su za $K = 2$ usko grlo korisnički diskovi, dok je za sve ostale usko grlo procesor (ova činjenica ne zavisi od parametra $r$). Vrednosti $\alpha_{max}$ mogu se videti na slici 2.

Traženi grafici iskorišćenja i vremena odziva mogu se pronaći na slikama 3, 4 i 5.

![Grafik zavisnosti $\alpha_{max}$ od $K$.](results/amaxes_analytical.svg)

![Grafik zavisnosti iskorišćenja servera od $K$ i $r$.](results/usage_analytical.svg)

![Grafik zavisnosti vremena odziva servera od $K$ i $r$.](results/response_analytical.svg)

![Grafik zavisnosti vremena odziva sistema od $K$ i $r$.](results/system_response_analytical.svg)

# Simulacija
Simulacija se odvija u ekvidistantnim vremenskim trenucima, nazvanim otkucaji (*tick*). Jedan otkucaj je 0.25ms (kako bi svako od zadatih vremena obrade bilo deljivo sa dužinom otkucaja). Unutar simulacije se sve mere, osim verovatnoća, izražavaju u celim brojevima kako ne bi došlo do greški zbog [nepreciznosti IEEE 754 realnih brojeva](https://0.30000000000000004.com/).

Svaki server reprezentuje se jednim objektom tipa `Server`. Serveri se stvaraju sa zadatim vremenom obrade zahteva i intenzitetom ulaznog toka (podrazumevano 0). U sebi čuvaju veze ka ostalim serverima sa njihovim verovatnoćama prelaza kao i red poslova koji se trenutno nalaze u redu i na obradi. Poslovi su reprezentovani brojem otkucaja u kojem su stvoreni, dok je Poasonov proces predstavljen objektima tipa `PoissonProcess`. Ovi objekti takođe imaju još četiri metode:

- `connect(server: Server, probability: float)`: postavlja izlaznu granu od tog servera do zadatog, sa zadatom verovatnoćom prelaza,
- `update(tick: int, stats_response_time: List[int])`: simulira ulazni tok (Poasonov proces dodavanja poslova u red), vreme obrade posla (Poasonov proces izbacivanja poslova iz reda i određivanja na koji server prelazi) i računa statistiku na nivou otkucaja (broj obrađenih poslova, trenutni broj poslova, da li trenutno ima poslova i vreme odziva),
- `update_stats()`: ažurira statistiku na nivou intervala za merenje statistike (jedna sekunda), prenoseći podatke iz statistike izmerene na nivou otkucaja (ovo se obavlja kako bi se smanjila količina memorije potrebna za čuvanje statistike, jer otkucaja ima dosta), i
- `get_stats()`: vraća statistiku na nivou intervala za merenje statistike.

Statistike koje se mere su sledeće:

- prosečan broj poslova na severu ($J$): svakog otkucaja meri se koliko poslova je trenutno na serveru i to se na kraju usrednji po otkucaju,
- prosečno iskorišćenje ($U$): svakog otkucaja meri se da li ima poslova na serveru i to se na kraju usrednji po otkucaju,
- protok ($X$): svaki put kad se obradi jedan posao povećava se broj obrađenih poslova i to se na kraju usrednji po intervalu merenja statistike, i
- vreme odziva ($T$): svaki put kad jedan posao izađe iz sistema računa se koliko mu je trebalo otkucaja od ulaska do izlaska (podsetnik: poslovi su reprezentovani kao brojevi otkucaja njihovog ulaska) i to se na kraju usrednji po intervalu merenja statistike.

Parametri simulacije su $K$, $r$ i vreme trajanja simulacije. Simulacija određuje $\alpha_{max}$ na osnovu analitičkih rezultata (jer nije drugačije rečeno u zadatku), stvara sve potrebne servere sa svojim vremenima obrade (izvršene su konverzije u otkucaje), poveže ih sa zadatim verovatnoćama prelaza, pokrene simulaciju sa ažuriranjem stanja svih servera u svakom otkucaju i ažuriranjem statistike svake sekunde i na kraju izračuna $J$, $X$ i $U$ svih servera i $T$ sistema.

Glavni program pokreće simulacije sa traženim parametrima $K$ i $r$ kao i zadatim brojem iteracija i vremena simulacije. Sve simulacije se pokreću kao nezavisni procesi (korišćenjem `multiprocessing` modula) raspoređeni na broj logičkih jezgara procesora trenutnog računara. Vreme izvršavanja za 100 iteracija (ukupno 1600 simulacija) na `rtidev5.etf.rs` mašini je bilo jedan sat i 41 minut.

# Analiza
Traženi dijagrami priloženi su u odeljku sa analitičkim rezultatima. Ono što se može primetiti jeste da, kao što smo očekivali, iskorišćenja i vremena odziva delova sistema koji nisu korisnički diskovi ne zavisi od $K$ već samo od $\alpha$ (razlikuju se samo slučajevi $K = 2$ i $K > 2$ jer se za njih dobija različito $\alpha_{max}$). Vidimo, takođe, da vreme odziva i iskorišćenje opada za korisničke diskove kako dodajemo više korisničkih diskova, što takođe ima smisla (poslovi će se rasporediti na drugim diskovima). Vreme odziva sistema se ne menja na značajan način u zavisnosti od $K$, jer $K$ svakako utiče samo na vreme odziva dela sistema sa korisničkim diskovima. Ono što, doduše, možemo primetiti, jeste kako je vreme odziva celog sistema značajno palo između $K = 2$ i $K = 3$ za $r = 0.99$, zato što u tom slučaju deo sistema sa korisničkim diskovima prestaje da bude usko grlo.

Tabelarni prikaz relativnih odstupanja simulacionih rezultata od analitičkih može se videti u tabelama 2, 3, 4, 5, 6, 7 i 8. Relativno odstupanje računato je kao $\frac{|R_a - R_s|}{R_a}$, gde je $R_a$ analitički a $R_s$ simulacioni rezultat. Prilikom usrednjavanja simulacionih rezultata nije vršeno izračunavanje standardne devijacije radi određivanja značajnih cifara rezultata, jer nije ni bilo traženo. Tražene tabele moguće je videti i u [Google Sheets obliku](https://docs.google.com/spreadsheets/d/1545fzj167WW6sUHQKttCCBmWZr4ADAv03GcoEwOaZN4), kao i u tabeli priloženoj uz ovaj izveštaj.

Kao što se može primetiti, rezultati simulacije ne odstupaju značajno od analitičkih, osim na označenim mestima. Označena mesta se, naime, nalaze u redovima sa $r = 0.99$, što znači da je sistem skoro pa izveden iz stacionarnog stanja. Ovo suštinski znači da kako $r$ teži jedinici, naše stohastičke pretpostavke prestaju da važe, jer procesor sve teže uspeva da na vreme obradi svoje poslove i dužina njegovog reda za čekanje može značajno da varira.

Možemo takođe videti (malo teže iz samog izveštaja, a malo lakše iz priloženih tabela) da su rezultati 100 iteracija simulacije generalno bolji od rezultata jedne iteracije, osim u delovima gde je i jedna iteracija dosta odstupala. Iz ovoga zaključujemo da je usrednjavanje sto iteracija pomoglo tome da se šum uveden od nasumičnosti simulacije umanji i vrednosti približe očekivanim srednjim vrednostima izračunatim analitički, osim na mestima gde su naše stohastičke pretpostavke svakako prestajale da važe. Sa ovakvim rezultatima možemo biti poprilično sigurni da je domaći zadatak uspešno rešen.

| $K$ | $r$  | $U_p$  | $U_{d_1}$ | $U_{d_2}$ | $U_{d_3}$ | $U_{dk_1}$ | $U_{dk_2}$ | $U_{dk_3}$ | $U_{dk_4}$ | $U_{dk_5}$ |
| --- | ---- | ------ | --------- | --------- | --------- | ---------- | ---------- | ---------- | ---------- | ---------- |
| 2   | 0.25 | 0.0155 | 0.0234    | 0.0110    | 0.0389    | 0.0077     | 0.0075     | -          | -          | -          |
| 2   | 0.5  | 0.0011 | 0.0088    | 0.0209    | 0.0085    | 0.0073     | 0.0008     | -          | -          | -          |
| 2   | 0.77 | 0.0156 | 0.0028    | 0.0127    | 0.0254    | 0.0014     | 0.0124     | -          | -          | -          |
| 2   | 0.99 | 0.0124 | 0.0035    | 0.0111    | 0.0072    | 0.0072     | 0.0018     | -          | -          | -          |
| 3   | 0.25 | 0.0052 | 0.0137    | 0.0079    | 0.0398    | 0.0215     | 0.0194     | 0.0158     | -          | -          |
| 3   | 0.5  | 0.0016 | 0.0135    | 0.0106    | 0.0016    | 0.0032     | 0.0037     | 0.0033     | -          | -          |
| 3   | 0.77 | 0.0018 | 0.0186    | 0.0135    | 0.0278    | 0.0229     | 0.0016     | 0.0006     | -          | -          |
| 3   | 0.99 | 0.0101 | 0.0074    | 0.0073    | 0.0050    | 0.0173     | 0.0006     | 0.0085     | -          | -          |
| 4   | 0.25 | 0.0125 | 0.0269    | 0.0026    | 0.0332    | 0.0344     | 0.0075     | 0.0081     | 0.0161     | -          |
| 4   | 0.5  | 0.0108 | 0.0090    | 0.0065    | 0.0076    | 0.0009     | 0.0021     | 0.0143     | 0.0113     | -          |
| 4   | 0.77 | 0.0089 | 0.0030    | 0.0057    | 0.0033    | 0.0033     | 0.0040     | 0.0039     | 0.0137     | -          |
| 4   | 0.99 | 0.0100 | 0.0095    | 0.0108    | 0.0396    | 0.0078     | 0.0174     | 0.0097     | 0.0170     | -          |
| 5   | 0.25 | 0.0017 | 0.0037    | 0.0054    | 0.0436    | 0.0131     | 0.0050     | 0.0276     | 0.0262     | 0.0095     |
| 5   | 0.5  | 0.0067 | 0.0002    | 0.0067    | 0.0032    | 0.0063     | 0.0060     | 0.0031     | 0.0048     | 0.0152     |
| 5   | 0.77 | 0.0087 | 0.0093    | 0.0105    | 0.0084    | 0.0191     | 0.0033     | 0.0028     | 0.0034     | 0.0040     |
| 5   | 0.99 | 0.0099 | 0.0210    | 0.0138    | 0.0028    | 0.0114     | 0.0139     | 0.0167     | 0.0042     | 0.0048     |
: Relativno odstupanje simulacionih (jedna iteracija) od analitičkih rezultata za iskorišćenja svih servera.

| $K$ | $r$  | $X_p$  | $X_{d_1}$ | $X_{d_2}$ | $X_{d_3}$ | $X_{dk_1}$ | $X_{dk_2}$ | $X_{dk_3}$ | $X_{dk_4}$ | $X_{dk_5}$ |
| --- | ---- | ------ | --------- | --------- | --------- | ---------- | ---------- | ---------- | ---------- | ---------- |
| 2   | 0.25 | 0.0048 | 0.0117    | 0.0125    | 0.0253    | 0.0064     | 0.0019     | -          | -          | -          |
| 2   | 0.5  | 0.0017 | 0.0124    | 0.0063    | 0.0313    | 0.0018     | 0.0033     | -          | -          | -          |
| 2   | 0.77 | 0.0070 | 0.0013    | 0.0051    | 0.0176    | 0.0043     | 0.0071     | -          | -          | -          |
| 2   | 0.99 | 0.0011 | 0.0034    | 0.0059    | 0.0079    | 0.0000     | 0.0055     | -          | -          | -          |
| 3   | 0.25 | 0.0043 | 0.0071    | 0.0153    | 0.0080    | 0.0016     | 0.0048     | 0.0133     | -          | -          |
| 3   | 0.5  | 0.0022 | 0.0026    | 0.0045    | 0.0027    | 0.0033     | 0.0001     | 0.0033     | -          | -          |
| 3   | 0.77 | 0.0109 | 0.0156    | 0.0119    | 0.0241    | 0.0192     | 0.0101     | 0.0018     | -          | -          |
| 3   | 0.99 | 0.0105 | 0.0052    | 0.0117    | 0.0015    | 0.0125     | 0.0038     | 0.0116     | -          | -          |
| 4   | 0.25 | 0.0080 | 0.0129    | 0.0020    | 0.0342    | 0.0049     | 0.0107     | 0.0032     | 0.0007     | -          |
| 4   | 0.5  | 0.0070 | 0.0134    | 0.0097    | 0.0101    | 0.0042     | 0.0032     | 0.0062     | 0.0152     | -          |
| 4   | 0.77 | 0.0058 | 0.0000    | 0.0048    | 0.0063    | 0.0009     | 0.0110     | 0.0036     | 0.0128     | -          |
| 4   | 0.99 | 0.0119 | 0.0069    | 0.0077    | 0.0226    | 0.0116     | 0.0191     | 0.0079     | 0.0131     | -          |
| 5   | 0.25 | 0.0027 | 0.0041    | 0.0041    | 0.0280    | 0.0057     | 0.0103     | 0.0166     | 0.0087     | 0.0227     |
| 5   | 0.5  | 0.0001 | 0.0082    | 0.0038    | 0.0028    | 0.0075     | 0.0069     | 0.0008     | 0.0010     | 0.0026     |
| 5   | 0.77 | 0.0045 | 0.0001    | 0.0076    | 0.0030    | 0.0137     | 0.0001     | 0.0014     | 0.0049     | 0.0062     |
| 5   | 0.99 | 0.0090 | 0.0190    | 0.0123    | 0.0048    | 0.0141     | 0.0069     | 0.0070     | 0.0005     | 0.0080     |
: Relativno odstupanje simulacionih (jedna iteracija) od analitičkih rezultata za protok svih servera.

| $K$ | $r$  | $J_p$       | $J_{d_1}$ | $J_{d_2}$ | $J_{d_3}$ | $J_{dk_1}$ | $J_{dk_2}$ | $J_{dk_3}$ | $J_{dk_4}$ | $J_{dk_5}$ |
| --- | ---- | ----------- | --------- | --------- | --------- | ---------- | ---------- | ---------- | ---------- | ---------- |
| 2   | 0.25 | 0.0182      | 0.0190    | 0.0156    | 0.0432    | 0.0151     | 0.0101     | -          | -          | -          |
| 2   | 0.5  | 0.0030      | 0.0088    | 0.0223    | 0.0097    | 0.0091     | 0.0082     | -          | -          | -          |
| 2   | 0.77 | 0.0478      | 0.0027    | 0.0153    | 0.0322    | 0.0240     | 0.0690     | -          | -          | -          |
| 2   | 0.99 | 0.0567      | 0.0112    | 0.0146    | 0.0168    | **1.3782** | 0.1575     | -          | -          | -          |
| 3   | 0.25 | 0.0113      | 0.0189    | 0.0028    | 0.0311    | 0.0231     | 0.0225     | 0.0094     | -          | -          |
| 3   | 0.5  | 0.0067      | 0.0109    | 0.0219    | 0.0031    | 0.0026     | 0.0134     | 0.0069     | -          | -          |
| 3   | 0.77 | 0.0102      | 0.0215    | 0.0180    | 0.0240    | 0.1070     | 0.0140     | 0.0110     | -          | -          |
| 3   | 0.99 | **13.4516** | 0.0111    | 0.0052    | 0.0044    | 0.1901     | 0.0109     | 0.0396     | -          | -          |
| 4   | 0.25 | 0.0146      | 0.0348    | 0.0076    | 0.0228    | 0.0457     | 0.0003     | 0.0095     | 0.0159     | -          |
| 4   | 0.5  | 0.0279      | 0.0148    | 0.0082    | 0.0085    | 0.0160     | 0.0119     | 0.0297     | 0.0089     | -          |
| 4   | 0.77 | 0.0189      | 0.0104    | 0.0146    | 0.0117    | 0.0118     | 0.0110     | 0.0145     | 0.0248     | -          |
| 4   | 0.99 | **17.9794** | 0.0130    | 0.0021    | 0.0492    | 0.0427     | 0.0366     | 0.0470     | 0.0478     | -          |
| 5   | 0.25 | 0.0013      | 0.0110    | 0.0020    | 0.0442    | 0.0184     | 0.0054     | 0.0335     | 0.0290     | 0.0036     |
| 5   | 0.5  | 0.0127      | 0.0024    | 0.0030    | 0.0119    | 0.0222     | 0.0015     | 0.0014     | 0.0039     | 0.0231     |
| 5   | 0.77 | 0.0114      | 0.0116    | 0.0080    | 0.0022    | 0.0328     | 0.0049     | 0.0027     | 0.0059     | 0.0047     |
| 5   | 0.99 | **13.7947** | 0.0395    | 0.0234    | 0.0059    | 0.0262     | 0.0383     | 0.0262     | 0.0090     | 0.0110     |
: Relativno odstupanje simulacionih (jedna iteracija) od analitičkih rezultata za prosečan broj poslova svih servera.

| $K$ | $r$  | $U_p$  | $U_{d_1}$ | $U_{d_2}$ | $U_{d_3}$ | $U_{dk_1}$ | $U_{dk_2}$ | $U_{dk_3}$ | $U_{dk_4}$ | $U_{dk_5}$ |
| --- | ---- | ------ | --------- | --------- | --------- | ---------- | ---------- | ---------- | ---------- | ---------- |
| 2   | 0.25 | 0.0037 | 0.0023    | 0.0005    | 0.0077    | 0.0004     | 0.0002     | -          | -          | -          |
| 2   | 0.5  | 0.0051 | 0.0004    | 0.0011    | 0.0004    | 0.0047     | 0.0052     | -          | -          | -          |
| 2   | 0.77 | 0.0128 | 0.0037    | 0.0035    | 0.0012    | 0.0096     | 0.0089     | -          | -          | -          |
| 2   | 0.99 | 0.0118 | 0.0016    | 0.0022    | 0.0051    | 0.0028     | 0.0027     | -          | -          | -          |
| 3   | 0.25 | 0.0044 | 0.0079    | 0.0047    | 0.0051    | 0.0035     | 0.0030     | 0.0048     | -          | -          |
| 3   | 0.5  | 0.0073 | 0.0006    | 0.0000    | 0.0007    | 0.0036     | 0.0033     | 0.0032     | -          | -          |
| 3   | 0.77 | 0.0071 | 0.0074    | 0.0066    | 0.0115    | 0.0033     | 0.0042     | 0.0024     | -          | -          |
| 3   | 0.99 | 0.0098 | 0.0112    | 0.0120    | 0.0130    | 0.0067     | 0.0058     | 0.0061     | -          | -          |
| 4   | 0.25 | 0.0039 | 0.0067    | 0.0023    | 0.0067    | 0.0030     | 0.0037     | 0.0014     | 0.0049     | -          |
| 4   | 0.5  | 0.0075 | 0.0018    | 0.0011    | 0.0016    | 0.0026     | 0.0018     | 0.0002     | 0.0019     | -          |
| 4   | 0.77 | 0.0065 | 0.0095    | 0.0096    | 0.0125    | 0.0050     | 0.0058     | 0.0054     | 0.0056     | -          |
| 4   | 0.99 | 0.0098 | 0.0126    | 0.0100    | 0.0143    | 0.0075     | 0.0083     | 0.0092     | 0.0087     | -          |
| 5   | 0.25 | 0.0034 | 0.0051    | 0.0016    | 0.0057    | 0.0045     | 0.0017     | 0.0025     | 0.0008     | 0.0038     |
| 5   | 0.5  | 0.0070 | 0.0022    | 0.0013    | 0.0000    | 0.0011     | 0.0005     | 0.0009     | 0.0005     | 0.0006     |
| 5   | 0.77 | 0.0067 | 0.0093    | 0.0077    | 0.0058    | 0.0064     | 0.0071     | 0.0070     | 0.0068     | 0.0072     |
| 5   | 0.99 | 0.0098 | 0.0106    | 0.0128    | 0.0119    | 0.0109     | 0.0104     | 0.0098     | 0.0092     | 0.0092     |
: Relativno odstupanje simulacionih (100 iteracija) od analitičkih rezultata za iskorišćenja svih servera.

| $K$ | $r$  | $X_p$  | $X_{d_1}$ | $X_{d_2}$ | $X_{d_3}$ | $X_{dk_1}$ | $X_{dk_2}$ | $X_{dk_3}$ | $X_{dk_4}$ | $X_{dk_5}$ |
| --- | ---- | ------ | --------- | --------- | --------- | ---------- | ---------- | ---------- | ---------- | ---------- |
| 2   | 0.25 | 0.0022 | 0.0028    | 0.0036    | 0.0040    | 0.0025     | 0.0025     | -          | -          | -          |
| 2   | 0.5  | 0.0052 | 0.0054    | 0.0047    | 0.0052    | 0.0045     | 0.0055     | -          | -          | -          |
| 2   | 0.77 | 0.0067 | 0.0061    | 0.0064    | 0.0060    | 0.0067     | 0.0064     | -          | -          | -          |
| 2   | 0.99 | 0.0004 | 0.0010    | 0.0004    | 0.0013    | 0.0021     | 0.0018     | -          | -          | -          |
| 3   | 0.25 | 0.0001 | 0.0005    | 0.0005    | 0.0012    | 0.0003     | 0.0003     | 0.0011     | -          | -          |
| 3   | 0.5  | 0.0031 | 0.0041    | 0.0020    | 0.0048    | 0.0032     | 0.0032     | 0.0033     | -          | -          |
| 3   | 0.77 | 0.0056 | 0.0050    | 0.0052    | 0.0066    | 0.0059     | 0.0053     | 0.0051     | -          | -          |
| 3   | 0.99 | 0.0102 | 0.0099    | 0.0106    | 0.0106    | 0.0108     | 0.0099     | 0.0100     | -          | -          |
| 4   | 0.25 | 0.0001 | 0.0001    | 0.0012    | 0.0003    | 0.0004     | 0.0006     | 0.0002     | 0.0015     | -          |
| 4   | 0.5  | 0.0031 | 0.0028    | 0.0019    | 0.0020    | 0.0039     | 0.0036     | 0.0014     | 0.0031     | -          |
| 4   | 0.77 | 0.0063 | 0.0064    | 0.0063    | 0.0076    | 0.0057     | 0.0061     | 0.0065     | 0.0063     | -          |
| 4   | 0.99 | 0.0102 | 0.0106    | 0.0091    | 0.0106    | 0.0099     | 0.0104     | 0.0107     | 0.0102     | -          |
| 5   | 0.25 | 0.0004 | 0.0008    | 0.0029    | 0.0008    | 0.0000     | 0.0004     | 0.0004     | 0.0002     | 0.0008     |
| 5   | 0.5  | 0.0029 | 0.0025    | 0.0016    | 0.0030    | 0.0029     | 0.0035     | 0.0021     | 0.0032     | 0.0031     |
| 5   | 0.77 | 0.0059 | 0.0059    | 0.0061    | 0.0045    | 0.0054     | 0.0059     | 0.0061     | 0.0062     | 0.0061     |
| 5   | 0.99 | 0.0102 | 0.0094    | 0.0119    | 0.0087    | 0.0103     | 0.0106     | 0.0093     | 0.0101     | 0.0100     |
: Relativno odstupanje simulacionih (100 iteracija) od analitičkih rezultata za protok svih servera.

| $K$ | $r$  | $J_p$       | $J_{d_1}$ | $J_{d_2}$ | $J_{d_3}$ | $J_{dk_1}$ | $J_{dk_2}$ | $J_{dk_3}$ | $J_{dk_4}$ | $J_{dk_5}$ |
| --- | ---- | ----------- | --------- | --------- | --------- | ---------- | ---------- | ---------- | ---------- | ---------- |
| 2   | 0.25 | 0.0040      | 0.0020    | 0.0005    | 0.0084    | 0.0009     | 0.0004     | -          | -          | -          |
| 2   | 0.5  | 0.0104      | 0.0016    | 0.0012    | 0.0005    | 0.0105     | 0.0090     | -          | -          | -          |
| 2   | 0.77 | 0.0318      | 0.0052    | 0.0045    | 0.0014    | 0.0467     | 0.0403     | -          | -          | -          |
| 2   | 0.99 | 0.0478      | 0.0025    | 0.0021    | 0.0052    | 0.3628     | 0.2158     | -          | -          | -          |
| 3   | 0.25 | 0.0052      | 0.0087    | 0.0051    | 0.0058    | 0.0039     | 0.0050     | 0.0058     | -          | -          |
| 3   | 0.5  | 0.0179      | 0.0003    | 0.0004    | 0.0004    | 0.0063     | 0.0038     | 0.0073     | -          | -          |
| 3   | 0.77 | 0.0362      | 0.0094    | 0.0082    | 0.0127    | 0.0121     | 0.0127     | 0.0069     | -          | -          |
| 3   | 0.99 | **15.6016** | 0.0159    | 0.0171    | 0.0150    | 0.0666     | 0.0629     | 0.0671     | -          | -          |
| 4   | 0.25 | 0.0049      | 0.0075    | 0.0029    | 0.0076    | 0.0045     | 0.0030     | 0.0009     | 0.0060     | -          |
| 4   | 0.5  | 0.0180      | 0.0019    | 0.0010    | 0.0015    | 0.0057     | 0.0040     | 0.0007     | 0.0020     | -          |
| 4   | 0.77 | 0.0335      | 0.0128    | 0.0127    | 0.0132    | 0.0106     | 0.0120     | 0.0127     | 0.0107     | -          |
| 4   | 0.99 | **15.3568** | 0.0185    | 0.0139    | 0.0167    | 0.0246     | 0.0246     | 0.0314     | 0.0264     | -          |
| 5   | 0.25 | 0.0036      | 0.0051    | 0.0015    | 0.0062    | 0.0055     | 0.0019     | 0.0033     | 0.0009     | 0.0047     |
| 5   | 0.5  | 0.0161      | 0.0031    | 0.0017    | 0.0003    | 0.0015     | 0.0002     | 0.0028     | 0.0019     | 0.0002     |
| 5   | 0.77 | 0.0318      | 0.0120    | 0.0094    | 0.0071    | 0.0111     | 0.0110     | 0.0110     | 0.0133     | 0.0127     |
| 5   | 0.99 | **15.3438** | 0.0148    | 0.0160    | 0.0139    | 0.0259     | 0.0233     | 0.0197     | 0.0208     | 0.0183     |
: Relativno odstupanje simulacionih (100 iteracija) od analitičkih rezultata za prosečan broj poslova svih servera.

| K | r    | $T_1$       | $T_{100}$   |
| - | ---- | ----------- | ----------- |
| 2 | 0.25 | 0.0086      | 0.0031      |
| 2 | 0.5  | 0.0075      | 0.0045      |
| 2 | 0.77 | 0.0375      | 0.0329      |
| 2 | 0.99 | 0.6003      | 0.2843      |
| 3 | 0.25 | 0.0079      | 0.0043      |
| 3 | 0.5  | 0.0002      | 0.0055      |
| 3 | 0.77 | 0.0112      | 0.0091      |
| 3 | 0.99 | **10.2126** | **11.7786** |
| 4 | 0.25 | 0.0093      | 0.0030      |
| 4 | 0.5  | 0.0081      | 0.0044      |
| 4 | 0.77 | 0.0060      | 0.0125      |
| 4 | 0.99 | **16.1586** | **13.8317** |
| 5 | 0.25 | 0.0042      | 0.0028      |
| 5 | 0.5  | 0.0047      | 0.0029      |
| 5 | 0.77 | 0.0075      | 0.0136      |
| 5 | 0.99 | **12.7689** | **14.1521** |
: Relativno odstupanje simulacionih od analitičkih rezultata za vreme odziva sistema.
