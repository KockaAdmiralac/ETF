package kockanje;

import java.awt.BorderLayout;
import java.awt.Button;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Frame;
import java.awt.GridLayout;
import java.awt.Label;
import java.awt.Panel;
import java.awt.TextField;
import java.awt.Toolkit;
import java.awt.event.ComponentAdapter;
import java.awt.event.ComponentEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.util.HashSet;

public class Igra extends Frame {
	private static final long serialVersionUID = 1L;
	private static final int INICIJALNA_VISINA_MREZE = 4 * 75 + 3 * 3;
	private static final int INICIJALNA_SIRINA_MREZE = 5 * 75 + 4 * 3;
	private static final int INICIJALNA_VISINA_PROZORA = 350;
	private static final int INICIJALNA_SIRINA_PROZORA = 600;
	private Mreza mreza = new Mreza(this);
	private double balans = 0;
	private double dobitak;
	private double ulog;
	private Label balansLabela = new Label("0");
	private TextField ulogPolje = new TextField("100");
	private Label kvotaLabela = new Label("");
	private Label dobitakLabela = new Label("");
	private Panel desniPanel = new Panel(new GridLayout(5, 1));
	private Button igrajDugme = new Button("Igraj");
	private Panel donjiPanel = new Panel();
	private Generator generator = new Generator();
	public Igra() {
		setTitle("Igra");
		Dimension dimenzijeEkrana = Toolkit.getDefaultToolkit().getScreenSize();
		setBounds((dimenzijeEkrana.width - getWidth()) / 2, (dimenzijeEkrana.height - getHeight()) / 2, INICIJALNA_SIRINA_PROZORA, INICIJALNA_VISINA_PROZORA);
		setResizable(true);
		setLayout(new BorderLayout());
		mreza.populate();
		add(mreza, BorderLayout.CENTER);
		Panel balansPanel = new Panel(new BorderLayout());
		balansPanel.add(new Label("Balans:"), BorderLayout.WEST);
		balansPanel.add(balansLabela, BorderLayout.CENTER);
		desniPanel.add(balansPanel);
		Panel ulogPanel = new Panel(new BorderLayout());
		ulogPanel.add(new Label("Ulog:"), BorderLayout.WEST);
		ulogPanel.add(ulogPolje, BorderLayout.CENTER);
		desniPanel.add(ulogPanel);
		Panel kvotaPanel = new Panel(new BorderLayout());
		kvotaPanel.add(new Label("Kvota:"), BorderLayout.WEST);
		kvotaPanel.add(kvotaLabela, BorderLayout.CENTER);
		desniPanel.add(kvotaPanel);
		Panel dobitakPanel = new Panel(new BorderLayout());
		dobitakPanel.add(new Label("Dobitak:"), BorderLayout.WEST);
		dobitakPanel.add(dobitakLabela, BorderLayout.CENTER);
		desniPanel.add(dobitakPanel);
		Panel igrajPanel = new Panel(new BorderLayout());
		igrajPanel.add(igrajDugme, BorderLayout.EAST);
		desniPanel.add(igrajPanel);
		add(desniPanel, BorderLayout.EAST);
		Label statusLabela = new Label("");
		donjiPanel.add(statusLabela);
		donjiPanel.setBackground(Color.DARK_GRAY);
		add(donjiPanel, BorderLayout.SOUTH);
		azurirajStanje();
		resized();
		pack();
		igrajDugme.addActionListener((ae) -> {
			int broj = generator.broj(0, mreza.brojPolja() - 1);
			if (mreza.dohvIzabrane().contains(broj)) {
				balans += dobitak;
				donjiPanel.setBackground(Color.GREEN);
			} else {
				balans -= ulog;
				donjiPanel.setBackground(Color.RED);
			}
			balansLabela.setText(String.valueOf(balans));
			balansLabela.revalidate();
			statusLabela.setText(String.valueOf(broj));
			statusLabela.revalidate();
		});
		ulogPolje.addTextListener((te) -> {
			azurirajStanje();
		});
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
	void resized() {
		mreza.setPreferredSize(new Dimension((int)(1.0 * getWidth() / INICIJALNA_SIRINA_PROZORA * INICIJALNA_SIRINA_MREZE), (int)(1.0 * getHeight() / INICIJALNA_VISINA_PROZORA * INICIJALNA_VISINA_MREZE)));
		desniPanel.setPreferredSize(new Dimension((int)(1.0 * getWidth() / INICIJALNA_SIRINA_PROZORA * (INICIJALNA_SIRINA_PROZORA - INICIJALNA_SIRINA_MREZE)), (int)(1.0 * getHeight() / INICIJALNA_VISINA_PROZORA * INICIJALNA_VISINA_MREZE)));
		donjiPanel.setPreferredSize(new Dimension(getWidth(), (int)(1.0 * getHeight() / INICIJALNA_VISINA_PROZORA * (INICIJALNA_VISINA_PROZORA - INICIJALNA_VISINA_MREZE))));
	}
	void azurirajStanje() {
		HashSet<Integer> izabrani = mreza.dohvIzabrane();
		igrajDugme.setEnabled(izabrani.size() != 0);
		if (izabrani.size() == 0) {
			kvotaLabela.setText("");
			dobitakLabela.setText("");
			dobitak = 0;
			ulog = 0;
		} else {
			try {
				ulog = Double.parseDouble(ulogPolje.getText());
			} catch (NumberFormatException e) {
				ulog = 0;
			}
			double kvota = 1.0 * mreza.brojPolja() / izabrani.size();
			dobitak = kvota * ulog;
			kvotaLabela.setText(String.valueOf(kvota));
			dobitakLabela.setText(String.valueOf(dobitak));
		}
		kvotaLabela.revalidate();
		dobitakLabela.revalidate();
	}
}
