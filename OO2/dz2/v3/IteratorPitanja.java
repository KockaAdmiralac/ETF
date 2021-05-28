package pitanja;

public abstract class IteratorPitanja {
	protected int index = 0;
	public abstract boolean postoji();
	public abstract Pitanje dohvati() throws GNemaPitanja;
	public void sledece() {
		index++;
	}
}
