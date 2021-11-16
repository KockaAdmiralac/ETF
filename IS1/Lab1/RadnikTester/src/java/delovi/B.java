package delovi;

import java.io.Serializable;

public class B implements Serializable {
    private final int id;
    public B(int id) {
        this.id = id;
    }
    @Override
    public String toString() {
        return "B[" + id + "]";
    }
}
