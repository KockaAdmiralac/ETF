package kdpl12022;

public class MonitorAtomicBroadcastBuffer<T> implements AtomicBroadcastBuffer<T> {
	private final int capacity;
	private final int consumers;
	private final T[] buffer;
	private final int[] numOfConsumers;
	private int writeIndex;
	private final int[] readIndex;
	private final int[] canConsume;

	@SuppressWarnings("unchecked")
	public MonitorAtomicBroadcastBuffer(int capacity, int consumers) {
		this.capacity = capacity;
		this.consumers = consumers;
		this.buffer = (T[]) new Object[capacity];
		this.numOfConsumers = new int[capacity];
		this.readIndex = new int[consumers];
		this.canConsume = new int[consumers];
	}

	@Override
	public synchronized void put(T data) {
		while (numOfConsumers[writeIndex] != 0) {
			try {
				wait();
			} catch (InterruptedException e) {
			}
		}
		buffer[writeIndex] = data;
		numOfConsumers[writeIndex] = consumers;
		writeIndex = (writeIndex + 1) % capacity;
		for (int i = 0; i < consumers; ++i) {
			++canConsume[i];
		}
		notifyAll();
	}

	@Override
	public synchronized T get(int id) {
		while (canConsume[id] == 0) {
			try {
				wait();
			} catch (InterruptedException e) {
			}
		}
		T data = buffer[readIndex[id]];
		--canConsume[id];
		if (--numOfConsumers[readIndex[id]] == 0) {
			notifyAll();
		}
		readIndex[id] = (readIndex[id] + 1) % capacity;
		return data;
	}

}
