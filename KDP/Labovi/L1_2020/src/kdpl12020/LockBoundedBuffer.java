package kdpl12020;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class LockBoundedBuffer<T> implements BoundedBuffer<T> {
	private final int capacity;
	private final List<T> buffer;
	private final Lock lock = new ReentrantLock();
	private final Condition space = lock.newCondition();
	private final Condition items = lock.newCondition();
	private int count = 0;
	
	public LockBoundedBuffer(int capacity) {
		this.capacity = capacity;
		buffer = new ArrayList<>(capacity);
	}

	@Override
	public void put(T data) {
		lock.lock();
		while (count == capacity) {
			space.awaitUninterruptibly();
		}
		++count;
		buffer.add(data);
		items.signal();
		lock.unlock();
	}

	@Override
	public T get() {
		lock.lock();
		while (count == 0) {
			items.awaitUninterruptibly();
		}
		--count;
		T data = buffer.remove(0);
		space.signal();
		lock.unlock();
		return data;
	}
}
