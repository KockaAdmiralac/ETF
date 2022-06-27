package kdpl12020;

public interface BoundedBuffer<T> {
	public void put(T data);
	public T get();
}
