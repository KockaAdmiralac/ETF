package slatkisi;

import java.io.Serializable;

public class Cokoladica implements Serializable {
    private final int id;
    public Cokoladica(int id) {
        this.id = id;
    }
    @Override
    public String toString() {
        return "COKOLADICA[" + id + "]";
    }
}
