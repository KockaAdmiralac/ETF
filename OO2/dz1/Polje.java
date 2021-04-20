package rs.ac.bg.etf.oo2.dz1;

public class Polje {

	private char kolona;
	private int red;

	public Polje(char kolona, int red) {
		this.kolona = kolona;
		this.red = red;
	}
	
	public boolean istiRed(Polje polje2) {
		return red == polje2.red;
	}
	
	public boolean istaKolona(Polje polje2) {
		return kolona == polje2.kolona;
	}
	
	public int rastojanje(Polje polje2) {
		return Math.abs(kolona - polje2.kolona) + Math.abs(red - polje2.red);
	}
	
	@Override
	public String toString() {
		return String.valueOf(kolona) + red;
	}

}
