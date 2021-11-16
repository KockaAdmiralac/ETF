package delovi;

import java.io.Serializable;

public class C implements Serializable {
    private final int id;
    public C(int id) {
        this.id = id;
    }
    @Override
    public String toString() {
        return "C[" + id + "]";
    }
}
