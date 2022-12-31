package rs.etf.pp1;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;

import org.apache.log4j.Logger;
import org.apache.log4j.PropertyConfigurator;

import java_cup.runtime.Symbol;
import rs.etf.pp1.symboltable.Tab;
import rs.etf.pp1.symboltable.concepts.Obj;
import rs.etf.pp1.symboltable.concepts.Scope;
import rs.etf.pp1.symboltable.concepts.Struct;
import rs.etf.pp1.symboltable.visitors.SymbolTableVisitor;
import rs.etf.pp1.syntax.Parser;
import rs.etf.pp1.ast.Program;
import rs.etf.pp1.generation.CodeGeneration;
import rs.etf.pp1.lex.Yylex;
import rs.etf.pp1.mj.runtime.Code;
import rs.etf.pp1.mj.runtime.Run;
import rs.etf.pp1.mj.runtime.disasm;
import rs.etf.pp1.semantics.NonDumbSymbolTableVisitor;
import rs.etf.pp1.semantics.SemanticChecker;

public class Main {

	public static Struct boolType = new Struct(Struct.Bool);

	public static void main(String[] args) {
		PropertyConfigurator.configure("log4j.properties");
		Logger logger = Logger.getLogger(Main.class);
		CommandLineParser cmd = new CommandLineParser(args);
		if (cmd.getError() != null) {
			logger.error(cmd.getError());
			System.exit(1);
		}
		Tab.init();
		Tab.currentScope.addToLocals(new Obj(Obj.Type, "bool", boolType));
		File codeFile = new File(cmd.getProgramFile());
		try (
			FileReader fr = new FileReader(codeFile);
			BufferedReader br = new BufferedReader(fr);
		) {
			Yylex lexer = new Yylex(br);
			Parser parser = new Parser(lexer);
			Symbol symbol = parser.parse();
			if (parser.errorDetected) {
				logger.error("Parser errors found, not continuing.");
				System.exit(2);
			}
			Program program = (Program) symbol.value;
			logger.debug(program.toString(""));
			SemanticChecker semanticChecker = new SemanticChecker();
			program.traverseBottomUp(semanticChecker);
			tsdump(logger);
			if (semanticChecker.errorDetected) {
				logger.error("Semantic errors found, not continuing.");
				System.exit(3);
			}
			CodeGeneration generator = new CodeGeneration();
			program.traverseBottomUp(generator);
			File objectFile = new File(cmd.getObjectFile());
			if (objectFile.exists()) {
				objectFile.delete();
			}
			Code.write(new FileOutputStream(objectFile));
			logger.info("Compilation successful.");
			String[] argv = new String[] {cmd.getObjectFile()};
			if (cmd.isDebug()) {
				disasm.main(argv);
			}
			if (cmd.isRun()) {
				Run.main(argv);
			}
		} catch (FileNotFoundException e) {
			logger.error("Specified file " + cmd.getProgramFile() + " not found.", e);
			System.exit(4);
		} catch (IOException e) {
			logger.error("Unknown IO error.", e);
			System.exit(5);
		} catch (Exception e) {
			logger.error("Unknown error.", e);
			System.exit(6);
		}
	}

	private static void tsdump(Logger logger) {
		logger.debug("==================== SYMBOL TABLE DUMP ========================");
		SymbolTableVisitor stv = new NonDumbSymbolTableVisitor();
		for (Scope s = Tab.currentScope; s != null; s = s.getOuter()) {
			s.accept(stv);
		}
		logger.debug(stv.getOutput());
	}

}
