package raspored;

import java.util.ArrayList;
import java.util.List;

public class Ponavljajuci extends Sadrzaj {
	private Vreme perioda;
	public Ponavljajuci(String naziv, Vreme trajanje, Vreme perioda) {
		super(naziv, trajanje);
		this.perioda = perioda;
	}
	public Vreme dohvPeriodu() {
		return perioda;
	}
	@Override
	protected List<Interval> vremena() {
		List<Interval> vremena = new ArrayList<>();
		Vreme pocinje = pocetak;
		Vreme zavrsava = pocinje.saberi(trajanje);
		while (true) {
			vremena.add(new Interval(pocinje, zavrsava));
			if (zavrsava.saberi(perioda).dohvVreme() < zavrsava.dohvVreme()) {
				break;
			}
			pocinje = pocinje.saberi(perioda);
			zavrsava = zavrsava.saberi(perioda);
		}
		return vremena;
	}
	@Override
	public char oznaka() {
		return 'P';
	}
	@Override
	public String toString() {
		return super.toString() + " T" + perioda;
	}
}
