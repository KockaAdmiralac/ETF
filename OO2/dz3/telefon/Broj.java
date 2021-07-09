package telefon;

public class Broj {
	private String drzava;
	private String pozivniBroj;
	private String pretplatnik;
	public Broj(String drzava, String pozivniBroj, String pretplatnik) {
		this.drzava = drzava;
		this.pozivniBroj = pozivniBroj;
		this.pretplatnik = pretplatnik;
	}
	public Broj(String tekst) {
		if (tekst.length() < 6) {
			// Nije rečeno da bacamo grešku.
			return;
		}
		drzava = tekst.substring(1, 4);
		pozivniBroj = tekst.substring(4, 6);
		pretplatnik = tekst.substring(6);
	}
	public boolean istaDrzava(Broj broj2) {
		return broj2.drzava.equals(drzava);
	}
	public boolean istaMreza(Broj broj2) {
		return istaDrzava(broj2) && broj2.pozivniBroj.equals(pozivniBroj);
	}
	public boolean equals(Broj broj2) {
		return istaMreza(broj2) && broj2.pretplatnik.equals(pretplatnik);
	}
	@Override
	public String toString() {
		// Ovo je moglo i preko StringBuilder, ali pošto je broj konkatenacija
		// konstantan, nema potrebe.
		return "+" + drzava + " " + pozivniBroj + " " + pretplatnik;
	}
}
