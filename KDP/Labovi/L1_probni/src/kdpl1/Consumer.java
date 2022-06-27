package kdpl1;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.ConcurrentLinkedQueue;
import java.util.concurrent.CyclicBarrier;

public class Consumer extends Thread {
	private final int id;
	private final int n;
	private final BlockingQueue<String> queue;
	private final List<Actor> processedData;
	private final ConcurrentLinkedQueue<Progress> progressQueue;
	private final BlockingQueue<Actor> dataQueue;
	private final CyclicBarrier consumerBarrier;
	
    public Consumer(int id, int n, BlockingQueue<String> queue, ConcurrentLinkedQueue<Progress> progressQueue, BlockingQueue<Actor> dataQueue, CyclicBarrier consumerBarrier) {
	    super("Consumer" + id);
	    this.id = id;
	    this.n = n;
	    this.queue = queue;
	    processedData = new ArrayList<>(n);
	    this.progressQueue = progressQueue;
	    this.dataQueue = dataQueue;
	    this.consumerBarrier = consumerBarrier;
    }

    @Override
    public void run() {
    	String line;
    	try {
    		Progress ourProgress = new Progress(id, 0);
    		progressQueue.add(ourProgress);
			while (!(line = queue.take()).equals("")) {
				Actor data = parseLine(line);
				if (data.birthYear == -1) {
					// Invalid data.
					continue;
				}
				if (data.deathYear != -1) {
					// Actor is dead.
					continue;
				}
				boolean isActor = false;
				for (String profession : data.primaryProfession) {
					if (profession.equals("actor") || profession.equals("actress")) {
						isActor = true;
						break;
					}
				}
				if (!isActor) {
					// Not an actor.
					continue;
				}
				processedData.add(data);
				if (processedData.size() == n) {
					ourProgress.progress.addAndGet(n);
					dataQueue.addAll(processedData);
					processedData.clear();
				}
			}
			ourProgress.progress.addAndGet(processedData.size());
			dataQueue.addAll(processedData);
			// Tell the next consumer there is nothing to consume further.
			queue.put("");
			consumerBarrier.await();
		} catch (InterruptedException | BrokenBarrierException e) {
			// We were interrupted, finish the thread.
			System.out.println("Consumer " + id + " stopping...");
		}
    }

    private static Actor parseLine(String line) {
    	return new Actor(line);
    }

}
