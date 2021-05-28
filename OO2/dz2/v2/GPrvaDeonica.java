package karting;

public class GPrvaDeonica extends Exception {
	private static final long serialVersionUID = 1L;
	public GPrvaDeonica() {
		super("Prva deonica ne sme imati specifičnosti!");
	}
}
