package kdpl1;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.concurrent.BlockingQueue;

public class Producer extends Thread {
	private final String fileName;
	private final BlockingQueue<String> queue;
	
    public Producer(String fileName, BlockingQueue<String> queue) {
	    super("Producer");
	    this.fileName = fileName;
	    this.queue = queue;
    }

    @Override
    public void run() {
    	try (BufferedReader reader = new BufferedReader(new FileReader(fileName))) {
    		// Skip first line (header).
    		String line = reader.readLine();
    		while ((line = reader.readLine()) != null) {
    			queue.put(line);
    		}
    		// Tell consumers the queue is empty.
    		queue.put("");
    	} catch (FileNotFoundException ex) {
    		System.err.println("Specified input file not found!");
    	} catch (InterruptedException ex) {
    		// We were probably interrupted intentionally, stop the thread.
    		System.out.println("Producer stopping...");
    	} catch (IOException ex) {
    		ex.printStackTrace();
    	}
    }

}
