package pitanja;

import java.util.ArrayList;
import java.util.List;

public class ZbirkaPitanja {
	private List<Pitanje> pitanja = new ArrayList<>();
	public Pitanje dohvati(int index) throws GNemaPitanja {
		if (pitanja.size() <= index || index < 0) {
			throw new GNemaPitanja();
		}
		return pitanja.get(index);
	}
	public void dodaj(Pitanje p) {
		pitanja.add(p);
	}
	public int dohvBrojPitanja() {
		return pitanja.size();
	}
	public IteratorPitanja iterator() {
		return new IteratorPitanja() {
			@Override
			public boolean postoji() {
				return index < dohvBrojPitanja();
			}
			@Override
			public Pitanje dohvati() throws GNemaPitanja {
				return ZbirkaPitanja.this.dohvati(index);
			}
		};
	}
	@Override
	public String toString() {
		StringBuilder sb = new StringBuilder();
		for (Pitanje p : pitanja) {
			sb.append(p);
			sb.append("\n");
		}
		return sb.toString();
	}
}
