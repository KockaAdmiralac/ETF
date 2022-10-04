package rs.ac.bg.etf.pia.petshop2021.entities;

import java.time.LocalDate;
import java.util.List;

public class Order {
    private String kupac;
    private LocalDate datumNarudzbine;
    private String proizvodi;

    public String getKupac() {
        return kupac;
    }

    public void setKupac(String kupac) {
        this.kupac = kupac;
    }

    public LocalDate getDatumNarudzbine() {
        return datumNarudzbine;
    }

    public void setDatumNarudzbine(LocalDate datumNarudzbine) {
        this.datumNarudzbine = datumNarudzbine;
    }

    public String getProizvodi() {
        return proizvodi;
    }

    public void setProizvodi(String proizvodi) {
        this.proizvodi = proizvodi;
    }
}
