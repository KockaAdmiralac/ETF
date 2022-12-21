package rs.etf.pp1;

public class CommandLineParser {
	private String error = null;
	private String programFile;
	private boolean debug = false;
	
	public CommandLineParser(String args[]) {
		if (args.length < 1) {
			error = "Program file to compile not specified.";
			return;
		}
		programFile = args[0];
		for (int i = 1; i < args.length; ++i) {
			if (args[i].equals("--debug")) {
				debug = true;
			}
		}
	}
	
	public String getError() {
		return error;
	}

	public String getProgramFile() {
		return programFile;
	}

	public boolean isDebug() {
		return debug;
	}
}
