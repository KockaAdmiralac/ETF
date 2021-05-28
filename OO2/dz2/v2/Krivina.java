package karting;

import java.util.HashMap;
import java.util.Map;

public class Krivina extends Specificnost implements Cloneable {
	private double maksBrzina;
	private Map<Vozilo, Double> stareBrzine = new HashMap<>();
	public Krivina(double maksBrzina) {
		this.maksBrzina = maksBrzina;
	}
	@Override
	public void ispoljiEfekat(Object o) throws GNeodgovarajuciObjekat {
		if (!(o instanceof Vozilo)) {
			throw new GNeodgovarajuciObjekat();
		}
		Vozilo v = (Vozilo) o;
		if (stareBrzine.get(v) != null) {
			// Već smo imali efekta na ovo vozilo.
			return;
		}
		stareBrzine.put(v, v.dohvMaksBrzinu());
		double novaBrzina = maksBrzina * v.dohvUpravljivost();
		if (novaBrzina < v.dohvMaksBrzinu()) {
			v.postMaksBrzinu(novaBrzina);
		}
	}
	@Override
	public void ponistiEfekat(Object o) throws GNeodgovarajuciObjekat {
		if (!(o instanceof Vozilo)) {
			throw new GNeodgovarajuciObjekat();
		}
		Vozilo v = (Vozilo) o;
		Double staraBrzina = stareBrzine.get(v);
		if (staraBrzina == null) {
			throw new GNeodgovarajuciObjekat();
		}
		if (staraBrzina > v.dohvMaksBrzinu()) {
			v.postMaksBrzinu(staraBrzina);
		}
		stareBrzine.remove(v);
	}
	public double dohvMaksBrzinu() {
		return maksBrzina;
	}
	@Override
	public Krivina clone() {
		try {
			Krivina k = (Krivina) super.clone();
			k.stareBrzine = new HashMap<>();
			for (Map.Entry<Vozilo, Double> entry : stareBrzine.entrySet()) {
				k.stareBrzine.put(entry.getKey(), entry.getValue());
			}
			return k;
		} catch (CloneNotSupportedException e) {
			throw new InternalError("Ovo se neće desiti", e);
		}
	}
	@Override
	public String toString() {
		return "K" + maksBrzina;
	}
}
