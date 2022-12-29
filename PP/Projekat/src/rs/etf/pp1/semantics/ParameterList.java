package rs.etf.pp1.semantics;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import rs.etf.pp1.symboltable.concepts.Obj;
import rs.etf.pp1.symboltable.concepts.Struct;

public class ParameterList {

	private List<Struct> parameters = new ArrayList<>();
	
	public ParameterList() {}
	
	public ParameterList(Obj method) {
		parameters = Arrays.asList(new Struct[method.getLevel()]);
		for (Obj o : method.getLocalSymbols()) {
			int pos = o.getFpPos();
			if (pos == 0) {
				continue;
			}
			parameters.set(pos - 1, o.getType());
		}
	}
	
	public void addParam(Struct param) {
		parameters.add(param);
	}
	
	public void addThis(Struct thisType) {
		parameters.add(0, thisType);
	}
	
	public List<Struct> getParams() {
		return parameters;
	}
	
}
