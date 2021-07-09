package sladoledzinica;

import java.awt.BorderLayout;
import java.awt.Button;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.Font;
import java.awt.Frame;
import java.awt.Label;
import java.awt.Panel;
import java.awt.TextField;
import java.awt.Toolkit;
import java.awt.event.ComponentAdapter;
import java.awt.event.ComponentEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

public class Sladoledzinica extends Frame {
	private static final long serialVersionUID = 1L;
	private AparatZaTocenje aparat = new AparatZaTocenje();
	private Panel dodajPanel = new Panel(new FlowLayout(FlowLayout.LEFT, 0, 0));
	private Label labelaNaziv = new Label("Naziv:");
	private TextField poljeNaziv = new TextField(20);
	private Label labelaBoja = new Label("Boja:");
	private TextField poljeBoja = new TextField(20);
	private Button dodajDugme = new Button("Dodaj ukus");
	public Sladoledzinica() {
		setTitle("Sladoledzinica");
		Dimension dimenzijeEkrana = Toolkit.getDefaultToolkit().getScreenSize();
		setBounds((dimenzijeEkrana.width - 500) / 2, (dimenzijeEkrana.height - 500) / 2, 500, 500);
		setResizable(false);
		setLayout(new BorderLayout());
		aparat.populate();
		add(aparat, BorderLayout.CENTER);
		labelaNaziv.setFont(new Font("Arial", Font.BOLD, 20));
		dodajPanel.setBackground(Color.CYAN);
		dodajPanel.add(labelaNaziv);
		dodajPanel.add(poljeNaziv);
		labelaBoja.setFont(new Font("Arial", Font.BOLD, 20));
		dodajPanel.add(labelaBoja);
		dodajPanel.add(poljeBoja);
		dodajDugme.addActionListener((ae) -> {
			try {
				Ukus noviUkus = new Ukus(poljeNaziv.getText(), Color.decode("#" + poljeBoja.getText()));
				aparat.dodajUkus(noviUkus);
			} catch (NumberFormatException e) {
				// Korisnik je loše uneo boju.
				e.printStackTrace();
			} catch (GSadrziUkus e) {
				// Korisnik je dva puta uneo isti ukus.
				e.printStackTrace();
			}
		});
		dodajPanel.add(dodajDugme);
		add(dodajPanel, BorderLayout.SOUTH);
		resized();
		pack();
		addWindowListener(new WindowAdapter() {
			@Override
			public void windowClosing(WindowEvent we) {
				dispose();
			}
		});
		addComponentListener(new ComponentAdapter() {
			@Override
			public void componentResized(ComponentEvent componentEvent) {
				resized();
			}
		});
	}
	public void resized() {
		aparat.resized(getWidth(), getHeight());
	}
}
