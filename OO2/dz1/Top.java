package rs.ac.bg.etf.oo2.dz1;

public class Top extends Figura {

	public Top(Polje polje) {
		super(polje);
	}

	@Override
	public boolean mogucePomeranje(Polje polje2) {
		return polje.istaKolona(polje2) ||
			   polje.istiRed(polje2);
	}

	@Override
	public char oznaka() {
		return 'T';
	}

}
