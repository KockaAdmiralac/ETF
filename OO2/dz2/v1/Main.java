package raspored;

public class Main {
	public static void main(String[] args) {
		try {
			Vreme trajanje = new Vreme(0, 30), pomeraj = new Vreme(9, 45);
			Sadrzaj s1 = new Ponavljajuci("Vesti", trajanje, new Vreme(4, 0));
			s1.pomeri(pomeraj);
			System.out.println("Pocetak p1: " + s1.dohvPocetak());
			Ponavljajuci s2 = new Ponavljajuci("Serija", trajanje, new Vreme(6, 0));
			System.out.println("s1: " + s1);
			System.out.println("s2: " + s2);
			System.out.println("Preklop (s1, s2): " + s1.preklapaSe(s2));
			Sema tvSema = new Sema("TV1");
			tvSema.dodaj(s1);
			tvSema.dodaj(s2);
			System.out.print(tvSema);
			System.out.printf("Zauzetost: %.2f%%", tvSema.zauzetost());
		} catch (GVreme | GDodaj e) {
			e.printStackTrace();
		}
	}
}
