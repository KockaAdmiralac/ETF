package rs.ac.bg.etf.oo2.dz1;

public abstract class Figura {

	protected Polje polje;

	public Figura(Polje polje) {
		this.polje = polje;
	}
	
	public abstract boolean mogucePomeranje(Polje polje2);
	public abstract char oznaka();
	
	@Override
	public String toString() {
		return String.valueOf(oznaka()) + polje;
	}

}
