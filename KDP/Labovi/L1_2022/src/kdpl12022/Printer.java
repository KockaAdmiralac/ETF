package kdpl12022;

import java.util.Map;
import java.util.concurrent.atomic.AtomicInteger;

public class Printer extends Thread {
	private final long printTime;
	private final AtomicInteger totalFilms;
	private final AtomicInteger matchedFilms;
	private final Barrier printerBarrier;
	private final Map<Integer, Map<String, Film>> maximumRatings;

	public Printer(long printTime, AtomicInteger totalFilms, AtomicInteger matchedFilms, Barrier printerBarrier,
			Map<Integer, Map<String, Film>> maximumRatings) {
		super("Printer");
		this.printTime = printTime;
		this.totalFilms = totalFilms;
		this.matchedFilms = matchedFilms;
		this.printerBarrier = printerBarrier;
		this.maximumRatings = maximumRatings;
	}

	@Override
	public void run() {
		while (!printerBarrier.await(printTime * 1000)) {
			System.out.println(matchedFilms.get() + "/" + totalFilms.get());
		}
		for (Integer decade : maximumRatings.keySet()) {
			System.out.println((decade * 10) + "-" + (decade * 10 + 9) + ":");
			Map<String, Film> genres = maximumRatings.get(decade);
			for (String genre : genres.keySet()) {
				System.out.println("\t" + genre + ": " + genres.get(genre).primaryTitle);
			}
		}
	}
}
