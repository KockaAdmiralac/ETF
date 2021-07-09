package telefon;

import java.awt.Button;
import java.awt.CardLayout;
import java.awt.GridLayout;
import java.awt.Label;
import java.awt.Panel;

public class Tastatura extends Panel implements Runnable {
	private static final long serialVersionUID = 1L;
	private Label natpis;
	private CardLayout layout = new CardLayout();
	private static final String[] BROJEVI = {
		"1", "2", "3",
		"4", "5", "6",
		"7", "8", "9",
		"*", "0", "+"
	};
	private static final String[] SLOVA = {
		" ",    "ABC",  "DEF",
		"GHI",  "JKL",  "MNO",
		"PQRS", "TUV",  "WXYZ",
		" ",    "_",    " "
	};
	public static final String REZIM_BROJEVI = "BROJEVI";
	public static final String REZIM_SLOVA = "SLOVA";
	private String prosloDugme = "";
	private int index;
	private Thread nit;
	public Tastatura(Label natpis) {
		this.natpis = natpis;
		setLayout(layout);
		Panel brojevi = new Panel(new GridLayout(4, 3));
		for (String broj : BROJEVI) {
			Button dugme = new Button(broj);
			dugme.addActionListener((ae) -> kliknuto(broj));
			brojevi.add(dugme);
		}
		add(brojevi, REZIM_BROJEVI);
		Panel slova = new Panel(new GridLayout(4, 3));
		for (String slovo : SLOVA) {
			Button dugme = new Button(slovo);
			dugme.addActionListener((ae) -> kliknuto(slovo));
			slova.add(dugme);
		}
		add(slova, REZIM_SLOVA);
	}
	private void kliknuto(String dugme) {
		if (dugme.length() == 0) {
			return;
		}
		String trenNatpis = natpis.getText();
		if (dugme.equals(prosloDugme) && dugme.length() > 1 && !prosloViseOd1s()) {
			index = (index + 1) % dugme.length();
			natpis.setText(trenNatpis.substring(0, trenNatpis.length() - 1) + dugme.charAt(index));
		} else {
			index = 0;
			natpis.setText(trenNatpis + dugme.charAt(index));
		}
		natpis.revalidate();
		prosloDugme = dugme;
		if (dugme.length() > 1) {
			zaustaviNit();
			nit = new Thread(this);
			nit.start();
		}
	}
	synchronized void zaustaviNit() {
		if (nit == null) {
			return;
		}
		nit.interrupt();
		try {
			wait();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}
	private synchronized boolean prosloViseOd1s() {
		if (nit != null) {
			zaustaviNit();
			return false;
		}
		return true;
	}
	public void postNatpis(Label natpis) {
		this.natpis = natpis;
	}
	@Override
	public void run() {
		try {
			Thread.sleep(1000);
		} catch (InterruptedException e) {
			// Prekinuti smo, znači prošlo je manje od sekund.
		}
		synchronized (this) {
			nit = null;
			notify();
		}
	}
	public void promeniRezim(String rezim) {
		layout.show(this, rezim);
	}
}
