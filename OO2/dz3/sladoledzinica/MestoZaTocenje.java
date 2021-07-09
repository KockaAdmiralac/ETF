package sladoledzinica;

import java.awt.Canvas;
import java.awt.Graphics;
import java.util.ArrayList;
import java.util.List;

public class MestoZaTocenje extends Canvas implements Runnable {
	private static final long serialVersionUID = 1L;
	private AparatZaTocenje aparat;
	private final static int VELICINA_CASE = 200;
	private final static int BROJ_SIPANJA = (int) Math.ceil(1.0 * VELICINA_CASE / 20);
	private List<Ukus> ukusi = new ArrayList<>();
	private Sladoled sladoled = null;
	private Thread timer = null;
	private Ukus trenutniUkus = null;
	public MestoZaTocenje(AparatZaTocenje aparat) {
		this.aparat = aparat;
	}
	public void postUkus(Ukus ukus) {
		trenutniUkus = ukus;
	}
	public void toci() {
		if (trenutniUkus == null) {
			return;
		}
		if (sladoled == null) {
			sladoled = new Sladoled(VELICINA_CASE);
		}
		zaustaviTocenje();
		timer = new Thread(this);
		timer.start();
	}
	public synchronized void zaustaviTocenje() {
		if (timer != null) {
			timer.interrupt();
		}
		while (timer != null) {
			try {
				wait();
			} catch (InterruptedException e) {
				// Ovo se neće desiti.
			}
		}
	}
	public void run() {
		try {
			while (!sladoled.pun()) {
				Thread.sleep(500);
				if (Thread.interrupted()) {
					// Za ovim najverovatnije nema zapravo potrebe.
					break;
				}
				sladoled.dodajUkus(trenutniUkus, 20);
				ukusi.add(trenutniUkus);
				aparat.azuriraj(sladoled);
				repaint();
			}
		} catch (InterruptedException e) {
			// Izlazimo iz petlje.
		}
		if (sladoled.pun()) {
			aparat.omoguciKupovinu();
		}
		synchronized (this) {
			timer = null;
			notify();
		}
	}
	public boolean tocenjeUToku() {
		return sladoled != null;
	}
	public void zavrsiTocenje() {
		zaustaviTocenje();
		System.out.println(sladoled);
		sladoled = null;
		ukusi.clear();
		repaint();
	}
	@Override
	public void paint(Graphics g) {
		int visina = getHeight();
		int sirina = getWidth();
		double odbirak = 1.0 * visina / BROJ_SIPANJA;
		int trenutnaKolicina = 0;
		for (Ukus ukus : ukusi) {
			++trenutnaKolicina;
			g.setColor(ukus.dohvBoju());
			g.fillRect(0, (int)(visina - trenutnaKolicina * odbirak), sirina, (int)odbirak);
		}
	}
}
