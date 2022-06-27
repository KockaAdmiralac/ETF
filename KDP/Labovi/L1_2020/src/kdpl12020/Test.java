package kdpl12020;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ConcurrentMap;

public class Test {
	private static final int BUFFER_LENGTH = 10000;

	public static void main(String[] args) {
		final int consumersNumber = args.length == 0 ? 5 : Integer.parseInt(args[0]);
		final int K = args.length < 2 ? 1000 : Integer.parseInt(args[1]);
		final String fileName = args.length < 3 ? "title.crew.tsv" : args[3];
		final long M = args.length < 4 ? 5 : Long.parseLong(args[4]);
		long startTime = System.currentTimeMillis();

		// Buffer for lines in the TSV file.
		BoundedBuffer<String> lines = new LockBoundedBuffer<>(BUFFER_LENGTH);
		// Barrier for consumers to wait on.
		Barrier consumerBarrier = new SemaphoreBarrier(consumersNumber);
		// Map of how are consumers progressing.
		ConcurrentMap<Integer, Integer> progress = new ConcurrentHashMap<>();
		// List of consumer result counts.
		BoundedBuffer<Result> results = new LockBoundedBuffer<>(consumersNumber + 1);
		// Map of whether consumers were selected for sending.
		ConcurrentMap<Integer, Boolean> selected = new ConcurrentHashMap<>();
		// Barrier for consumers to wait on for the combiner to select them.
		Barrier selectedBarrier = new SemaphoreBarrier(1);
		// Barrier for the printer to wait on for the combiner to finish.
		Barrier printerBarrier = new SemaphoreBarrier(1);
		// Receiving list of films at the combiner.
		BoundedBuffer<Film> sending = new LockBoundedBuffer<>(BUFFER_LENGTH);
		// Final received list of films for printing.
		List<Film> finalData = new ArrayList<>();

		Producer producer = new Producer(fileName, lines);
		producer.start();

		for (int i = 0; i < consumersNumber; i++) {
			Consumer consumer = new Consumer(i, K, lines, progress, results, consumerBarrier, selected, selectedBarrier,
					sending);
			consumer.start();
		}

		Combiner combiner = new Combiner(consumerBarrier, results, selected, selectedBarrier, sending, finalData,
				printerBarrier);
		combiner.start();

		Printer printer = new Printer(M, progress, printerBarrier, finalData);
		printer.start();

		try {
			printer.join();
		} catch (Exception e) {
			e.printStackTrace();
		}
		long endTime = System.currentTimeMillis();
		System.out.println("Total time: " + (endTime - startTime) + "ms");
	}
}
