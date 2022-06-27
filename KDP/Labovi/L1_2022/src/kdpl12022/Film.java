package kdpl12022;

public class Film {
	public final String tconst;
	public final String titleType;
	public final String primaryTitle;
	public final String originalTitle;
	public final boolean isAdult;
	public final int startYear;
	public final int endYear;
	public final int runtimeMinutes;
	public final String[] genres;
	public Rating rating;
	public Film(String row) {
		String[] splitRow = row.split("\t");
		tconst = splitRow[0];
		titleType = splitRow[1];
		primaryTitle = splitRow[2];
		originalTitle = splitRow[3];
		isAdult = splitRow[4].equals("1");
		startYear = splitRow[5].equals("\\N") ? -1 : Integer.parseInt(splitRow[5]);
		endYear = splitRow[6].equals("\\N") ? -1 : Integer.parseInt(splitRow[6]);
		runtimeMinutes = splitRow[7].equals("\\N") ? -1 : Integer.parseInt(splitRow[7]);
		genres = splitRow[8].equals("\\N") ? new String[0] : splitRow[8].split(",");
	}
}
