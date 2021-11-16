package automobil;

import delovi.*;
import java.io.Serializable;

public class Automobil implements Serializable {
    private final A a;
    private final B b;
    private final C c;
    
    public Automobil(A a, B b, C c) {
        this.a = a;
        this.b = b;
        this.c = c;
    }
    
    @Override
    public String toString() {
        return "Automobil[" + a + ", " + b + "," + c + "]";
    }
}
