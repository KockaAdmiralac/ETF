package kockanje;

import java.awt.Color;
import java.awt.GridLayout;
import java.awt.Panel;
import java.util.ArrayList;
import java.util.HashSet;

public class Mreza extends Panel {
	private static final long serialVersionUID = 1L;
	private ArrayList<Polje> izabranaPolja = new ArrayList<>();
	private HashSet<Integer> izabrani = new HashSet<>();
	private Igra igra;
	private int visina;
	private int sirina;
	public Mreza(Igra igra, int visina, int sirina) {
		this.visina = visina;
		this.sirina = sirina;
		this.igra = igra;
	}
	int brojPolja() {
		return visina * sirina;
	}
	void populate() {
		setLayout(new GridLayout(visina, sirina, 3, 3));
		setBackground(Color.BLACK);
		for (int i = 0; i < brojPolja(); ++i) {
			add(new Polje(this, i));
		}
	}
	public Mreza(Igra igra) {
		this(igra, 4, 5);
	}
	void pritisnut(Polje polje) {
		if (polje.dohvStatus() == Polje.IZABRANO) {
			izabrani.add(polje.dohvBroj());
			izabranaPolja.add(polje);
		} else {
			izabrani.remove(polje.dohvBroj());
			izabranaPolja.remove(polje);
		}
		igra.azurirajStanje();
	}
	public ArrayList<Polje> dohvIzabranaPolja() {
		return izabranaPolja;
	}
	public HashSet<Integer> dohvIzabrane() {
		return izabrani;
	}
}
