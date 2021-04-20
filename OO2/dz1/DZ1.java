package rs.ac.bg.etf.oo2.dz1;

public class DZ1 {

	private static void testCase(String message, boolean condition) {
		System.out.print(message);
		System.out.print("... ");
		if (condition) {
			System.out.println("PASS");
		} else {
			System.out.println("FAIL");
		}
	}

	public static void main(String[] args) {
		System.out.println("================================================================================");
		Polje p1 = new Polje('A', 1);
		Polje p2 = new Polje('B', 2);
		Polje p3 = new Polje('A', 2);
		Polje p4 = new Polje('B', 1);
		testCase("Representacija prvog polja je A1", p1.toString().equals("A1"));
		testCase("Reprezentacija drugog polja je B2", p2.toString().equals("B2"));
		testCase("Rastojanje između p1 i p2 je 2", p1.rastojanje(p2) == 2);
		testCase("Rastojanje između p1 i p3 je 1", p1.rastojanje(p3) == 1);
		testCase("p1 i p2 nisu u istoj koloni ni redu", !p1.istiRed(p2) && !p1.istaKolona(p2));
		testCase("p1 i p3 su u istoj koloni i različitim redovima", !p1.istiRed(p3) && p1.istaKolona(p3));
		testCase("p1 i p4 nisu u istoj koloni i jesu u istom redu", p1.istiRed(p4) && !p1.istaKolona(p4));
		System.out.println("================================================================================");
		Top t = new Top(p1);
		testCase("Reprezentacija topa je TA1", t.toString().equals("TA1"));
		testCase("Oznaka topa je T", t.oznaka() == 'T');
		testCase("Topa je moguće pomeriti vertikalno", t.mogucePomeranje(p3));
		testCase("Topa je moguće pomeriti horizontalno", t.mogucePomeranje(p4));
		testCase("Topa nije moguće pomerati dijagonalno", !t.mogucePomeranje(p2));
		System.out.println("================================================================================");
		Skakac s = new Skakac(p2);
		testCase("Reprezentacija skakača je SB2", s.toString().equals("SB2"));
		testCase("Oznaka skakača je S", s.oznaka() == 'S');
		testCase("Skakača je moguče pomeriti u G na jednu stranu", s.mogucePomeranje(new Polje('D', 3)));
		testCase("Skakača je moguće pomeriti u G na drugu stranu", s.mogucePomeranje(new Polje('A', 4)));
		testCase("Skakača nije moguće pomeriti na polje manje od 3 udaljeno", !s.mogucePomeranje(p1));
		testCase("Skakača nije moguće pomeriti u jednom smeru", !s.mogucePomeranje(new Polje('B', 5)));
		System.out.println("================================================================================");
	}

}
