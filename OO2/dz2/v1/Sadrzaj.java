package raspored;

import java.util.List;

abstract public class Sadrzaj {
	private String naziv;
	protected Vreme trajanje;
	protected Vreme pocetak = new Vreme();
	protected static class Interval {
		public Vreme pocetak;
		public Vreme kraj;
		public Interval(Vreme pocetak, Vreme kraj) {
			this.pocetak = pocetak;
			this.kraj = kraj;
		}
		public boolean preklapaSe(Interval interval2) {
			return
				pocetak.dohvVreme() < interval2.pocetak.dohvVreme() &&
				kraj.dohvVreme() > interval2.pocetak.dohvVreme();
		}
	}
	public Sadrzaj(String naziv, Vreme trajanje) {
		this.naziv = naziv;
		this.trajanje = trajanje;
	}
	public Vreme preklapaSe(Sadrzaj sadrzaj2) {
		List<Interval> vremena1 = vremena();
		List<Interval> vremena2 = sadrzaj2.vremena();
		for (Interval i1 : vremena1) {
			for (Interval i2 : vremena2) {
				if (i1.preklapaSe(i2)) {
					return i2.pocetak;
				}
				if (i2.preklapaSe(i1)) {
					return i1.pocetak;
				}
			}
		}
		return null;
	}
	abstract protected List<Interval> vremena();
	public void pomeri(Vreme pomeraj) {
		pocetak = pocetak.saberi(pomeraj);
	}
	public String dohvNaziv() {
		return naziv;
	}
	public Vreme dohvTrajanje() {
		return trajanje;
	}
	public Vreme dohvPocetak() {
		return pocetak;
	}
	public void postPocetak(Vreme pocetak) {
		this.pocetak = pocetak;
	}
	abstract public char oznaka();
	@Override
	public String toString() {
		return oznaka() + ", " + naziv + " | " + pocetak + " - " + pocetak.saberi(trajanje);
	}
}
