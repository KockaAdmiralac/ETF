package rs.etf.pp1.generation;

import java.util.ArrayList;
import java.util.List;

import rs.etf.pp1.mj.runtime.Code;

public class ConditionScope {
	private List<Integer> thenPatchLocations = new ArrayList<>();
	private List<Integer> elsePatchLocations = new ArrayList<>();
	private int jumpLocation;
	private boolean isLoop;
	private ConditionScope parent;

	public ConditionScope(boolean isLoop, ConditionScope parent) {
		jumpLocation = Code.pc;
		this.isLoop = isLoop;
		this.parent = parent;
	}

	public void addThenLocation(int location) {
		thenPatchLocations.add(location);
	}

	public void addElseLocation(int location) {
		elsePatchLocations.add(location);
	}

	private void patchLocations(List<Integer> locations) {
		locations.forEach(loc -> Code.fixup(loc));
		locations.clear();
	}

	public void patchThenLocations() {
		patchLocations(thenPatchLocations);
	}

	public void patchElseLocations() {
		patchLocations(elsePatchLocations);
	}

	public int getJumpLocation() {
		return jumpLocation;
	}

	public ConditionScope getLastLoopScope() {
		if (isLoop) {
			return this;
		}
		return parent.getLastLoopScope();
	}

}
