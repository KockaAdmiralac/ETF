package kdpl12020;

public class Film {
	public final String tconst;
	public final String[] directors;
	public final String[] writers;

	public Film(String line) {
		String[] splitLine = line.split("\t");
		tconst = splitLine[0];
		String directorsCell = splitLine[1];
		String writersCell = splitLine[2];
		directors = directorsCell.equals("\\N") ? new String[0] : directorsCell.split(",");
		writers = writersCell.equals("\\N") ? new String[0] : writersCell.split(",");
	}
}
