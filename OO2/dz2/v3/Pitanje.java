package pitanja;

public class Pitanje implements Cloneable {
	private static int jedinstveniId = 1;
	private int id = jedinstveniId++;
	private String tekst;
	private int brojPoena;
	private double tezina;
	public Pitanje(String tekst, int brojPoena, double tezina) {
		this.tekst = tekst;
		this.brojPoena = brojPoena;
		this.tezina = tezina;
	}
	public String dohvTekst() {
		return tekst;
	}
	public int dohvBrojPoena() {
		return brojPoena;
	}
	public double dohvTezinu() {
		return tezina;
	}
	@Override
	public Pitanje clone() {
		try {
			return (Pitanje) super.clone();
		} catch (CloneNotSupportedException e) {
			throw new InternalError("Ovo se neće desiti", e);
		}
	}
	@Override
	public String toString() {
		return "Pitanje " + id + ": " + tekst;
	}
}
