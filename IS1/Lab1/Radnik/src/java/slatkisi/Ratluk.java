package slatkisi;

import java.io.Serializable;

public class Ratluk implements Serializable {
    private final int id;
    public Ratluk(int id) {
        this.id = id;
    }
    @Override
    public String toString() {
        return "RATLUK[" + id + "]";
    }
}
