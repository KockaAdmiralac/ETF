package telefon;

import java.awt.BorderLayout;
import java.awt.Font;
import java.awt.Label;
import java.awt.Panel;

public class Stavka extends Panel {
	private static final long serialVersionUID = 1L;
	private Label naslovLabela;
	public Stavka(String naslov, String tekst) {
		setLayout(new BorderLayout());
		naslovLabela = new Label(naslov);
		naslovLabela.setFont(new Font("Arial", Font.BOLD, 24));
		add(naslovLabela, BorderLayout.NORTH);
		Label tekstLabela = new Label(tekst);
		add(tekstLabela, BorderLayout.SOUTH);
	}
	public void postNaslov(String naslov) {
		naslovLabela.setText(naslov);
		naslovLabela.revalidate();
		naslovLabela.repaint();
	}
}
