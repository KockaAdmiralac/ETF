package kdpl12022;

import java.util.Map;
import java.util.TreeMap;
import java.util.concurrent.atomic.AtomicInteger;

public class Test {
	private static final int BUFFER_LENGTH = 10000;

	public static void main(String[] args) {
		final int consumersNumber = args.length == 0 ? 5 : Integer.parseInt(args[0]);
		final long M = args.length < 4 ? 5 : Long.parseLong(args[4]);
		long startTime = System.currentTimeMillis();

		// Buffer for film file lines.
		BoundedBuffer<String> lines = new MonitorBoundedBuffer<>(BUFFER_LENGTH);
		// Buffer for ratings file lines.
		AtomicBroadcastBuffer<Rating> ratings = new MonitorAtomicBroadcastBuffer<>(BUFFER_LENGTH, consumersNumber);
		// Barrier used to tell the producers that consumers have finished reading
		// films.
		Barrier consumersBarrier = new MonitorBarrier(consumersNumber);
		// Barrier used to tell the combiner that consumers have finished sending films.
		Barrier combinerBarrier = new MonitorBarrier(consumersNumber);
		// Variables for updating the amount of processed films.
		AtomicInteger totalFilms = new AtomicInteger();
		AtomicInteger matchedFilms = new AtomicInteger();
		// Buffer for local maximum maps that consumers are sending to the combiner.
		BoundedBuffer<Map<Integer, Map<String, Film>>> localFilms = new MonitorBoundedBuffer<>(consumersNumber + 1);
		// Barrier for the printer to wait for the combiner to finish.
		Barrier printerBarrier = new MonitorBarrier(1);
		// Combiner maximum rated films.
		Map<Integer, Map<String, Film>> maximumRatings = new TreeMap<>();

		Producer producer = new Producer(lines, ratings, consumersBarrier);
		producer.start();

		for (int i = 0; i < consumersNumber; ++i) {
			Consumer consumer = new Consumer(i, lines, ratings, consumersBarrier, totalFilms, matchedFilms, localFilms,
					combinerBarrier);
			consumer.start();
		}

		Combiner combiner = new Combiner(localFilms, combinerBarrier, maximumRatings, printerBarrier);
		combiner.start();

		Printer printer = new Printer(M, totalFilms, matchedFilms, printerBarrier, maximumRatings);
		printer.start();

		try {
			printer.join();
		} catch (InterruptedException ex) {
			ex.printStackTrace();
		}

		long endTime = System.currentTimeMillis();
		System.out.println("Total time: " + (endTime - startTime) + "ms");
	}
}
