package rs.etf.pp1.generation;

import java.util.List;
import java.util.SortedMap;
import java.util.Stack;
import java.util.TreeMap;

import rs.etf.pp1.ClassUtils;
import rs.etf.pp1.Main;
import rs.etf.pp1.ast.*;
import rs.etf.pp1.mj.runtime.Code;
import rs.etf.pp1.semantics.ParameterList;
import rs.etf.pp1.symboltable.Tab;
import rs.etf.pp1.symboltable.concepts.Obj;
import rs.etf.pp1.symboltable.concepts.Struct;

public class CodeGeneration extends VisitorAdaptor {

	private Stack<ConditionScope> conditionScopes = new Stack<>();
	private SortedMap<String, TVF> vtables = new TreeMap<>();
	private Obj currentClass = null;
	private int returnErrorHandler;

	@Override
	public void visit(ProgName node) {
		Obj chr = Tab.find("chr");
		Obj ord = Tab.find("ord");
		Obj len = Tab.find("len");
		// chr() function
		chr.setAdr(Code.pc);
		Code.put(Code.return_);
		// ord() function
		ord.setAdr(Code.pc);
		Code.put(Code.return_);
		// len() function
		len.setAdr(Code.pc);
		Code.put(Code.arraylength);
		Code.put(Code.return_);
		// Error handler when no return was found.
		returnErrorHandler = Code.pc;
		String errorMessage = "No value returned from method";
		for (char c : errorMessage.toCharArray()) {
			Code.loadConst(c);
			Code.loadConst(1);
			Code.put(Code.bprint);
		}
		Code.put(Code.trap);
		Code.put(1);
	}

	private void exitReturn() {
		Code.put(Code.exit);
		Code.put(Code.return_);
	}

	private boolean designatorParentIsStore(Designator designator) {
		SyntaxNode parent = designator.getParent();
		return (parent instanceof FunctionCallFactor) || (parent instanceof DesignatorStatement)
				|| (parent instanceof ArrayAssignmentDesignators) || (parent instanceof ReadStatement);
	}

	private Obj findConstructorWithParams(Struct cls, ParameterList params) {
		for (Obj meth : cls.getMembers()) {
			if (meth.getKind() != Obj.Meth || !meth.getName().startsWith("$constructor")) {
				continue;
			}
			if (ClassUtils.areParametersCompatible(meth, params)) {
				return meth;
			}
		}
		return null;
	}

	@Override
	public void visit(MethodName node) {
		node.obj.setAdr(Code.pc);
		if (node.obj.getName().equals("main") && currentClass == null) {
			Code.mainPc = Code.pc;
			for (TVF tvf : vtables.values()) {
				tvf.generate();
			}
		}
		Code.put(Code.enter);
		Code.put(node.obj.getLevel());
		Code.put(node.obj.getLocalSymbols().size());
	}

	@Override
	public void visit(ConstructorType node) {
		node.obj.setAdr(Code.pc);
		Code.put(Code.enter);
		Code.put(node.obj.getLevel());
		Code.put(node.obj.getLocalSymbols().size());
	}

	@Override
	public void visit(RegularClassName node) {
		currentClass = ((ClassDecl) node.getParent()).obj;
	}

	@Override
	public void visit(ExtendsClassName node) {
		currentClass = ((ClassDecl) node.getParent()).obj;
	}

	@Override
	public void visit(ClassDecl node) {
		vtables.put(node.obj.getName(), new TVF(node.obj.getType()));
		currentClass = null;
	}

	@Override
	public void visit(MethodDecl node) {
		if (node.obj.getType().equals(Tab.noType)) {
			exitReturn();
		} else {
			Code.putJump(returnErrorHandler);
		}
	}

	@Override
	public void visit(ConstructorClassMethodBody node) {
		exitReturn();
	}

	@Override
	public void visit(ReturnNoExprStatement node) {
		exitReturn();
	}

	@Override
	public void visit(ReturnExprStatement node) {
		exitReturn();
	}

	@Override
	public void visit(ConstFactor node) {
		Code.load(node.getConst().obj);
	}

	@Override
	public void visit(AssignmentDesignatorStatement node) {
		Code.store(node.getDesignator().obj);
	}

	@Override
	public void visit(IdentDesignator node) {
		if (currentClass != null) {
			boolean isFunctionCall = (node.getParent() instanceof FunctionCallFactor
					|| node.getParent() instanceof FunctionCallDesignatorStatement);
			boolean isMember = currentClass.getType().getMembersTable().searchKey(node.obj.getName()) == node.obj;
			if (isFunctionCall || isMember) {
				// Push 'this' to stack.
				Code.put(Code.load_n + 0);
			}
		}
		if (!designatorParentIsStore(node)) {
			Code.load(node.obj);
		}
	}

	@Override
	public void visit(PropertyAccessDesignator node) {
		if (!designatorParentIsStore(node)) {
			Code.load(node.obj);
		}
	}

	@Override
	public void visit(ArrayAccessDesignator node) {
		if (!designatorParentIsStore(node)) {
			Code.load(node.obj);
		}
	}

	@Override
	public void visit(PrintNoNumberStatement node) {
		if (node.getExpr().struct.equals(Tab.charType)) {
			Code.loadConst(1);
			Code.put(Code.bprint);
		} else if (node.getExpr().struct.equals(Main.boolType)) {
			Code.loadConst(1);
			Code.put(Code.print);
		} else {
			Code.loadConst(5);
			Code.put(Code.print);
		}
	}

	@Override
	public void visit(PrintNumberStatement node) {
		Code.loadConst(node.getN2());
		if (node.getExpr().struct.equals(Tab.intType)) {
			Code.put(Code.print);
		} else {
			Code.put(Code.bprint);
		}
	}

	@Override
	public void visit(FunctionCallFactor node) {
		boolean accessOverObject = node.getDesignator() instanceof PropertyAccessDesignator;
		if (currentClass == null && !accessOverObject) {
			Code.put(Code.call);
			Code.put2(node.getDesignator().obj.getAdr() - Code.pc + 1);
		} else {
			// Push 'this' to stack.
			node.getDesignator().traverseBottomUp(this);
			// Get the TVF address.
			Code.put(Code.getfield);
			Code.put2(0);
			// Call the virtual method by name.
			Code.put(Code.invokevirtual);
			for (char c : node.getDesignator().obj.getName().toCharArray()) {
				Code.put4(c);
			}
			Code.put4(-1);
		}
	}

	@Override
	public void visit(FunctionCallDesignatorStatement node) {
		boolean accessOverObject = node.getDesignator() instanceof PropertyAccessDesignator;
		if (currentClass == null && !accessOverObject) {
			Code.put(Code.call);
			Code.put2(node.getDesignator().obj.getAdr() - Code.pc + 1);
		} else {
			// Push 'this' to stack.
			node.getDesignator().traverseBottomUp(this);
			// Get the TVF address.
			Code.put(Code.getfield);
			Code.put2(0);
			// Call the virtual method by name.
			Code.put(Code.invokevirtual);
			for (char c : node.getDesignator().obj.getName().toCharArray()) {
				Code.put4(c);
			}
			Code.put4(-1);
		}
		if (node.getDesignator().obj.getType() != Tab.noType) {
			// Remove return result from expression stack.
			Code.put(Code.pop);
		}
	}

	@Override
	public void visit(ArrayReferenceFactor node) {
		Struct typeToAllocate = node.struct.getElemType();
		Code.put(Code.newarray);
		Code.put(typeToAllocate.equals(Tab.charType) ? 0 : 1);
	}

	@Override
	public void visit(NewHeader node) {
		ObjectReferenceFactor parent = (ObjectReferenceFactor) node.getParent();
		Code.put(Code.new_);
		Code.put2(parent.struct.getNumberOfFields() * 4);
		// Stack: (obj)
		Code.put(Code.dup);
		// Stack: (obj) (obj)
		Code.loadConst(vtables.get(parent.getType().getTypeName()).getPtr());
		// Stack: (obj) (obj) (ptr)
		Code.put(Code.putfield);
		Code.put2(0);
		// Stack: (obj)
		Code.put(Code.dup);
		// Stack: (obj) (obj)
	}

	@Override
	public void visit(ObjectReferenceFactor node) {
		Obj constructor = findConstructorWithParams(node.struct, node.getFunctionCall().parameterlist);
		// Stack: (obj) (obj) <params>
		if (constructor == null) {
			// This is only possible for default constructors, so there are no parameters.
			Code.put(Code.pop);
		} else {
			Code.put(Code.call);
			Code.put2(constructor.getAdr() - Code.pc + 1);
		}
		// Stack: (obj)
	}

	@Override
	public void visit(MulopTerm node) {
		Code.put(node.getM2());
	}

	@Override
	public void visit(NegatedExpr node) {
		if (node.getA1() == Code.sub) {
			Code.put(Code.neg);
		}
	}

	@Override
	public void visit(AddopExpr node) {
		Code.put(node.getA2());
	}

	@Override
	public void visit(NegatedAddopExpr node) {
		if (node.getA1() == Code.sub) {
			// THIS IS A HACK
			if (node.getA3() == Code.add) {
				// Stack: (a) (b)
				Code.put(Code.dup2);
				// Stack: (a) (b) (a) (b)
				Code.put(Code.pop);
				// Stack: (a) (b) (a)
				Code.put(Code.dup_x1);
				// Stack: (a) (a) (b) (a)
				Code.put(Code.add);
				// Stack: (a) (a) (b+a)
				Code.put(Code.neg);
				// Stack: (a) (a) (-b-a)
				Code.put(Code.add);
				// Stack: (a) (-b)
				Code.put(Code.add);
				// Stack: (a-b)
				Code.put(Code.neg);
				// Stack: (-a+b)
			} else {
				// Stack: (a) (b)
				Code.put(Code.add);
				// Stack: (a+b)
				Code.put(Code.neg);
				// Stack: (-a-b)
			}
		} else {
			Code.put(node.getA3());
		}
	}

	@Override
	public void visit(UnaryAddopDesignatorStatement node) {
		Obj obj = node.getDesignator().obj;
		if (obj.getKind() == Obj.Elem) {
			Code.put(Code.dup2);
		} else if (obj.getKind() == Obj.Fld) {
			Code.put(Code.dup);
		}
		Code.load(obj);
		Code.loadConst(1);
		Code.put(node.getOp());
		Code.store(obj);
	}

	@Override
	public void visit(ArrayAssignmentDesignatorStatement node) {
		Obj src = node.getDesignator().obj;
		Code.load(src);
		List<Designator> designators = node.getArrayAssignmentDesignators().designatorlist.getDesignators();
		for (int i = designators.size() - 1; i >= 0; --i) {
			if (designators.get(i) == null) {
				continue;
			}
			Obj dst = designators.get(i).obj;
			if (dst.getKind() == Obj.Elem) {
				Code.put(Code.dup_x2);
			} else if (dst.getKind() == Obj.Fld) {
				Code.put(Code.dup_x1);
			} else {
				Code.put(Code.dup);
			}
			Code.loadConst(i);
			if (src.getType().getElemType().getKind() == Struct.Char) {
				Code.put(Code.baload);
			} else {
				Code.put(Code.aload);
			}
			Code.store(dst);
		}
		Code.put(Code.pop);
	}

	@Override
	public void visit(ReadStatement node) {
		Obj dst = node.getDesignator().obj;
		if (dst.getType().getKind() == Struct.Char) {
			Code.put(Code.bread);
		} else {
			Code.put(Code.read);
		}
		Code.store(dst);
	}

	@Override
	public void visit(IfHeader node) {
		conditionScopes.push(new ConditionScope(false, conditionScopes.empty() ? null : conditionScopes.peek()));
	}

	@Override
	public void visit(Or node) {
		Code.putJump(0);
		ConditionScope scope = conditionScopes.peek();
		scope.addThenLocation(Code.pc - 2);
		scope.patchElseLocations();
	}

	@Override
	public void visit(ExprCondFact node) {
		Code.loadConst(0);
		Code.putFalseJump(Code.ne, 0);
		conditionScopes.peek().addElseLocation(Code.pc - 2);
	}

	@Override
	public void visit(RelopCondFact node) {
		Code.putFalseJump(node.getR2(), 0);
		conditionScopes.peek().addElseLocation(Code.pc - 2);
	}

	@Override
	public void visit(ThenHeader node) {
		conditionScopes.peek().patchThenLocations();
	}

	@Override
	public void visit(IfStatement node) {
		conditionScopes.pop().patchElseLocations();
	}

	@Override
	public void visit(ElseHeader node) {
		Code.putJump(0);
		ConditionScope scope = conditionScopes.peek();
		scope.addThenLocation(Code.pc - 2);
		scope.patchElseLocations();
	}

	@Override
	public void visit(IfElseStatement node) {
		// Patches the jump before the 'else' clause.
		conditionScopes.pop().patchThenLocations();
	}

	@Override
	public void visit(LoopHeader node) {
		SyntaxNode parent = node.getParent();
		if (parent instanceof ForeachStatement) {
			// Stack: (adr) (0)
			Code.loadConst(0);
		}
		conditionScopes.push(new ConditionScope(true, conditionScopes.empty() ? null : conditionScopes.peek()));
		if (parent instanceof ForeachStatement) {
			ForeachStatement stmt = (ForeachStatement) parent;
			Obj ident = stmt.obj;
			// Stack: (adr) (idx)
			Code.put(Code.dup2);
			// Stack: (adr) (idx) (adr) (idx)
			Code.put(Code.dup_x1);
			// Stack: (adr) (idx) (idx) (adr) (idx)
			Code.put(Code.pop);
			// Stack: (adr) (idx) (idx) (adr)
			Code.put(Code.arraylength);
			// Stack: (adr) (idx) (idx) (len)
			// Condition: idx < len
			Code.putFalseJump(Code.lt, 0);
			conditionScopes.peek().addElseLocation(Code.pc - 2);
			// Stack: (adr) (idx)
			Code.put(Code.dup2);
			// Stack: (adr) (idx) (adr) (idx)
			if (stmt.getDesignator().obj.getType().getElemType().equals(Tab.charType)) {
				Code.put(Code.baload);
			} else {
				Code.put(Code.aload);
			}
			// Stack: (adr) (idx) (val)
			Code.store(ident);
			// Stack: (adr) (idx)
			Code.loadConst(1);
			// Stack: (adr) (idx) (1)
			Code.put(Code.add);
			// Stack: (adr) (idx+1)
		}
	}

	@Override
	public void visit(WhileStatement node) {
		ConditionScope scope = conditionScopes.pop();
		Code.putJump(scope.getJumpLocation());
		scope.patchElseLocations();
	}

	@Override
	public void visit(BreakStatement node) {
		Code.putJump(0);
		conditionScopes.peek().getLastLoopScope().addElseLocation(Code.pc - 2);
	}

	@Override
	public void visit(ContinueStatement node) {
		Code.putJump(conditionScopes.peek().getLastLoopScope().getJumpLocation());
	}

	@Override
	public void visit(ForeachStatement node) {
		ConditionScope scope = conditionScopes.pop();
		Code.putJump(scope.getJumpLocation());
		scope.patchElseLocations();
		// Stack: (adr) (idx)
		Code.put(Code.pop);
		// Stack: (adr)
		Code.put(Code.pop);
		// Stack: -
	}

}
