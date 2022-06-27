package kdpl12022;

import java.util.Map;
import java.util.TreeMap;

public class Combiner extends Thread {
	private final BoundedBuffer<Map<Integer, Map<String, Film>>> localFilms;
	private final Barrier combinerBarrier;
	private final Barrier printerBarrier;
	private final Map<Integer, Map<String, Film>> maximumRatings;

	public Combiner(BoundedBuffer<Map<Integer, Map<String, Film>>> localFilms, Barrier combinerBarrier,
			Map<Integer, Map<String, Film>> maximumRatings, Barrier printerBarrier) {
		super("Combiner");
		this.localFilms = localFilms;
		this.combinerBarrier = combinerBarrier;
		this.maximumRatings = maximumRatings;
		this.printerBarrier = printerBarrier;
	}

	@Override
	public void run() {
		combinerBarrier.await(0);
		localFilms.put(null);
		Map<Integer, Map<String, Film>> films;
		while ((films = localFilms.get()) != null) {
			for (int decade : films.keySet()) {
				Map<String, Film> genreMap = maximumRatings.get(decade);
				if (genreMap == null) {
					genreMap = new TreeMap<>();
					maximumRatings.put(decade, genreMap);
				}
				for (String genre : films.get(decade).keySet()) {
					Film film = films.get(decade).get(genre);
					Film currentGenreMaximum = genreMap.get(genre);
					if (currentGenreMaximum == null) {
						genreMap.put(genre, film);
					} else {
						if (film.rating.averageRating > currentGenreMaximum.rating.averageRating) {
							genreMap.put(genre, film);
						}
					}
				}
			}
		}
		printerBarrier.arrived();
	}
}
