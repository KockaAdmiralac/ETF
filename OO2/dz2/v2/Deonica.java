package karting;

import java.util.ArrayList;
import java.util.List;

public class Deonica implements Cloneable {
	private List<Specificnost> specificnosti = new ArrayList<>();
	private double duzina;
	public Deonica(double duzina) {
		this.duzina = duzina;
	}
	public void dodajSpecificnost(Specificnost s) {
		specificnosti.add(s);
	}
	public void izbaciSpecificnost(int id) {
		for (int i = 0; i < specificnosti.size(); ++i) {
			if (specificnosti.get(i).dohvatiId() == id) {
				specificnosti.remove(i);
				break;
			}
		}
	}
	public Specificnost dohvSpecificnost(int index) {
		return specificnosti.get(index);
	}
	int brojSpecificnosti() {
		return specificnosti.size();
	}
	public double dohvDuzinu() {
		return duzina;
	}
	@Override
	public String toString() {
		StringBuilder sb = new StringBuilder();
		sb.append("deonica(");
		sb.append(duzina);
		sb.append("m)");
		for (Specificnost s : specificnosti) {
			sb.append(s);
		}
		return sb.toString();
	}
	@Override
	public Deonica clone() {
		try {
			Deonica d = (Deonica) super.clone();
			d.specificnosti = new ArrayList<>(d.specificnosti);
			return d;
		} catch (CloneNotSupportedException e) {
			throw new InternalError("Ovo se neće desiti", e);
		}
	}
}
