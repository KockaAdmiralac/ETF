package pitanja;

public class PitanjeSaPonudjenimOdgovorima extends Pitanje {
	private String[] odgovori;
	public PitanjeSaPonudjenimOdgovorima(String tekst, int brojPoena, double tezina, String[] odgovori) {
		super(tekst, brojPoena, tezina);
		this.odgovori = odgovori;
	}
	@Override
	public String toString() {
		StringBuilder sb = new StringBuilder();
		sb.append(super.toString());
		for (int i = 0; i < odgovori.length; ++i) {
			sb.append("\n");
			sb.append("    ");
			sb.append(i + 1);
			sb.append(". ");
			sb.append(odgovori[i]);
		}
		return sb.toString();
	}
}
