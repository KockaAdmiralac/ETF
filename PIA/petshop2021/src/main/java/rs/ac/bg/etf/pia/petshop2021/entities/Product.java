package rs.ac.bg.etf.pia.petshop2021.entities;

public class Product {
    private String naziv;
    private String opis;
    private int cena;
    private boolean promocija;
    private boolean kupiti;
    private int koliko;

    public boolean isKupiti() {
        return kupiti;
    }

    public void setKupiti(boolean kupiti) {
        this.kupiti = kupiti;
    }

    public int getKoliko() {
        return koliko;
    }

    public void setKoliko(int koliko) {
        this.koliko = koliko;
    }

    public String getNaziv() {
        return naziv;
    }

    public void setNaziv(String naziv) {
        this.naziv = naziv;
    }

    public String getOpis() {
        return opis;
    }

    public void setOpis(String opis) {
        this.opis = opis;
    }

    public int getCena() {
        return cena;
    }

    public void setCena(int cena) {
        this.cena = cena;
    }

    public boolean isPromocija() {
        return promocija;
    }

    public void setPromocija(boolean promocija) {
        this.promocija = promocija;
    }
}
