package karting;

abstract public class Specificnost {
	private static int jedinstveniId = 0;
	private int id = jedinstveniId++;
	abstract public void ispoljiEfekat(Object o) throws GNeodgovarajuciObjekat;
	abstract public void ponistiEfekat(Object o) throws GNeodgovarajuciObjekat;
	public int dohvatiId() {
		return id;
	}
}
