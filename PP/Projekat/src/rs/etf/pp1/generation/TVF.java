package rs.etf.pp1.generation;

import java.util.HashMap;
import java.util.Map;

import rs.etf.pp1.mj.runtime.Code;
import rs.etf.pp1.symboltable.concepts.Obj;
import rs.etf.pp1.symboltable.concepts.Struct;

public class TVF {
	private Map<String, Obj> methodMap = new HashMap<>();
	private int ptr;

	public TVF(Struct cls) {
		ptr = Code.dataSize;
		Struct currentClass = cls;
		while (currentClass != null) {
			for (Obj member : currentClass.getMembers()) {
				if (member.getKind() == Obj.Meth && !member.getName().startsWith("$constructor")
						&& !methodMap.containsKey(member.getName())) {
					methodMap.put(member.getName(), member);
					Code.dataSize += member.getName().length() + 2;
				}
			}
			currentClass = currentClass.getElemType();
		}
		++Code.dataSize;
	}

	private void writeConstFromProgram(int adr, int cnst) {
		Code.loadConst(cnst);
		Code.put(Code.putstatic);
		Code.put2(adr);
	}
	
	public void generate() {
		int currentPtr = ptr;
		for (Obj method : methodMap.values()) {
			for (char c : method.getName().toCharArray()) {
				writeConstFromProgram(currentPtr++, c);
			}
			writeConstFromProgram(currentPtr++, -1);
			writeConstFromProgram(currentPtr++, method.getAdr());
		}
		writeConstFromProgram(currentPtr, -2);
	}
	
	public int getPtr() {
		return ptr;
	}
}
