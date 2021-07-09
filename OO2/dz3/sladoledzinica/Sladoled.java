package sladoledzinica;

import java.util.LinkedHashMap;
import java.util.Map;

public class Sladoled {
	private static class KolicinaUkusa {
		Ukus ukus;
		int kolicina;
		KolicinaUkusa(Ukus ukus, int kolicina) {
			this.ukus = ukus;
			this.kolicina = kolicina;
		}
	}
	private int velicinaCase;
	private int trenutnaKolicina = 0;
	private Map<String, KolicinaUkusa> ukusi = new LinkedHashMap<>();
	public Sladoled(int velicinaCase) {
		this.velicinaCase = velicinaCase;
	}
	public void dodajUkus(Ukus ukus, int kolicina) {
		if (trenutnaKolicina + kolicina > velicinaCase) {
			kolicina = velicinaCase - trenutnaKolicina;
		}
		trenutnaKolicina += kolicina;
		if (ukusi.containsKey(ukus.dohvNaziv())) {
			ukusi.get(ukus.dohvNaziv()).kolicina += kolicina;
		} else {
			ukusi.put(ukus.dohvNaziv(), new KolicinaUkusa(ukus, kolicina));
		}
	}
	@Override
	public String toString() {
		StringBuilder sb = new StringBuilder();
		for (KolicinaUkusa ku : ukusi.values()) {
			sb.append(ku.kolicina);
			sb.append("ml");
			sb.append(ku.ukus);
			sb.append(" ");
		}
		return sb.toString();
	}
	boolean pun() {
		return trenutnaKolicina == velicinaCase;
	}
}
