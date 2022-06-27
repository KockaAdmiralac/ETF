package kdpl12022;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class Producer extends Thread {
	private final BoundedBuffer<String> lines;
	private final AtomicBroadcastBuffer<Rating> ratings;
	private final Barrier consumersBarrier;

	public Producer(BoundedBuffer<String> lines, AtomicBroadcastBuffer<Rating> ratings, Barrier consumersBarrier) {
		super("Producer");
		this.lines = lines;
		this.ratings = ratings;
		this.consumersBarrier = consumersBarrier;
	}

	@Override
	public void run() {
		try (BufferedReader reader = new BufferedReader(new FileReader("title.basics_300000.tsv"))) {
			// Skip first line (header).
			String line = reader.readLine();
			while ((line = reader.readLine()) != null) {
				lines.put(line);
			}
			// Tell consumers the queue is empty.
			lines.put(null);
		} catch (IOException ex) {
			ex.printStackTrace();
		}
		consumersBarrier.await(0);
		try (BufferedReader reader = new BufferedReader(new FileReader("title.ratings_300000.tsv"))) {
			// Skip first line (header).
			String line = reader.readLine();
			while ((line = reader.readLine()) != null) {
				ratings.put(new Rating(line));
			}
			// Tell consumers the queue is empty.
			ratings.put(null);
		} catch (IOException ex) {
			ex.printStackTrace();
		}
	}
}
