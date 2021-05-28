package karting;

import java.util.Random;

public class Prepreka extends Specificnost implements Cloneable {
	private double tezina;
	static private Random random = new Random();
	public Prepreka(double tezina) {
		this.tezina = tezina;
	}
	public double dohvTezinu() {
		return tezina;
	}
	@Override
	public void ispoljiEfekat(Object o) throws GNeodgovarajuciObjekat {
		if (!(o instanceof Vozilo)) {
			throw new GNeodgovarajuciObjekat();
		}
		Vozilo v = (Vozilo) o;
		if (v.dohvUpravljivost() >= tezina) {
			return;
		}
		double razlika = tezina - v.dohvUpravljivost();
		if (random.nextDouble() < razlika) {
			v.postTrenBrzinu(0);
		}
	}
	@Override
	public void ponistiEfekat(Object o) throws GNeodgovarajuciObjekat {}
	@Override
	public Prepreka clone() {
		try {
			return (Prepreka) super.clone();
		} catch (CloneNotSupportedException e) {
			throw new InternalError("Ovo se neće desiti", e);
		}
	}
	@Override
	public String toString() {
		return "P" + tezina;
	}
}
