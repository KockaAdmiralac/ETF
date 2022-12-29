package rs.etf.pp1.semantics;

import java.util.ArrayList;
import java.util.List;

import rs.etf.pp1.ast.Designator;

public class DesignatorList {

	private List<Designator> designators = new ArrayList<>();

	public void addDesignator(Designator designator) {
		designators.add(designator);
	}

	public List<Designator> getDesignators() {
		return designators;
	}

}
