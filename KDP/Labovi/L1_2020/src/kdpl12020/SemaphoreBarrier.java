package kdpl12020;

import java.util.concurrent.Semaphore;
import java.util.concurrent.TimeUnit;

public class SemaphoreBarrier implements Barrier {
	private final Semaphore sem1 = new Semaphore(1);
	private final Semaphore sem2 = new Semaphore(0);
	private final Semaphore awaiter = new Semaphore(0);
	private final Semaphore mutex = new Semaphore(1);
	private final int count;
	// Protected by sem1 and sem2.
	private int currentCount = 0;
	// Protected by mutex.
	private int awaiting = 0;
	private boolean passed = false;

	public SemaphoreBarrier(int count) {
		this.count = count;
	}
	
	@Override
	public void arrived() {
		sem1.acquireUninterruptibly();
		++currentCount;
		if (currentCount == count) {
			sem2.release();
			mutex.acquireUninterruptibly();
			awaiter.release(awaiting);
			passed = true;
			mutex.release();
		} else {
			sem1.release();
		}
		sem2.acquireUninterruptibly();
		--currentCount;
		if (currentCount == 0) {
			sem1.release();
		} else {
			sem2.release();
		}
	}

	@Override
	public boolean await(long timeout) {
		boolean acquired;
		mutex.acquireUninterruptibly();
		if (passed) {
			mutex.release();
			return true;
		}
		++awaiting;
		mutex.release();
		try {
			if (timeout == 0) {
				awaiter.acquireUninterruptibly();
				acquired = true;
			} else {
				acquired = awaiter.tryAcquire(timeout, TimeUnit.MILLISECONDS);
			}
		} catch (InterruptedException e) {
			return false;
		}
		mutex.acquireUninterruptibly();
		--awaiting;
		mutex.release();
		return acquired;
	}

	@Override
	public void reset() {
		passed = false;
	}

}
