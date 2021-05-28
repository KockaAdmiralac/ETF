package karting;

public class Vozilo {
	private double maksBrzina;
	private double ubrzanje;
	private double upravljivost;
	private String takmicar;
	private double trenBrzina = 0;
	public Vozilo(double maksBrzina, double ubrzanje, double upravljivost, String takmicar) {
		this.maksBrzina = maksBrzina;
		this.ubrzanje = ubrzanje;
		this.upravljivost = upravljivost;
		this.takmicar = takmicar;
	}
	public double dohvMaksBrzinu() {
		return maksBrzina;
	}
	public double dohvTrenBrzinu() {
		return trenBrzina;
	}
	public double dohvUbrzanje() {
		return ubrzanje;
	}
	public double dohvUpravljivost() {
		return upravljivost;
	}
	public String dohvIme() {
		return takmicar;
	}
	public void postMaksBrzinu(double maksBrzina) {
		this.maksBrzina = maksBrzina;
		if (trenBrzina > maksBrzina) {
			trenBrzina = maksBrzina;
		}
	}
	public void postTrenBrzinu(double trenBrzina) {
		if (trenBrzina > maksBrzina) {
			this.trenBrzina = maksBrzina;
		} else {
			this.trenBrzina = trenBrzina;
		}
	}
	public void postUbrzanje(double ubrzanje) {
		this.ubrzanje = ubrzanje;
	}
	public void postUpravljivost(double upravljivost) {
		this.upravljivost = upravljivost;
	}
	public void postIme(String takmicar) {
		this.takmicar = takmicar;
	}
	public double pomeriVozilo(double vreme) {
		double put = 0;
		if (trenBrzina + ubrzanje * vreme > maksBrzina) {
			double delimVreme = (maksBrzina - trenBrzina) / ubrzanje;
			put = trenBrzina * delimVreme + (ubrzanje * delimVreme * delimVreme) / 2 + maksBrzina * (vreme - delimVreme);
			trenBrzina = maksBrzina;
		} else {
			put = trenBrzina * vreme + (ubrzanje * vreme * vreme) / 2;
			trenBrzina += ubrzanje * vreme;
		}
		return put;
	}
	public double izracunajVreme(double put) {
		double ubrzanoVreme = (Math.sqrt(trenBrzina * trenBrzina + 2 * ubrzanje * put) - trenBrzina) / ubrzanje;
		double maksUbrzanoVreme = (maksBrzina - trenBrzina) / ubrzanje;
		if (maksUbrzanoVreme >= ubrzanoVreme) {
			return ubrzanoVreme;
		}
		double preostaliPut = put - trenBrzina * maksUbrzanoVreme - (ubrzanje * maksUbrzanoVreme * maksUbrzanoVreme) / 2;
		return maksUbrzanoVreme + preostaliPut / maksBrzina;
	}
	@Override
	public String toString() {
		return takmicar + " [" + maksBrzina + ", " + ubrzanje + ", " + upravljivost + "]";
	}
}
