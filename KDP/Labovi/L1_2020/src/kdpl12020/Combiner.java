package kdpl12020;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ConcurrentMap;

public class Combiner extends Thread {
	private final Barrier consumerBarrier;
	private final BoundedBuffer<Result> results;
	private final ConcurrentMap<Integer, Boolean> selected;
	private final Barrier selectedBarrier;
	private final BoundedBuffer<Film> sending;
	private final List<Film> finalData;
	private final Barrier printerBarrier;

	public Combiner(Barrier consumerBarrier, BoundedBuffer<Result> results, ConcurrentMap<Integer, Boolean> selected,
			Barrier selectedBarrier, BoundedBuffer<Film> sending, List<Film> finalData, Barrier printerBarrier) {
		super("Combiner");
		this.consumerBarrier = consumerBarrier;
		this.results = results;
		this.selected = selected;
		this.selectedBarrier = selectedBarrier;
		this.sending = sending;
		this.finalData = finalData;
		this.printerBarrier = printerBarrier;
	}

	@Override
	public void run() {
		int maxDirectors = 0;
		List<Integer> maxId = new ArrayList<>();
		Result result;
		consumerBarrier.await(0);
		results.put(null);
		while ((result = results.get()) != null) {
			if (result.maxDirectors > maxDirectors) {
				maxDirectors = result.maxDirectors;
				maxId.clear();
			}
			if (result.maxDirectors == maxDirectors) {
				maxId.add(result.id);
			}
		}
		int senders = maxId.size();
		for (int id : maxId) {
			selected.put(id, true);
		}
		selectedBarrier.arrived();
		while (true) {
			Film data = sending.get();
			if (data == null) {
				if (--senders == 0) {
					break;
				}
			} else {
				finalData.add(data);
			}
		}
		printerBarrier.arrived();
	}

}
