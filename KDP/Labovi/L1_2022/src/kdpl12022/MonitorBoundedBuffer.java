package kdpl12022;

import java.util.ArrayList;
import java.util.List;

public class MonitorBoundedBuffer<T> implements BoundedBuffer<T> {
	private final int capacity;
	private final List<T> buffer;

	public MonitorBoundedBuffer(int capacity) {
		this.capacity = capacity;
		buffer = new ArrayList<T>(capacity);
	}

	@Override
	public synchronized void put(T data) {
		while (buffer.size() == capacity) {
			try {
				wait();
			} catch (InterruptedException ex) {
				// Ignoring all interrupts.
			}
		}
		buffer.add(data);
		notifyAll();
	}

	@Override
	public synchronized T get() {
		while (buffer.size() == 0) {
			try {
				wait();
			} catch (InterruptedException ex) {
				// Ignoring all interrupts.
			}
		}
		T data = buffer.remove(0);
		notifyAll();
		return data;
	}
}
