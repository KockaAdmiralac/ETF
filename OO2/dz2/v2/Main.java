package karting;

public class Main {
	public static void main(String[] args) {
		Vozilo v1 = new Vozilo(30.0, 3.0, 0.75, "Crash Bandicoot");
		Vozilo v2 = new Vozilo(40.0, 4.0, 0.5, "Coco Bandicoot");
		v2.postMaksBrzinu(40.0);
		v2.postUbrzanje(4.0);
		v2.postUpravljivost(0.5);
		v2.postTrenBrzinu(0.0);
		Vozilo v3 = new Vozilo(45, 2.5, 0.25, "Tiny Tiger");
		Specificnost s1 = new Krivina(40.0);
		Specificnost s2 = new Prepreka(0.6);
		Deonica prva = new Deonica(50.0);
		Deonica d = new Deonica(100.0);
		d.dodajSpecificnost(s1);
		d.dodajSpecificnost(((Krivina)s1).clone());
		d.dodajSpecificnost(s2);
		Deonica d2 = d.clone();
		Staza s = new Staza("Hmm");
		try {
			s.dodajDeonicu(prva);
			s.dodajDeonicu(d);
			s.dodajDeonicu(d2);
		} catch (GPrvaDeonica g) {
			g.printStackTrace();
		}
		Trka t = new Trka(s);
		t.dodajVozilo(v1);
		t.dodajVozilo(v2);
		t.dodajVozilo(v3);
		t.simuliraj(14);
		System.out.println(t);
		t.simuliraj(1);
		System.out.println(t);
		t.simuliraj(20);
		System.out.println(t);
	}
}