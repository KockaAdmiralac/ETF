package telefon;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Frame;
import java.awt.GridLayout;
import java.awt.Toolkit;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

public class Main {
	public static void main(String[] args) {
		Frame frame = new Frame();
		frame.setTitle("Telefoni");
		Dimension dimenzijeEkrana = Toolkit.getDefaultToolkit().getScreenSize();
		frame.setBounds((dimenzijeEkrana.width - 500) / 2, (dimenzijeEkrana.height - 500) / 2, 800, 600);
		frame.setResizable(false);
		frame.setLayout(new GridLayout(1, 0));
		Telefon tel1 = new Telefon(new Broj("+3816311"), Color.GREEN);
		Telefon tel2 = new Telefon(new Broj("387", "64", "33"), Color.YELLOW);
		frame.add(tel1);
		frame.add(tel2);
		frame.addWindowListener(new WindowAdapter() {
			@Override
			public void windowClosing(WindowEvent we) {
				frame.dispose();
				tel1.iskljuci();
				tel2.iskljuci();
			}
		});
		frame.setVisible(true);
	}
}
