package rs.ac.bg.etf.pia.fica2022.entities;

public class Automobil {
    private String marka;
    private int cena;
    private int id;

    public String getMarka() {
        return marka;
    }

    public void setMarka(String marka) {
        this.marka = marka;
    }

    public int getCena() {
        return cena;
    }

    public void setCena(int cena) {
        this.cena = cena;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }
    
    @Override
    public String toString() {
        return marka;
    }
    
}
