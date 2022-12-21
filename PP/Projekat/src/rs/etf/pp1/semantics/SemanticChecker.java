package rs.etf.pp1.semantics;

import org.apache.log4j.Logger;

import rs.etf.pp1.ast.Program;
import rs.etf.pp1.ast.VisitorAdaptor;

public class SemanticChecker extends VisitorAdaptor {
	Logger logger = Logger.getLogger(SemanticChecker.class);
	
	public void visit(Program program) {
		logger.info("Found 'program'.");
	}
}
