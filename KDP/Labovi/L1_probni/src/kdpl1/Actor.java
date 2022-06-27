package kdpl1;

public class Actor {
	public final String nconst;
	public final String primaryName;
	public int birthYear;
	public int deathYear;
	public final String[] primaryProfession;
	public final String[] knownForTitles;
	
	public Actor() {
		nconst = null;
		primaryName = null;
		birthYear = -1;
		deathYear = -1;
		primaryProfession = new String[0];
		knownForTitles = new String[0];
	}
	
	public Actor(String row) {
		String[] splitRow = row.split("\t");
		nconst = splitRow[0];
		primaryName = splitRow[1];
		try {
			birthYear = splitRow[2].equals("\\N") ? -1 : Integer.parseInt(splitRow[2]);
		} catch (NumberFormatException ex) {
			System.err.println(splitRow[2]);
			birthYear = -1;
		}
		try {
			deathYear = splitRow[3].equals("\\N") ? -1 : Integer.parseInt(splitRow[3]);
		} catch (NumberFormatException ex) {
			System.err.println(splitRow[3]);
			deathYear = -1;
		}
		primaryProfession = splitRow[4].split(",");
		knownForTitles = splitRow[5].split(",");
	}
}
