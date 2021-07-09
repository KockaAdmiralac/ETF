package telefon;

public class GNePostoji extends Exception {
	private static final long serialVersionUID = 1L;
	public GNePostoji() {
		super("Zadati broj telefona ili ime nisu u imeniku!");
	}
}
