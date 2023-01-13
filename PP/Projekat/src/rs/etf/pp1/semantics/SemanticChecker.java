package rs.etf.pp1.semantics;

import java.util.Collection;
import java.util.List;

import org.apache.log4j.Logger;

import rs.etf.pp1.ClassUtils;
import rs.etf.pp1.Main;
import rs.etf.pp1.ast.*;
import rs.etf.pp1.mj.runtime.Code;
import rs.etf.pp1.symboltable.Tab;
import rs.etf.pp1.symboltable.concepts.Obj;
import rs.etf.pp1.symboltable.concepts.Struct;

public class SemanticChecker extends VisitorAdaptor {
	private Logger logger = Logger.getLogger(SemanticChecker.class);
	private Obj currentType = null;
	private Obj currentClass = null;
	private int numConstructors = 0;
	private Obj currentMethod = null;
	private int loopCount = 0;
	public boolean errorDetected = false;
	private static final String[] objKindNames = { "Con", "Var", "Type", "Meth", "Fld", "Elem", "Prog" };
	private static final String[] structKindNames = { "None", "Int", "Char", "Array", "Class", "Bool" };

	private void error(String message, SyntaxNode node) {
		errorDetected = true;
		String lineMessage = "";
		if (node != null) {
			lineMessage = " (line " + node.getLine() + ")";
		}
		logger.error("Semantic error: " + message + lineMessage);
	}

	private void logSymbol(String message, Obj sym, SyntaxNode node) {
		StringBuilder builder = new StringBuilder(message);
		if (node != null) {
			builder.append(" (line " + node.getLine() + ")");
		}
		builder.append(": [");
		builder.append(sym.getName());
		builder.append(", ");
		builder.append(objKindNames[sym.getKind()]);
		builder.append(", ");
		builder.append(structKindNames[sym.getType().getKind()]);
		builder.append(", ");
		builder.append(sym.getAdr());
		builder.append(", ");
		builder.append(sym.getLevel());
		builder.append("]");
		logger.info(builder.toString());
	}

	private void addParam(String paramName, Struct type) {
		if (currentMethod == null) {
			// ???
			return;
		}
		Obj previousParam = Tab.find(paramName);
		if (previousParam.getKind() == Obj.Var && previousParam.getLevel() == 1) {
			error("Declaration of duplicate parameter " + paramName, null);
			return;
		}
		Obj param = Tab.insert(Obj.Var, paramName, type);
		logSymbol("New parameter detected in current method", param, null);
		currentMethod.setLevel(currentMethod.getLevel() + 1);
		param.setFpPos(currentMethod.getLevel());
	}

	private Designator getPreviousDesignator(Designator designator) {
		if (designator instanceof PropertyAccessDesignator) {
			return ((PropertyAccessDesignator) designator).getDesignator();
		} else if (designator instanceof ArrayAccessDesignator) {
			return ((ArrayAccessDesignator) designator).getDesignator();
		}
		return null;
	}

	private boolean isModifiableDesignator(Designator designator) {
		Obj obj = designator.obj;
		return obj.getKind() == Obj.Elem || obj.getKind() == Obj.Fld || obj.getKind() == Obj.Var;
	}

	private Obj getMethodFromSuperclasses(Struct currentClass, String methodName) {
		Struct superclass = currentClass.getElemType();
		while (superclass != null) {
			for (Obj obj : superclass.getMembers()) {
				if (obj.getKind() == Obj.Meth && obj.getName().equals(methodName)) {
					return obj;
				}
			}
			superclass = superclass.getElemType();
		}
		return null;
	}

	@Override
	public void visit(ProgName node) {
		node.obj = Tab.insert(Obj.Prog, node.getName(), Tab.noType);
		if (node.obj.getKind() != Obj.Prog) {
			error("Program cannot have the same name as one of the predefined types", node);
		}
		logSymbol("Defined program type", node.obj, node);
		Tab.openScope();
	}

	@Override
	public void visit(Program node) {
		node.obj = node.getProgName().obj;
		Code.dataSize = Tab.currentScope.getnVars();
		// Can't chain symbols under the type, as there is no type.
		Tab.chainLocalSymbols(node.obj);
		Tab.closeScope();
	}

	@Override
	public void visit(NumberConst node) {
		node.obj = new Obj(Obj.Con, "$const", Tab.intType, node.getNumber(), 0);
	}

	@Override
	public void visit(CharConst node) {
		node.obj = new Obj(Obj.Con, "$const", Tab.charType, (int) node.getCharconst(), 0);
	}

	@Override
	public void visit(BoolConst node) {
		node.obj = new Obj(Obj.Con, "$const", Main.boolType, node.getBool() ? 1 : 0, 0);
	}

	@Override
	public void visit(Type node) {
		String typeName = node.getTypeName();
		Obj sym = Tab.find(node.getTypeName());
		if (sym == Tab.noObj) {
			currentType = null;
			error("Type " + typeName + " not declared before usage", node);
			return;
		}
		if (sym.getKind() != Obj.Type) {
			currentType = null;
			error("Name " + typeName + " does not represent a type", node);
			return;
		}
		currentType = sym;
	}

	@Override
	public void visit(ConstDeclSingle node) {
		if (currentType == null) {
			// Error reported beforehand, ignoring.
			return;
		}
		if (!node.getConst().obj.getType().equals(currentType.getType())) {
			error("Incompatible types in declaration of " + node.getName(), node);
			return;
		}
		if (Tab.find(node.getName()) != Tab.noObj) {
			error("Constant " + node.getName() + " already defined", node);
			return;
		}
		Obj cnst = Tab.insert(Obj.Con, node.getName(), node.getConst().obj.getType());
		cnst.setAdr(node.getConst().obj.getAdr());
		logSymbol("Found constant declaration", cnst, node);
	}

	@Override
	public void visit(YesArrayBrackets node) {
		if (currentType == null) {
			// Error reported beforehand, ignoring.
			return;
		}
		node.struct = new Struct(Struct.Array, currentType.getType());
	}

	@Override
	public void visit(NoArrayBrackets node) {
		if (currentType == null) {
			// Error reported beforehand, ignoring.
			return;
		}
		node.struct = currentType.getType();
	}

	@Override
	public void visit(VarDeclSingle node) {
		Struct varType = node.getArrayBrackets().struct;
		if (varType == null) {
			// Error reported beforehand, ignoring.
			return;
		}
		boolean isVar = currentClass == null || currentMethod != null;
		Obj prevSym = Tab.find(node.getName());
		Obj sym = Tab.insert(isVar ? Obj.Var : Obj.Fld, node.getName(), varType);
		if (sym == prevSym) {
			error("Duplicate variable or field declaration", node);
			return;
		}
		logSymbol("Variable declaration detected", sym, node);
	}

	@Override
	public void visit(VarDecl node) {
		currentType = null;
	}

	@Override
	public void visit(RegularClassName node) {
		if (Tab.find(node.getName()) != Tab.noObj) {
			error("Class name duplicates another symbol", node);
			return;
		}
		currentClass = Tab.insert(Obj.Type, node.getName(), new Struct(Struct.Class));
		numConstructors = 0;
		Tab.openScope();
		Tab.insert(Obj.Fld, "$tvfp", Tab.intType);
		logSymbol("Class definition detected", currentClass, node);
	}

	@Override
	public void visit(ExtendsClassName node) {
		if (Tab.find(node.getName()) != Tab.noObj) {
			error("Class name duplicates another symbol", node);
			return;
		}
		currentClass = Tab.insert(Obj.Type, node.getName(), new Struct(Struct.Class));
		numConstructors = 0;
		Tab.openScope();
		logSymbol("Class definition with inheritance detected", currentClass, node);
		Obj inheritedClass = Tab.find(node.getTypeName());
		if (inheritedClass == Tab.noObj) {
			error("Class to inherit from, " + node.getTypeName() + ", has not been previously declared", node);
			return;
		}
		if (inheritedClass.getKind() != Obj.Type) {
			error("Class to inherit from, " + node.getTypeName() + ", is not a valid type", node);
			return;
		}
		Struct inheritedType = inheritedClass.getType();
		if (inheritedType == Tab.intType || inheritedType == Tab.charType || inheritedType == Main.boolType) {
			error("Classes cannot inherit from base types", node);
			return;
		}
		currentClass.getType().setElementType(inheritedType);
		for (Obj sym : inheritedClass.getType().getMembers()) {
			if (sym.getKind() == Obj.Meth) {
				continue;
			}
			// Should never return false, considering how we just opened the scope.
			Tab.currentScope.addToLocals(sym);
		}
	}

	@Override
	public void visit(RegularClassDecl node) {
		Tab.chainLocalSymbols(currentClass.getType());
		Tab.closeScope();
		node.obj = currentClass;
		currentClass = null;
	}

	@Override
	public void visit(ConstructorType node) {
		if (currentType == null || !currentType.getType().equals(currentClass.getType())) {
			currentType = null;
			error("Constructor name must be same as the class's name", node);
			return;
		}
		currentType = null;
		currentMethod = Tab.insert(Obj.Meth, "$constructor" + (numConstructors++), Tab.noType);
		currentMethod.setLevel(0);
		logSymbol("Class constructor index " + numConstructors + " detected", currentMethod, node);
		node.obj = currentMethod;
		Tab.openScope();
		addParam("this", currentClass.getType());
	}

	@Override
	public void visit(ConstructorClassMethodBody node) {
		Tab.chainLocalSymbols(currentMethod);
		Tab.closeScope();
		ParameterList parameters = new ParameterList(currentMethod);
		for (int i = 0; i < numConstructors - 1; ++i) {
			Obj constructorMethod = Tab.find("$constructor" + i);
			if (ClassUtils.areParametersCompatible(constructorMethod, parameters)) {
				error("Constructor has the same formal arguments as constructor index " + i, node);
			}
		}
		node.obj = currentMethod;
		currentMethod = null;
	}

	@Override
	public void visit(MethodName node) {
		if (Tab.find(node.getName()) != Tab.noObj) {
			error("Method name duplicates another symbol", node);
			return;
		}
		currentMethod = Tab.insert(Obj.Meth, node.getName(),
				(currentType == null) ? Tab.noType : currentType.getType());
		currentMethod.setLevel(0);
		logSymbol("Method detected", currentMethod, node);
		currentType = null;
		Tab.openScope();
		if (currentClass != null) {
			addParam("this", currentClass.getType());
		}
		node.obj = currentMethod;
	}

	@Override
	public void visit(MethodDecl node) {
		Tab.chainLocalSymbols(currentMethod);
		Tab.closeScope();
		node.obj = currentMethod;
		currentMethod = null;
	}

	@Override
	public void visit(FormParamSingle node) {
		addParam(node.getName(), node.getArrayBrackets().struct);
		currentType = null;
	}

	@Override
	public void visit(FactorTerm node) {
		node.struct = node.getFactor().struct;
	}

	@Override
	public void visit(MulopTerm node) {
		if (!node.getFactor().struct.equals(Tab.intType) || !node.getTerm().struct.equals(Tab.intType)) {
			error("Both operands of a Mulop expression must be integers", node);
			node.struct = Tab.noType;
			return;
		}
		node.struct = Tab.intType;
	}

	@Override
	public void visit(DesignatorFactor node) {
		node.struct = node.getDesignator().obj.getType();
	}

	@Override
	public void visit(FunctionCallFactor node) {
		Obj method = node.getDesignator().obj;
		if (method.getKind() != Obj.Meth) {
			error("Invoked object is not a method", node);
			node.struct = Tab.noType;
			return;
		}
		ParameterList parameters = node.getFunctionCall().parameterlist;
		Designator previousDesignator = getPreviousDesignator(node.getDesignator());
		if (previousDesignator != null && previousDesignator.obj.getType().getKind() == Struct.Class) {
			parameters.addThis(previousDesignator.obj.getType());
		} else if (previousDesignator == null && currentClass != null && currentMethod != null) {
			Obj classMethod = Tab.currentScope.getOuter().findSymbol(method.getName());
			if (classMethod != null && method.equals(classMethod)) {
				parameters.addThis(currentClass.getType());
			} else {
				Obj superclassMethod = getMethodFromSuperclasses(currentClass.getType(), method.getName());
				if (superclassMethod != null && method.equals(superclassMethod)) {
					parameters.addThis(currentClass.getType());
				}
			}
		}
		if (!ClassUtils.areParametersCompatible(method, parameters)) {
			error("Incompatible parameter types in method invocation", node);
			node.struct = Tab.noType;
			return;
		}
		node.struct = method.getType();
		logSymbol("Method invocation detected", method, node);
	}

	@Override
	public void visit(ConstFactor node) {
		node.struct = node.getConst().obj.getType();
	}

	@Override
	public void visit(ArrayReferenceFactor node) {
		if (currentType == null) {
			node.struct = Tab.noType;
			return;
		}
		if (!node.getExpr().struct.equals(Tab.intType)) {
			error("Instantiated array size must be an integer", node);
			node.struct = Tab.noType;
			return;
		}
		node.struct = new Struct(Struct.Array, currentType.getType());
		logSymbol("Array instantiation detected", currentType, node);
		currentType = null;
	}

	@Override
	public void visit(ObjectReferenceFactor node) {
		if (currentType == null) {
			node.struct = Tab.noType;
			return;
		}
		if (currentType.getType().getKind() != Struct.Class) {
			node.struct = Tab.noType;
			error("Only classes and arrays may be instatiated with 'new'", node);
			return;
		}
		ParameterList parameters = node.getFunctionCall().parameterlist;
		Collection<Obj> methods = (currentClass != null && currentClass.equals(currentType))
				? Tab.currentScope.getOuter().getLocals().symbols()
				: currentType.getType().getMembers();
		parameters.addThis(currentType.getType());
		boolean constructorMatches = false;
		for (Obj method : methods) {
			if (!method.getName().startsWith("$constructor")) {
				continue;
			}
			if (ClassUtils.areParametersCompatible(method, parameters)) {
				constructorMatches = true;
			}
		}
		if (!constructorMatches && parameters.getParams().size() > 1) {
			error("No constructor matches the given arguments", node);
			node.struct = Tab.noType;
			return;
		}
		node.struct = currentType.getType();
		logSymbol("Class instantiation detected", currentType, node);
		currentType = null;
	}

	@Override
	public void visit(ExpressionFactor node) {
		node.struct = node.getExpr().struct;
	}

	@Override
	public void visit(TermExpr node) {
		node.struct = node.getTerm().struct;
	}

	@Override
	public void visit(NegatedExpr node) {
		if (!node.getTerm().struct.equals(Tab.intType)) {
			error("Only integers may be negated", node);
			node.struct = Tab.noType;
			return;
		}
		node.struct = Tab.intType;
	}

	@Override
	public void visit(AddopExpr node) {
		if (!node.getExpr().struct.equals(Tab.intType) || !node.getTerm().struct.equals(Tab.intType)) {
			error("Only integers may be added or subtracted", node);
			node.struct = Tab.noType;
			return;
		}
		node.struct = Tab.intType;
	}

	@Override
	public void visit(NegatedAddopExpr node) {
		if (!node.getExpr().struct.equals(Tab.intType) || !node.getTerm().struct.equals(Tab.intType)) {
			error("Only integers may be added, subtracted or negated", node);
			node.struct = Tab.noType;
			return;
		}
		node.struct = Tab.intType;
	}

	@Override
	public void visit(ExprActPars node) {
		node.parameterlist = new ParameterList();
		node.parameterlist.addParam(node.getExpr().struct);
	}

	@Override
	public void visit(ExprListActPars node) {
		node.parameterlist = node.getActPars().parameterlist;
		node.parameterlist.addParam(node.getExpr().struct);
	}

	@Override
	public void visit(ActParsFunctionCall node) {
		node.parameterlist = node.getActPars().parameterlist;
	}

	@Override
	public void visit(NoParsFunctionCall node) {
		node.parameterlist = new ParameterList();
	}

	@Override
	public void visit(OrCondition node) {
		if (!node.getCondition().struct.equals(Main.boolType) || !node.getCondTerm().struct.equals(Main.boolType)) {
			error("Both sides of an OR condition must be booleans", node);
			node.struct = Tab.noType;
			return;
		}
		node.struct = Main.boolType;
	}

	@Override
	public void visit(CondTermCondition node) {
		node.struct = node.getCondTerm().struct;
	}

	@Override
	public void visit(AndCondTerm node) {
		if (!node.getCondTerm().struct.equals(Main.boolType) || !node.getCondFact().struct.equals(Main.boolType)) {
			error("Both sides of an AND condition must be booleans", node);
			node.struct = Tab.noType;
			return;
		}
		node.struct = Main.boolType;
	}

	@Override
	public void visit(CondFactCondTerm node) {
		node.struct = node.getCondFact().struct;
	}

	@Override
	public void visit(ExprCondFact node) {
		node.struct = node.getExpr().struct;
	}

	@Override
	public void visit(RelopCondFact node) {
		if (!node.getExpr().struct.compatibleWith(node.getExpr1().struct)) {
			error("Both sides of a Relop expression must be compatible", node);
			node.struct = Tab.noType;
			return;
		}
		if (node.getExpr().struct.isRefType() && (node.getR2() > 1)) {
			error("When comparing reference types, only == or != may be used", node);
			node.struct = Tab.noType;
			return;
		}
		node.struct = Main.boolType;
	}

	@Override
	public void visit(IdentDesignator node) {
		node.obj = Tab.find(node.getSymName());
		if (node.obj != Tab.noObj) {
			logSymbol("Designator detected", node.obj, node);
			return;
		}
		if (currentClass != null) {
			Obj methodFromSuperclass = getMethodFromSuperclasses(currentClass.getType(), node.getSymName());
			if (methodFromSuperclass != null) {
				node.obj = methodFromSuperclass;
				logSymbol("Method from superclass detected", node.obj, node);
				return;
			}
		}
		error("Symbol " + node.getSymName() + " not found", node);
	}

	@Override
	public void visit(PropertyAccessDesignator node) {
		Obj obj = node.getDesignator().obj;
		if (obj.getType().getKind() != Struct.Class) {
			error("Left-hand side of the property access operator must be an object", node);
			node.obj = Tab.noObj;
			return;
		}
		Collection<Obj> symbols = (currentClass != null && obj.getType().equals(currentClass.getType()))
				? Tab.currentScope.getOuter().getLocals().symbols()
				: obj.getType().getMembers();
		for (Obj field : symbols) {
			if (field.getName().equals(node.getFieldName())) {
				node.obj = field;
				logSymbol("Field access detected", node.obj, node);
				return;
			}
		}
		Obj methodFromSuperclass = getMethodFromSuperclasses(obj.getType(), node.getFieldName());
		if (methodFromSuperclass != null) {
			node.obj = methodFromSuperclass;
			logSymbol("Method from superclass detected during property access", node.obj, node);
			return;
		}
		error("Field " + node.getFieldName() + " not found in type of the left-hand side", node);
		node.obj = Tab.noObj;
	}

	@Override
	public void visit(ArrayAccessDesignator node) {
		Obj obj = node.getDesignator().obj;
		if (obj.getType().getKind() != Struct.Array) {
			error("Left-hand side of the array access operator must be an array", node);
			node.obj = Tab.noObj;
			return;
		}
		if (!node.getExpr().struct.equals(Tab.intType)) {
			error("Index during array access must be an integer", node);
			node.obj = Tab.noObj;
			return;
		}
		node.obj = new Obj(Obj.Elem, "$arrayelem", obj.getType().getElemType());
		logSymbol("Array element access detected", obj, node);
	}

	@Override
	public void visit(AssignmentDesignatorStatement node) {
		Obj obj = node.getDesignator().obj;
		if (!isModifiableDesignator(node.getDesignator())) {
			error("Left hand side of an assignment operation must be modifiable", node);
			return;
		}
		if (!ClassUtils.areTypesAssignable(node.getExpr().struct, obj.getType())) {
			error("Right side of an assignment operation must be compatible with the left side", node);
		}
	}

	@Override
	public void visit(FunctionCallDesignatorStatement node) {
		Obj method = node.getDesignator().obj;
		if (method.getKind() != Obj.Meth) {
			error("Invoked object is not a method", node);
			return;
		}
		Designator previousDesignator = getPreviousDesignator(node.getDesignator());
		ParameterList parameters = node.getFunctionCall().parameterlist;
		if (previousDesignator != null && previousDesignator.obj.getType().getKind() == Struct.Class) {
			parameters.addThis(previousDesignator.obj.getType());
		} else if (previousDesignator == null && currentClass != null && currentMethod != null) {
			Obj classMethod = Tab.currentScope.getOuter().findSymbol(method.getName());
			if (classMethod != null && method.equals(classMethod)) {
				parameters.addThis(currentClass.getType());
			} else {
				Obj superclassMethod = getMethodFromSuperclasses(currentClass.getType(), method.getName());
				if (superclassMethod != null && method.equals(superclassMethod)) {
					parameters.addThis(currentClass.getType());
				}
			}
		}
		if (!ClassUtils.areParametersCompatible(method, parameters)) {
			error("Incompatible parameter types in method invocation", node);
			return;
		}
		logSymbol("Method invocation detected with return value ignored", method, node);
	}

	@Override
	public void visit(UnaryAddopDesignatorStatement node) {
		Obj obj = node.getDesignator().obj;
		if (!isModifiableDesignator(node.getDesignator())) {
			error("Left hand side of an increment/decrement operation must be modifiable", node);
			return;
		}
		if (!obj.getType().equals(Tab.intType)) {
			error("Left hand side of an increment/decrement operation must be an integer", node);
		}
	}

	@Override
	public void visit(IfStatement node) {
		if (!node.getCondition().struct.equals(Main.boolType)) {
			error("Conditional expression in the if statement must be a boolean", node);
		}
	}

	@Override
	public void visit(IfElseStatement node) {
		if (!node.getCondition().struct.equals(Main.boolType)) {
			error("Conditional expression in the if-else statement must be a boolean", node);
		}
	}

	@Override
	public void visit(WhileStatement node) {
		if (!node.getCondition().struct.equals(Main.boolType)) {
			error("Conditional expression in the while statement must be a boolean", node);
		}
		--loopCount;
	}

	@Override
	public void visit(LoopHeader node) {
		++loopCount;
	}

	@Override
	public void visit(BreakStatement node) {
		if (loopCount == 0) {
			error("Break statements may only be used within loops", node);
		}
	}

	@Override
	public void visit(ContinueStatement node) {
		if (loopCount == 0) {
			error("Continue statements may only be used within loops", node);
		}
	}

	@Override
	public void visit(ReturnNoExprStatement node) {
		if (currentMethod == null || currentMethod.getName().startsWith("$constructor")) {
			error("Return statements may only be used within methods", node);
			return;
		}
		if (!currentMethod.getType().equals(Tab.noType)) {
			error("Return statements with no return value may only be used within methods declared as void", node);
		}
	}

	@Override
	public void visit(ReturnExprStatement node) {
		if (currentMethod == null || currentMethod.getName().startsWith("$constructor")) {
			error("Return statements may only be used within methods", node);
			return;
		}
		if (!currentMethod.getType().equals(node.getExpr().struct)) {
			error("Return statement must return an expression of the method's declared return type", node);
		}
	}

	@Override
	public void visit(ReadStatement node) {
		if (!isModifiableDesignator(node.getDesignator())) {
			error("Designator in a read statement must be modifiable", node);
			return;
		}
		Struct objType = node.getDesignator().obj.getType();
		if (!objType.equals(Tab.intType) && !objType.equals(Tab.charType) && !objType.equals(Main.boolType)) {
			error("Designator in a read statement must be an integer, character or boolean", node);
		}
	}

	@Override
	public void visit(PrintNoNumberStatement node) {
		Struct objType = node.getExpr().struct;
		if (!objType.equals(Tab.intType) && !objType.equals(Tab.charType) && !objType.equals(Main.boolType)) {
			error("Expression in a print statement must be an integer, character or boolean", node);
		}
	}

	@Override
	public void visit(PrintNumberStatement node) {
		Struct objType = node.getExpr().struct;
		if (!objType.equals(Tab.intType) && !objType.equals(Tab.charType) && !objType.equals(Main.boolType)) {
			error("Expression in a print statement must be an integer, character or boolean", node);
		}
	}

	@Override
	public void visit(ForeachStatement node) {
		--loopCount;
		Struct designator = node.getDesignator().obj.getType();
		if (designator.getKind() != Struct.Array) {
			error("Designator in a foreach statement must be an array", node);
			return;
		}
		Obj ident = Tab.find(node.getIdent());
		if (ident == Tab.noObj) {
			error("Variable identifier in a foreach statement must be declared before use", node);
			return;
		}
		if (!ident.getType().equals(designator.getElemType())) {
			error("Variable identifier in a foreach statement must be the same type as elements of the designator array",
					node);
		}
		node.obj = ident;
	}

	@Override
	public void visit(EmptyArrayAssignmentDesignators node) {
		node.designatorlist = new DesignatorList();
		node.designatorlist.addDesignator(null);
	}

	@Override
	public void visit(DesignatorArrayAssignmentDesignators node) {
		node.designatorlist = new DesignatorList();
		node.designatorlist.addDesignator(node.getDesignator());
	}

	@Override
	public void visit(MissingListArrayAssignmentDesignators node) {
		node.designatorlist = node.getArrayAssignmentDesignators().designatorlist;
		node.designatorlist.addDesignator(null);
	}

	@Override
	public void visit(DesignatorListArrayAssignmentDesignators node) {
		node.designatorlist = node.getArrayAssignmentDesignators().designatorlist;
		node.designatorlist.addDesignator(node.getDesignator());
	}

	@Override
	public void visit(ArrayAssignmentDesignatorStatement node) {
		Struct designator = node.getDesignator().obj.getType();
		if (designator.getKind() != Struct.Array) {
			error("Designator at the right hand side of an array assignment expression must be an array", node);
			return;
		}
		List<Designator> designators = node.getArrayAssignmentDesignators().designatorlist.getDesignators();
		for (int i = 0; i < designators.size(); ++i) {
			if (designators.get(i) == null) {
				continue;
			}
			if (!isModifiableDesignator(designators.get(i))) {
				error("Designator at index " + i + " in array assignment expression is not assignable", node);
				continue;
			}
			if (!ClassUtils.areTypesAssignable(designators.get(i).obj.getType(), designator.getElemType())) {
				error("Designator at index " + i + " in array assignment expression is of incompatible type", node);
			}
		}
	}

}
