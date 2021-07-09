package sladoledzinica;

import java.awt.BorderLayout;
import java.awt.Button;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.Label;
import java.awt.Panel;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.ArrayList;
import java.util.List;

public class AparatZaTocenje extends Panel {
	private static final long serialVersionUID = 1L;
	private MestoZaTocenje mesto = new MestoZaTocenje(this);
	private Panel dostupniUkusi = new Panel(new GridLayout(3, 0));
	private Panel sladoledPanel = new Panel(new BorderLayout());
	private Panel tocenje = new Panel(new GridLayout(2, 1, 0, 0));
	private Button prodajDugme = new Button("Prodaj");
	private Label sladoledLabela = new Label("");
	private List<Ukus> ukusi = new ArrayList<>();
	private Label sladoledTekst = new Label("Sladoled:");
	public void populate() {
		setLayout(new BorderLayout());

		add(dostupniUkusi, BorderLayout.CENTER);

		prodajDugme.addActionListener((ae) -> {
			mesto.zavrsiTocenje();
			sladoledLabela.setText("");
			prodajDugme.setEnabled(false);
		});
		prodajDugme.setEnabled(false);
		tocenje.add(prodajDugme);
		tocenje.add(mesto);
		add(tocenje, BorderLayout.EAST);

		sladoledTekst.setFont(new Font("Arial", Font.BOLD, 20));
		sladoledPanel.add(sladoledTekst, BorderLayout.WEST);
		sladoledPanel.setBackground(Color.LIGHT_GRAY);
		sladoledPanel.add(sladoledLabela, BorderLayout.CENTER);
		sladoledLabela.revalidate();
		add(sladoledPanel, BorderLayout.SOUTH);
	}
	void azuriraj(Sladoled sladoled) {
		sladoledLabela.setText(sladoled.toString());
		sladoledLabela.revalidate();
	}
	public void dodajUkus(Ukus ukus) throws GSadrziUkus {
		for (Ukus u : ukusi) {
			if (u.equals(ukus)) {
				throw new GSadrziUkus();
			}
		}
		ukusi.add(ukus);
		Button dugmeUkus = new Button(ukus.dohvNaziv());
		dugmeUkus.setBackground(ukus.dohvBoju());
		dugmeUkus.addMouseListener(new MouseAdapter() {
			@Override
			public void mousePressed(MouseEvent e) {
				mesto.postUkus(ukus);
				mesto.toci();
			}
			@Override
			public void mouseReleased(MouseEvent e) {
				mesto.zaustaviTocenje();
			}
		});
		dostupniUkusi.add(dugmeUkus);
		dostupniUkusi.revalidate();
		dostupniUkusi.repaint();
	}
	public void omoguciKupovinu() {
		prodajDugme.setEnabled(true);
	}
	void resized(int width, int height) {
		dostupniUkusi.setPreferredSize(new Dimension(width / 2, height / 2));
		tocenje.setPreferredSize(new Dimension(width / 2, height / 10 * 8));
	}
}
