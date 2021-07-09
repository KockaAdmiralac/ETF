package telefon;

import java.awt.GridLayout;
import java.awt.Panel;

public class ListaStavki extends Panel {
	private static final long serialVersionUID = 1L;
	public ListaStavki() {
		setLayout(new GridLayout(0, 1));
	}
	public void dodajStavku(Stavka s) {
		add(s);
		revalidate();
		repaint();
	}
}
