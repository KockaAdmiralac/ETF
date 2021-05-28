package karting;

import java.util.ArrayList;
import java.util.List;

public class Staza {
	private List<Deonica> deonice = new ArrayList<>();
	private String ime;
	public Staza(String ime) {
		this.ime = ime;
	}
	public String dohvIme() {
		return ime;
	}
	public void dodajDeonicu(Deonica d) throws GPrvaDeonica {
		if (d.brojSpecificnosti() > 0 && deonice.size() == 0) {
			throw new GPrvaDeonica();
		}
		deonice.add(d);
	}
	public double duzina() {
		double duzina = 0;
		for (Deonica d : deonice) {
			duzina += d.dohvDuzinu();
		}
		return duzina;
	}
	public Deonica deonicaNaDuzini(double duzina) throws GGraniceStaze {
		double trenutnaDuzina = 0;
		for (Deonica d : deonice) {
			if (trenutnaDuzina <= duzina && duzina < trenutnaDuzina + d.dohvDuzinu()) {
				return d;
			}
			trenutnaDuzina += d.dohvDuzinu();
		}
		throw new GGraniceStaze();
	}
	public double udaljenostDeonice(Deonica d) throws GDeonicaStaze {
		double udaljenost = 0;
		for (Deonica d2 : deonice) {
			if (d == d2) {
				return udaljenost;
			}
			udaljenost += d2.dohvDuzinu();
		}
		throw new GDeonicaStaze();
	}
	@Override
	public String toString() {
		StringBuilder sb = new StringBuilder();
		sb.append(ime);
		sb.append(" )");
		sb.append(duzina());
		sb.append("m)\n");
		for (Deonica d : deonice) {
			sb.append(d);
			sb.append("\n");
		}
		return sb.toString();
	}
}
