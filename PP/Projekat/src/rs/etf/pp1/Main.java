package rs.etf.pp1;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

import org.apache.log4j.Logger;
import org.apache.log4j.PropertyConfigurator;

import rs.etf.pp1.symboltable.Tab;
import rs.etf.pp1.syntax.Parser;
import rs.etf.pp1.ast.Program;
import rs.etf.pp1.lex.Yylex;
import rs.etf.pp1.semantics.SemanticChecker;

public class Main {

	public static void main(String[] args) {
		PropertyConfigurator.configure("log4j.properties");
		Logger logger = Logger.getLogger(Main.class);
		CommandLineParser cmd = new CommandLineParser(args);
		if (cmd.getError() != null) {
			logger.error(cmd.getError());
			System.exit(1);
		}
		Tab.init();
		File codeFile = new File(cmd.getProgramFile());
		try (FileReader fr = new FileReader(codeFile); BufferedReader br = new BufferedReader(fr);) {
			//
			Yylex lexer = new Yylex(br);
			Parser parser = new Parser(lexer);
			Program program = (Program) parser.parse().value;
			logger.debug(program.toString(""));
			SemanticChecker semanticChecker = new SemanticChecker();
			program.traverseBottomUp(semanticChecker);

			// Useful debug information after code generation.
			if (cmd.isDebug()) {
				Tab.dump();
			}
		} catch (FileNotFoundException e) {
			logger.error("Specified file " + cmd.getProgramFile() + " not found.", e);
		} catch (IOException e) {
			logger.error("Unknown IO error.", e);
		} catch (Exception e) {
			logger.error("Unknown error.", e);
		}
	}

}
