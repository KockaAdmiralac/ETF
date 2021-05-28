package raspored;

public class Vreme {
	private int sati;
	private int minuti;
	public Vreme() {
		this.sati = 0;
		this.minuti = 0;
	}
	public Vreme(int sati, int minuti) throws GVreme {
		if (sati < 0 || minuti < 0 || sati > 23 || minuti > 59 || minuti % 15 > 0) {
			throw new GVreme();
		}
		this.sati = sati;
		this.minuti = minuti;
	}
	public int dohvVreme() {
		return sati * 60 + minuti;
	}
	public boolean equals(Vreme vreme2) {
		return sati == vreme2.sati && minuti == vreme2.minuti;
	}
	public Vreme saberi(Vreme vreme2) {
		int ukupnoMinuta = dohvVreme() + vreme2.dohvVreme();
		int prekoracenje = ukupnoMinuta % (24 * 60);
		try {
			return new Vreme(prekoracenje / 60, prekoracenje % 60);
		} catch (GVreme g) {
			throw new InternalError("Ovo se neće desiti; vreme je provereno za prekoračenja pre nego što je " +
					"sabrano.", g);
		}
	}
	@Override
	public String toString() {
		return "(" + sati + ":" + minuti + ")";
	}
}
