package kdpl12022;

public interface AtomicBroadcastBuffer<T> {
	public void put(T data);
	public T get(int id);
}
