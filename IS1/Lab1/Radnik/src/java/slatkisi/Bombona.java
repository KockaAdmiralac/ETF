package slatkisi;

import java.io.Serializable;

public class Bombona implements Serializable {
    private final int id;
    public Bombona(int id) {
        this.id = id;
    }
    @Override
    public String toString() {
        return "BOMBONA[" + id + "]";
    }
}
