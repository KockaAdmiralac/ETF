package telefon;

public class Kontakt extends Stavka {
	private static final long serialVersionUID = 1L;
	private String ime;
	private Broj broj;
	public Kontakt(String ime, Broj broj) {
		super(ime, broj.toString());
		this.ime = ime;
		this.broj = broj;
	}
	String dohvIme() {
		return ime;
	}
	Broj dohvBroj() {
		return broj;
	}
}
