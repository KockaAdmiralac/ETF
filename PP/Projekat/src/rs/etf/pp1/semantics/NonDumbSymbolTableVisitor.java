package rs.etf.pp1.semantics;

import java.util.HashMap;
import java.util.Map;

import rs.etf.pp1.symboltable.concepts.Obj;
import rs.etf.pp1.symboltable.concepts.Scope;
import rs.etf.pp1.symboltable.concepts.Struct;
import rs.etf.pp1.symboltable.visitors.SymbolTableVisitor;

public class NonDumbSymbolTableVisitor extends SymbolTableVisitor {

	private StringBuilder output = new StringBuilder();
	private final String indent = "\t";
	private StringBuilder currentIndent = new StringBuilder();
	private Map<Struct, String> visitedClasses = new HashMap<>();
	private String lastVisitedName;

	protected void nextIndentationLevel() {
		currentIndent.append(indent);
	}

	protected void previousIndentationLevel() {
		if (currentIndent.length() > 0)
			currentIndent.setLength(currentIndent.length() - indent.length());
	}

	@Override
	public void visitObjNode(Obj objToVisit) {
		switch (objToVisit.getKind()) {
		case Obj.Con:
			output.append("Con ");
			break;
		case Obj.Var:
			output.append("Var ");
			break;
		case Obj.Type:
			output.append("Type ");
			break;
		case Obj.Meth:
			output.append("Meth ");
			break;
		case Obj.Fld:
			output.append("Fld ");
			break;
		case Obj.Prog:
			output.append("Prog ");
			break;
		}

		output.append(objToVisit.getName());
		lastVisitedName = objToVisit.getName();
		output.append(": ");
		objToVisit.getType().accept(this);
		output.append(", ");
		output.append(objToVisit.getAdr());
		output.append(", ");
		output.append(objToVisit.getLevel() + " ");

		if (objToVisit.getKind() == Obj.Prog || objToVisit.getKind() == Obj.Meth) {
			output.append("\n");
			nextIndentationLevel();
		}

		for (Obj o : objToVisit.getLocalSymbols()) {
			output.append(currentIndent.toString());
			o.accept(this);
			output.append("\n");
		}

		if (objToVisit.getKind() == Obj.Prog || objToVisit.getKind() == Obj.Meth)
			previousIndentationLevel();

	}

	@Override
	public void visitScopeNode(Scope scope) {
		for (Obj o : scope.values()) {
			o.accept(this);
			output.append("\n");
		}
	}

	@Override
	public void visitStructNode(Struct structToVisit) {
		switch (structToVisit.getKind()) {
		case Struct.None:
			output.append("notype");
			break;
		case Struct.Int:
			output.append("int");
			break;
		case Struct.Char:
			output.append("char");
			break;
		case Struct.Bool:
			output.append("bool");
			break;
		case Struct.Array:
			output.append("Arr of ");

			switch (structToVisit.getElemType().getKind()) {
			case Struct.None:
				output.append("notype");
				break;
			case Struct.Int:
				output.append("int");
				break;
			case Struct.Char:
				output.append("char");
				break;
			case Struct.Class:
				output.append("Class");
				break;
			}
			break;
		case Struct.Class:
			output.append("Class [");
			String className = visitedClasses.get(structToVisit);
			if (className == null) {
				visitedClasses.put(structToVisit, lastVisitedName);
				nextIndentationLevel();
				for (Obj obj : structToVisit.getMembers()) {
					output.append("\n");
					output.append(currentIndent.toString());
					obj.accept(this);
				}
				if (!structToVisit.getMembers().isEmpty()) {
					output.append("\n");
				}
				previousIndentationLevel();
				output.append(currentIndent.toString());
			} else {
				output.append(className);
			}
			output.append("]");
			break;
		}

	}

	@Override
	public String getOutput() {
		return output.toString();
	}

}
