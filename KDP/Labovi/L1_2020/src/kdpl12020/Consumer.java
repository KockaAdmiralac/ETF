package kdpl12020;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ConcurrentMap;

public class Consumer extends Thread {
	private final int id;
	private final int k;
	private final BoundedBuffer<String> lines;
	private final ConcurrentMap<Integer, Integer> progress;
	private final BoundedBuffer<Result> results;
	private final ConcurrentMap<Integer, Boolean> selected;
	private final Barrier selectedBarrier;
	private final Barrier barrier;
	private final BoundedBuffer<Film> sending;

	public Consumer(int id, int k, BoundedBuffer<String> lines, ConcurrentMap<Integer, Integer> progress,
			BoundedBuffer<Result> results, Barrier barrier, ConcurrentMap<Integer, Boolean> selected,
			Barrier selectedBarrier, BoundedBuffer<Film> sending) {
		super("Consumer" + id);
		this.id = id;
		this.k = k;
		this.lines = lines;
		this.progress = progress;
		this.results = results;
		this.barrier = barrier;
		this.selected = selected;
		this.selectedBarrier = selectedBarrier;
		this.sending = sending;
	}

	@Override
	public void run() {
		String line;
		List<Film> films = new ArrayList<>();
		int maxDirectors = 0;
		int processed = 0;
		while ((line = lines.get()) != null) {
			Film data = new Film(line);
			int directorCount = data.directors.length;
			if (directorCount > maxDirectors) {
				maxDirectors = directorCount;
				films.clear();
			}
			if (directorCount == maxDirectors) {
				films.add(data);
			}
			if (++processed % k == 0) {
				// Update our progress every K processed lines.
				progress.put(id, processed);
			}
		}
		progress.put(id, processed);
		// Signal other consumers we're done.
		lines.put(null);
		// Signal the combiner we're done.
		results.put(new Result(id, maxDirectors));
		barrier.arrived();
		selectedBarrier.await(0);
		if (selected.getOrDefault(id, false)) {
			// Send data to the combiner.
			for (Film film : films) {
				sending.put(film);
			}
			// Signal the combiner sending data is over.
			sending.put(null);
		}
	}

}
