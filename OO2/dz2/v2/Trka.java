package karting;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Trka {
	private Staza staza;
	double vreme;
	private List<StanjeVozila> vozila = new ArrayList<>();
	private class StanjeVozila {
		public Vozilo vozilo;
		public double put;
		public double vreme;
		public int plasman;
		StanjeVozila(Vozilo vozilo) {
			this.vozilo = vozilo;
		}
	}
	public Trka(Staza staza) {
		this.staza = staza;
	}
	public void dodajVozilo(Vozilo v) {
		if (vozila.size() == 8) {
			return;
		}
		vozila.add(new StanjeVozila(v));
	}
	public int brojVozila() {
		return vozila.size();
	}
	public void simuliraj(double vreme) {
		this.vreme += vreme;
		for (StanjeVozila sv : vozila) {
			Vozilo v = sv.vozilo;
			if (sv.plasman > 0) {
				continue;
			}
			double preostaloVreme = vreme;
			boolean ispoljiEfekte = (sv.put == 0);
			while (true) {
				Deonica trenDeonica;
				try {
					trenDeonica = staza.deonicaNaDuzini(sv.put);
				} catch (GGraniceStaze g) {
					// Došli smo do kraja.
					sv.plasman = Collections.max(vozila, (sv1, sv2) -> sv1.plasman - sv2.plasman).plasman + 1;
					break;
				}
				if (ispoljiEfekte) {
					for (int i = 0; i < trenDeonica.brojSpecificnosti(); ++i) {
						try {
							trenDeonica.dohvSpecificnost(i).ispoljiEfekat(v);
						} catch (GNeodgovarajuciObjekat g) {
							throw new InternalError("Ovo se neće desiti", g);
						}
					}
					ispoljiEfekte = false;
				}
				double duzinaCeleDeonice = trenDeonica.dohvDuzinu();
				double pocetakDeonice;
				try {
					pocetakDeonice = staza.udaljenostDeonice(trenDeonica);
				} catch (GDeonicaStaze g) {
					throw new InternalError("Ovo se neće desiti", g);
				}
				double trenutnoPredjenPutDeonice = sv.put - pocetakDeonice;
				double putDeoniceZaPrelazenje = duzinaCeleDeonice - trenutnoPredjenPutDeonice;
				double vremeZaCeluDeonicu = v.izracunajVreme(putDeoniceZaPrelazenje);
				if (vremeZaCeluDeonicu > preostaloVreme) {
					// Došli smo do sredine jedne deonice.
					sv.put += v.pomeriVozilo(preostaloVreme);
					sv.vreme += preostaloVreme;
					break;
				} else {
					// Završili smo jednu deonicu.
					sv.put += v.pomeriVozilo(vremeZaCeluDeonicu);
					sv.vreme += vremeZaCeluDeonicu;
					for (int i = 0; i < trenDeonica.brojSpecificnosti(); ++i) {
						try {
							trenDeonica.dohvSpecificnost(i).ponistiEfekat(v);
						} catch (GNeodgovarajuciObjekat g) {
							throw new InternalError("Ovo se neće desiti", g);
						}
					}
					ispoljiEfekte = true;
					preostaloVreme -= vremeZaCeluDeonicu;
				}
			}
		}
	}
	public int dohvatiPlasman(Vozilo v) throws GNepostojeceVozilo {
		for (StanjeVozila sv : vozila) {
			if (sv.vozilo == v) {
				return sv.plasman;
			}
		}
		throw new GNepostojeceVozilo();
	}
	public double dohvatiPredjeniPut(Vozilo v) throws GNepostojeceVozilo {
		for (StanjeVozila sv : vozila) {
			if (sv.vozilo == v) {
				return sv.put;
			}
		}
		throw new GNepostojeceVozilo();
	}
	public boolean zavrsiloTrku(Vozilo v) throws GNepostojeceVozilo {
		for (StanjeVozila sv : vozila) {
			if (sv.vozilo == v) {
				return sv.plasman != 0;
			}
		}
		throw new GNepostojeceVozilo();
	}
	@Override
	public String toString() {
		StringBuilder sb = new StringBuilder();
		sb.append(staza.dohvIme());
		sb.append(" [");
		sb.append(vreme);
		sb.append("s]\n");
		vozila.sort((sv1, sv2) -> sv1.plasman - sv2.plasman);
		for (StanjeVozila sv : vozila) {
			if (sv.plasman == 0) {
				continue;
			}
			sb.append(sv.plasman);
			sb.append(". ");
			sb.append(sv.vozilo);
			sb.append(" [");
			sb.append(sv.vreme);
			sb.append("s]\n");
		}
		return sb.toString();
	}
}
