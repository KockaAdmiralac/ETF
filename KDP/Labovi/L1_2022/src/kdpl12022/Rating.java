package kdpl12022;

public class Rating {
	public final String tconst;
	public final double averageRating;
	public final int numVotes;
	public Rating(String row) {
		String[] splitRow = row.split("\t");
		tconst = splitRow[0];
		averageRating = Double.parseDouble(splitRow[1]);
		numVotes = Integer.parseInt(splitRow[2]);
	}
}
