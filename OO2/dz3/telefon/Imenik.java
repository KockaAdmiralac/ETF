package telefon;

import java.util.HashMap;
import java.util.Map;

public class Imenik extends ListaStavki {
	private static final long serialVersionUID = 1L;
	private Map<String, String> brojUIme = new HashMap<>();
	private Map<String, Broj> imeUBroj = new HashMap<>();
	@Override
	public void dodajStavku(Stavka s) {
		if (!(s instanceof Kontakt)) {
			return;
		}
		Kontakt k = (Kontakt) s;
		brojUIme.put(k.dohvBroj().toString(), k.dohvIme());
		imeUBroj.put(k.dohvIme(), k.dohvBroj());
		super.dodajStavku(s);
	}
	public String dohvIme(Broj broj) throws GNePostoji {
		if (!brojUIme.containsKey(broj.toString())) {
			throw new GNePostoji();
		}
		return brojUIme.get(broj.toString());
	}
	public Broj dohvBroj(String ime) throws GNePostoji {
		if (!imeUBroj.containsKey(ime)) {
			throw new GNePostoji();
		}
		return imeUBroj.get(ime);
	}
}
