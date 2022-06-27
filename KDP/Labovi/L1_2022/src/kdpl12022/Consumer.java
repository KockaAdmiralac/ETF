package kdpl12022;

import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.atomic.AtomicInteger;

public class Consumer extends Thread {
	private final int id;
	private final BoundedBuffer<String> lines;
	private final AtomicBroadcastBuffer<Rating> ratings;
	private final Barrier consumersBarrier;
	private final AtomicInteger totalFilms;
	private final AtomicInteger matchedFilms;
	private final BoundedBuffer<Map<Integer, Map<String, Film>>> localFilms;
	private final Barrier combinerBarrier;

	public Consumer(int id, BoundedBuffer<String> lines, AtomicBroadcastBuffer<Rating> ratings,
			Barrier consumersBarrier, AtomicInteger totalFilms, AtomicInteger matchedFilms,
			BoundedBuffer<Map<Integer, Map<String, Film>>> localFilms, Barrier combinerBarrier) {
		super("Consumer");
		this.id = id;
		this.lines = lines;
		this.ratings = ratings;
		this.consumersBarrier = consumersBarrier;
		this.totalFilms = totalFilms;
		this.matchedFilms = matchedFilms;
		this.localFilms = localFilms;
		this.combinerBarrier = combinerBarrier;
	}

	@Override
	public void run() {
		String line;
		Map<String, Film> films = new HashMap<>();
		Map<Integer, Map<String, Film>> maximumRatings = new HashMap<>();
		while ((line = lines.get()) != null) {
			Film film = new Film(line);
			if (film.startYear == -1) {
				continue;
			}
			films.put(film.tconst, film);
			totalFilms.incrementAndGet();
		}
		// Tell other consumers there is nothing to consume.
		lines.put(null);
		consumersBarrier.arrived();
		Rating rating;
		while ((rating = ratings.get(id)) != null) {
			Film film = films.get(rating.tconst);
			if (film != null) {
				film.rating = rating;
				int decade = film.startYear / 10;
				Map<String, Film> genreMap = maximumRatings.get(decade);
				if (genreMap == null) {
					genreMap = new HashMap<>();
					maximumRatings.put(decade, genreMap);
				}
				for (String genre : film.genres) {
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
			matchedFilms.incrementAndGet();
		}
		localFilms.put(maximumRatings);
		combinerBarrier.arrived();
	}
}
