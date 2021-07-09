package sladoledzinica;

import java.awt.Color;

public class Ukus {
	private String naziv;
	private Color boja;
	public Ukus(String naziv, Color boja) {
		this.naziv = naziv;
		this.boja = boja;
	}
	public boolean equals(Ukus ukus2) {
		return naziv.equals(ukus2.naziv);
	}
	public String dohvNaziv() {
		return naziv;
	}
	public Color dohvBoju() {
		return boja;
	}
	@Override
	public String toString() {
		return "[" + naziv + "]";
	}
}
