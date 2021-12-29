package rs.ac.bg.etf.rm2.projekat;

import java.awt.Button;
import java.awt.GridLayout;

import javax.swing.JFrame;

import com.ireasoning.protocol.snmp.SnmpSession;

public class Main extends JFrame {
	private static final long serialVersionUID = 2430549939571029723L;
	public static final int[] SUPPORTED_VARIANTS = {4, 5, 6, 7, 9};
	
	public Main() {
		setTitle("RM2 projekat");
		setLayout(new GridLayout());
		for (int variantNumber : SUPPORTED_VARIANTS) {
			Button variantButton = new Button("Varijanta " + variantNumber);
			variantButton.addActionListener(ae -> {
				Variant variant = getVariantByNumber(variantNumber);
				variant.setTitle("RM2 projekat, varijanta " + variantNumber);
				variant.setVisible(true);
				dispose();
			});
			add(variantButton);
		}
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		pack();
	}
	
	private static Variant getVariantByNumber(int number) {
		switch (number) {
			case 4: return new Variant4();
			case 5: return new Variant5();
			case 6: return new Variant6();
			case 7: return new Variant7();
			case 9: return new Variant9();
		}
		return null;
	}
	
	public static void main(String[] args) {
		SnmpSession.loadMib2();
		Main main = new Main();
		main.setVisible(true);
	}
}
