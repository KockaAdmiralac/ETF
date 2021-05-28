package raspored;

import java.util.ArrayList;
import java.util.List;

import raspored.Sadrzaj.Interval;

public class Sema {
	private String naziv;
	private Vreme pocetak;
	private Vreme kraj;
	private List<Sadrzaj> sadrzaji = new ArrayList<>();
	public Sema(String naziv) {
		try {
			pocetak = new Vreme(8, 0);
		} catch (GVreme g) {
			throw new IllegalStateException("Ovo se neće desiti; 08:00 je validno vreme.", g);
		}
		try {
			kraj = new Vreme(22, 0);
		} catch (GVreme g) {
			throw new IllegalStateException("Ovo se neće desiti; 22:00 je validno vreme.", g);
		}
		this.naziv = naziv;
	}
	public Sema(String naziv, Vreme pocetak) {
		try {
			kraj = new Vreme(22, 0);
		} catch (GVreme g) {
			throw new IllegalStateException("Ovo se neće desiti; 22:00 je validno vreme.", g);
		}
		this.naziv = naziv;
		this.pocetak = pocetak;
	}
	public Sema(String naziv, Vreme pocetak, Vreme kraj) {
		this.naziv = naziv;
		this.pocetak = pocetak;
		this.kraj = kraj;
	}
	public int brojSadrzaja() {
		return sadrzaji.size();
	}
	public Sadrzaj dohvati(int index) throws GIndeks {
		if (index < 0 || index >= sadrzaji.size()) {
			throw new GIndeks();
		}
		return sadrzaji.get(index);
	}
	public void dodaj(Sadrzaj s) throws GDodaj {
		Vreme min;
		try {
			min = new Vreme(0, 15);
		} catch (GVreme g) {
			throw new InternalError("Ovo se neće desiti; 00:15 je validno vreme.", g);
		}
		if (s.dohvPocetak().dohvVreme() < pocetak.dohvVreme()) {
			s.postPocetak(pocetak);
		}
		boolean moze;
		while (s.dohvPocetak().saberi(s.dohvTrajanje()).dohvVreme() < kraj.dohvVreme()) {
			moze = true;
			for (Sadrzaj tren : sadrzaji) {
				if (tren.preklapaSe(s) != null) {
					moze = false;
					break;
				}
			}
			if (moze) {
				int i = 0;
				for (; i < sadrzaji.size(); ++i) {
					if (sadrzaji.get(i).dohvPocetak().dohvVreme() > s.dohvPocetak().dohvVreme()) {
						sadrzaji.add(i, s);
						break;
					}
				}
				if (i == sadrzaji.size()) {
					sadrzaji.add(s);
				}
				return;
			} else {
				s.postPocetak(s.dohvPocetak().saberi(min));
			}
		}
		throw new GDodaj();
	}
	public double zauzetost() {
		double ukupno = kraj.dohvVreme() - pocetak.dohvVreme();
		if (ukupno == 0) {
			return 0;
		}
		double zauzeto = 0;
		for (Sadrzaj s : sadrzaji) {
			for (Interval i : s.vremena()) {
				if (i.pocetak.dohvVreme() >= pocetak.dohvVreme() && i.kraj.dohvVreme() <= kraj.dohvVreme()) {
					zauzeto += i.kraj.dohvVreme() - i.pocetak.dohvVreme();
				}
			}
		}
		return zauzeto / ukupno * 100;
	}
	public String toString() {
		StringBuilder sb = new StringBuilder();
		sb.append(naziv);
		sb.append(" : ");
		sb.append(pocetak);
		sb.append(" - ");
		sb.append(kraj);
		sb.append("\n");
		for (Sadrzaj s : sadrzaji) {
			sb.append(s);
			sb.append("\n");
		}
		return sb.toString();
	}
}
