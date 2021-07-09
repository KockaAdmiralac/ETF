package telefon;

import java.awt.BorderLayout;
import java.awt.Button;
import java.awt.Color;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.Label;
import java.awt.Panel;

public class Telefon extends Panel {
	private static final long serialVersionUID = 1L;
	private Broj broj;
	private Imenik imenik = new Imenik();
	private Label natpisBroj = new Label("");
	private Label natpisIme = new Label("");
	private Tastatura tastatura = new Tastatura(natpisBroj);
	private boolean ukljucen = true;
	private boolean fazaImena = false;
	public Telefon(Broj broj, Color boja) {
		this.broj = broj;
		setBackground(boja);
		setLayout(new BorderLayout());
		Panel gornjiPanel = new Panel(new BorderLayout());
		Panel prikazPanel = new Panel(new BorderLayout());
		prikazPanel.add(natpisBroj, BorderLayout.NORTH);
		prikazPanel.add(natpisIme, BorderLayout.SOUTH);
		gornjiPanel.add(prikazPanel, BorderLayout.NORTH);
		gornjiPanel.add(tastatura, BorderLayout.CENTER);
		add(gornjiPanel, BorderLayout.NORTH);
		Panel donjiPanel = new Panel(new BorderLayout());
		donjiPanel.add(imenik, BorderLayout.NORTH);
		Panel dugmici = new Panel(new GridLayout(1, 2));
		Button dodajKontakt = new Button("Dodaj kontakt");
		Button iskljuciTelefon = new Button("Isključi telefon");
		iskljuciTelefon.setBackground(Color.GRAY);
		dugmici.add(dodajKontakt);
		dugmici.add(iskljuciTelefon);
		donjiPanel.add(dugmici, BorderLayout.CENTER);
		Label brojLabela = new Label(broj.toString());
		brojLabela.setFont(new Font("Arial", Font.BOLD, 20));
		donjiPanel.add(brojLabela, BorderLayout.SOUTH);
		add(donjiPanel, BorderLayout.SOUTH);
		dodajKontakt.addActionListener((ae) -> {
			if (fazaImena) {
				imenik.dodajStavku(new Kontakt(natpisIme.getText(), new Broj(natpisBroj.getText())));
				natpisIme.setText("");
				natpisBroj.setText("");
				tastatura.promeniRezim(Tastatura.REZIM_BROJEVI);
				tastatura.postNatpis(natpisBroj);
			} else {
				tastatura.promeniRezim(Tastatura.REZIM_SLOVA);
				tastatura.postNatpis(natpisIme);
			}
			fazaImena = !fazaImena;
		});
		iskljuciTelefon.addActionListener((ae) -> {
			ukljucen = !ukljucen;
			if (ukljucen) {
				iskljuciTelefon.setLabel("Isključi telefon");
				iskljuciTelefon.setBackground(Color.GRAY);
			} else {
				iskljuciTelefon.setLabel("Uključi telefon");
				iskljuciTelefon.setBackground(Color.RED);
			}
			iskljuciTelefon.revalidate();
		});
	}
	public Broj dohvBroj() {
		return broj;
	}
	void iskljuci() {
		tastatura.zaustaviNit();
	}
}
