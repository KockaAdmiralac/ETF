package rs.etf.pp1;

public class CommandLineParser {
	private String error = null;
	private String programFile;
	private String objectFile;
	private boolean debug = false;
	private boolean run = false;

	public CommandLineParser(String args[]) {
		if (args.length < 1) {
			error = "Program file to compile not specified.";
			return;
		}
		if (args.length < 2) {
			error = "Object file to output not specified";
			return;
		}
		programFile = args[0];
		objectFile = args[1];
		for (int i = 1; i < args.length; ++i) {
			if (args[i].equals("--debug")) {
				debug = true;
			} else if (args[i].equals("--run")) {
				run = true;
			}
		}
	}

	public String getError() {
		return error;
	}

	public String getProgramFile() {
		return programFile;
	}

	public String getObjectFile() {
		return objectFile;
	}

	public boolean isDebug() {
		return debug;
	}

	public boolean isRun() {
		return run;
	}
}
