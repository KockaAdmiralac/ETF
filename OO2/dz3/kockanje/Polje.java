package kockanje;

import java.awt.Canvas;
import java.awt.Color;
import java.awt.Font;
import java.awt.FontMetrics;
import java.awt.Graphics;
import java.awt.Toolkit;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

public class Polje extends Canvas {
	public static final int SLOBODNO = 0;
	public static final int IZABRANO = 1;
	private static final long serialVersionUID = 1L;
	private int broj;
	private int status = SLOBODNO;
	public Polje(Mreza mreza, int broj) {
		this.broj = broj;
		addMouseListener(new MouseAdapter() {
			@Override
			public void mousePressed(MouseEvent e) {
				status = Math.abs(1 - status);
				mreza.pritisnut(Polje.this);
				repaint();
			}
		});
	}
	public int dohvBroj() {
		return broj;
	}
	public int dohvStatus() {
		return status;
	}
	public void postStatus(int status) {
		this.status = status;
	}
	public void paint(Graphics g) {
		super.paint(g);
		int width = getWidth();
		int height = getHeight();
		g.setColor(Color.ORANGE);
		g.fillRect(0, 0, width, height);
		if (status == IZABRANO) {
			g.setColor(Color.BLUE);
			g.fillOval(0, 0, width, height);
			g.setColor(Color.WHITE);
		} else {
			g.setColor(Color.BLACK);
		}
		int refDimenzija = (width < height) ? width : height;
		// /2 na kraju je zbog toga da bi dvocifreni brojevi zauzimali tačno trećinu dimenzije,
		// kao što je to prikazano na slici u postavci.
		double fontSize = refDimenzija / 72.0 * Toolkit.getDefaultToolkit().getScreenResolution() / 3 / 2;
		g.setFont(new Font("Comic Sans MS", Font.BOLD, (int)Math.floor(fontSize)));
		String brojStr = String.valueOf(broj);
		FontMetrics fm = g.getFontMetrics();
		g.drawString(brojStr, (width - fm.stringWidth(brojStr)) / 2, (height - fm.getHeight()) / 2 + fm.getAscent());
	}
}
