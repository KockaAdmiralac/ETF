package kdpl1;

import java.util.concurrent.atomic.AtomicInteger;

public class Progress {
	public final int id;
	public final AtomicInteger progress;

	public Progress(int id, int progress) {
		this.id = id;
		this.progress = new AtomicInteger(progress);
	}
}
