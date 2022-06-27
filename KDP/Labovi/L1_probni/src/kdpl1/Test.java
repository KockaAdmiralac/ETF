package kdpl1;

import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.ConcurrentLinkedQueue;
import java.util.concurrent.CyclicBarrier;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Test {
	
	public static void main(String[] args) {
		int consumersNumber = args.length == 0 ? 5 : Integer.parseInt(args[0]);
		int N = args.length < 2 ? 1000 : Integer.parseInt(args[1]);
		String fileName = args.length < 3 ? "data.tsv" : args[3];
		long interval = args.length < 4 ? 5000 : Long.parseLong(args[4]);

		BlockingQueue<String> bq = new LinkedBlockingQueue<>();
		ConcurrentLinkedQueue<Progress> progressQueue = new ConcurrentLinkedQueue<>();
		BlockingQueue<Actor> dataQueue = new LinkedBlockingQueue<>();
		CyclicBarrier consumerBarrier = new CyclicBarrier(consumersNumber, () -> {
			try {
				System.out.println("All consumers finished.");
				dataQueue.put(new Actor());
			} catch (InterruptedException e) {
				// Interrupted, exiting...
				System.out.println("Interrupted while signalling the combiner.");
			}
		});
		Lock printerLock = new ReentrantLock();
		Condition printerCondition = printerLock.newCondition();
		Map<Integer, Integer> finalResult = new HashMap<>();
		
		Producer producer = new Producer(fileName, bq);
		producer.start();

		for (int i = 0; i < consumersNumber; i++) {
			Consumer consumer = new Consumer(i, N, bq, progressQueue, dataQueue, consumerBarrier);
			consumer.start();
		}

		Combiner combiner = new Combiner(dataQueue, printerLock, printerCondition, finalResult);
		combiner.start();

		Printer printer = new Printer(interval, progressQueue, printerLock, printerCondition, finalResult);
		printer.start();

		try {
			printer.join();
		} catch (Exception e) {
			e.printStackTrace();
		}

	}
}
