package kdpl12020;

public class MonitorBarrier implements Barrier {
	private final int count;
	private int currentCount = 0;
	boolean passed = false;
	int round = 0;
	public MonitorBarrier(int count) {
		this.count = count;
	}
	@Override
	public synchronized void arrived() {
		int myRound = round;
		if (passed) {
			return;
		}
		if (++currentCount == count) {
			passed = true;
			notifyAll();
		} else {
			while (!passed && round == myRound) {
				try {
					wait();
				} catch (InterruptedException e) {}
			}
		}
	}
	@Override
	public synchronized boolean await(long timeout) {
		int myRound = round;
		if (passed) {
			return true;
		}
		while (!passed && myRound == round) {
			try {
				long timeBefore = System.currentTimeMillis();
				wait(timeout);
				long timeAfter = System.currentTimeMillis();
				if (timeout != 0 && timeAfter - timeBefore >= timeout) {
					break;
				}
			} catch (InterruptedException e) {}
		}
		return currentCount == count;
	}
	@Override
	public synchronized void reset() {
		currentCount = 0;
		passed = false;
		round++;
	}
}
