package kdpl12020;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class Producer extends Thread {
	private final String fileName;
	private final BoundedBuffer<String> lines;

	public Producer(String fileName, BoundedBuffer<String> lines) {
		super("Producer");
		this.fileName = fileName;
		this.lines = lines;
	}

	@Override
	public void run() {
		try (BufferedReader reader = new BufferedReader(new FileReader(fileName))) {
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
	}

}
