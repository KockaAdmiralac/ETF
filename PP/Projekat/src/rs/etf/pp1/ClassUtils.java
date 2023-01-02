package rs.etf.pp1;

import java.util.List;

import rs.etf.pp1.semantics.ParameterList;
import rs.etf.pp1.symboltable.concepts.Obj;
import rs.etf.pp1.symboltable.concepts.Struct;

public class ClassUtils {

	public static boolean isSuperclassOf(Struct parent, Struct child) {
		do {
			// HACK: equals will enter an infinite loop if the classes have the same amount
			// of methods and fields
			if (parent == child) {
				return true;
			}
			child = child.getElemType();
		} while (child != null);
		return false;
	}

	public static boolean areTypesAssignable(Struct src, Struct dst) {
		if (src.getKind() != Struct.Class || dst.getKind() != Struct.Class) {
			return src.assignableTo(dst);
		}
		if (isSuperclassOf(dst, src)) {
			return true;
		}
		return src.assignableTo(dst);
	}

	public static boolean areParametersCompatible(Obj method, ParameterList parameters) {
		List<Struct> params = parameters.getParams();
		if (method.getKind() != Obj.Meth || method.getLevel() != params.size()) {
			return false;
		}
		for (Obj o : method.getLocalSymbols()) {
			int pos = o.getFpPos();
			if (pos == 0) {
				continue;
			}
			if (!areTypesAssignable(params.get(pos - 1), o.getType())) {
				return false;
			}
		}
		return true;
	}

}
