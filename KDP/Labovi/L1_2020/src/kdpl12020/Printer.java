package kdpl12020;

import java.util.List;
import java.util.TreeSet;
import java.util.concurrent.ConcurrentMap;

public class Printer extends Thread {
	private final long interval;
	private final ConcurrentMap<Integer, Integer> progress;
	private final Barrier printerBarrier;
	private final List<Film> finalData;

	public Printer(long interval, ConcurrentMap<Integer, Integer> progress, Barrier printerBarrier, List<Film> finalData) {
		super("Printer");
		this.interval = interval;
		this.progress = progress;
		this.printerBarrier = printerBarrier;
		this.finalData = finalData;
	}

	@Override
	public void run() {
		while (true) {
			if (printerBarrier.await(interval * 1000)) {
				break;
			}
			for (Integer id : new TreeSet<Integer>(progress.keySet())) {
				System.out.println("Consumer " + id + ": " + progress.get(id));
			}
		}
		System.out.println("Final result:");
		for (Film film : finalData) {
			System.out.println(film.tconst + " (" + film.directors.length + ")");
		}
	}

}
