package rs.ac.bg.etf.oo2.dz1;

public class Skakac extends Figura {

	public Skakac(Polje polje) {
		super(polje);
	}

	@Override
	public boolean mogucePomeranje(Polje polje2) {
		return polje.rastojanje(polje2) == 3 &&
			   !polje.istiRed(polje2) &&
			   !polje.istaKolona(polje2);
	}

	@Override
	public char oznaka() {
		return 'S';
	}

}
