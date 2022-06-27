package kdpl1;

import java.util.Map;
import java.util.TreeSet;
import java.util.concurrent.ConcurrentLinkedQueue;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;

public class Printer extends Thread {
	private final long interval;
	private final ConcurrentLinkedQueue<Progress> progressQueue;
	private final Lock printerLock;
	private final Condition printerCondition;
	private final Map<Integer, Integer> finalResult;

    public Printer(long interval, ConcurrentLinkedQueue<Progress> progressQueue, Lock printerLock, Condition printerCondition, Map<Integer, Integer> finalResult) {
	    super("Printer");
	    this.interval = interval;
	    this.progressQueue = progressQueue;
	    this.printerLock = printerLock;
	    this.printerCondition = printerCondition;
	    this.finalResult = finalResult;
    }

    @Override
    public void run() {
		try {
			while (true) {
				printerLock.lock();
				boolean awaitResult = printerCondition.await(interval, TimeUnit.MILLISECONDS);
				printerLock.unlock();
				if (awaitResult) {
					break;
				}
				progressQueue.forEach(p -> System.out.println("Consumer " + p.id + ": " + p.progress.get()));
			}
		} catch (InterruptedException e) {
			System.out.println("Printer interrupted, exiting...");
		}
		System.out.println("Final result:");
		for (Integer decade : new TreeSet<>(finalResult.keySet())) {
			int startYear = decade * 10;
			int endYear = startYear + 9;
			System.out.println(startYear + "-" + endYear + ": " + finalResult.get(decade));
		}
		System.out.println("Printer finished.");
    }

}
