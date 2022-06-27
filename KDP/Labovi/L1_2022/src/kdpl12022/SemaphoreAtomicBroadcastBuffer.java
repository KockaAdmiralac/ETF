package kdpl12022;

import java.util.concurrent.Semaphore;

public class SemaphoreAtomicBroadcastBuffer<T> implements AtomicBroadcastBuffer<T> {
	private final int capacity;
	private final int consumers;
	private final Semaphore[] itemMutex;
	private final Semaphore[] consumerSems;
	private final Semaphore producerSem;
	// Protected by itemMutex.
	private final T[] buffer;
	private int consumerCount[];
	// Used by only one thread.
	private int producerProgress = 0;
	private int consumerProgress[];
	
	@SuppressWarnings("unchecked")
	public SemaphoreAtomicBroadcastBuffer(int capacity, int consumers) {
		this.capacity = capacity;
		this.consumers = consumers;
		producerSem = new Semaphore(capacity);
		itemMutex = new Semaphore[capacity];
		for (int i = 0; i < capacity; ++i) {
			itemMutex[i] = new Semaphore(1);
		}
		consumerSems = new Semaphore[consumers];
		for (int i = 0; i < consumers; ++i) {
			consumerSems[i] = new Semaphore(0);
		}
		consumerProgress = new int[consumers];
		consumerCount = new int[capacity];
		buffer = (T[]) new Object[capacity];
	}
	
	@Override
	public void put(T data) {
		producerSem.acquireUninterruptibly();
		buffer[producerProgress] = data;
		consumerCount[producerProgress] = consumers;
		producerProgress = (producerProgress + 1) % capacity;
		for (int i = 0; i < consumers; ++i) {
			consumerSems[i].release();
		}
	}

	@Override
	public T get(int id) {
		consumerSems[id].acquireUninterruptibly();
		int currentElement = consumerProgress[id];
		consumerProgress[id] = (consumerProgress[id] + 1) % capacity;
		itemMutex[currentElement].acquireUninterruptibly();
		T item = buffer[currentElement];
		int currentConsumerCount = --consumerCount[currentElement];
		itemMutex[currentElement].release();
		if (currentConsumerCount == 0) {
			producerSem.release();
		}
		return item;
	}

}
