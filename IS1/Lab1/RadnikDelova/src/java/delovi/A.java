package delovi;

import java.io.Serializable;

public class A implements Serializable {
    private final int id;
    public A(int id) {
        this.id = id;
    }
    @Override
    public String toString() {
        return "A[" + id + "]";
    }
}
