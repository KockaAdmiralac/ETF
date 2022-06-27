package kdpl1;

import java.util.Map;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;

public class Combiner extends Thread {
	private final BlockingQueue<Actor> dataQueue;
	private final Lock printerLock;
	private final Condition printerCondition;
	private final Map<Integer, Integer> finalResult;

	public Combiner(BlockingQueue<Actor> dataQueue, Lock printerLock, Condition printerCondition, Map<Integer, Integer> finalResult) {
		super("Combiner");
		this.dataQueue = dataQueue;
		this.printerLock = printerLock;
		this.printerCondition = printerCondition;
		this.finalResult = finalResult;
	}

	@Override
	public void run() {
		try {
			Actor data;
			while ((data = dataQueue.take()).nconst != null) {
				int decade = data.birthYear / 10;
				Integer currentResult = finalResult.get(decade);
				finalResult.put(decade, currentResult == null ? 1 : currentResult + 1);
			}
			System.out.println("Combiner finished.");
			printerLock.lock();
			printerCondition.signal();
			printerLock.unlock();
		} catch (InterruptedException e) {
			System.out.println("Combiner interrupted, exiting...");
		}
	}

}
