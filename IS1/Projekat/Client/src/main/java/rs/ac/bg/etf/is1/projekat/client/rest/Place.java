package rs.ac.bg.etf.is1.projekat.client.rest;

public class Place {
    public int id;
    public int postalCode;
    public String name;
    @Override
    public String toString() {
        return "Place:" +
                "\n\tID: " + id +
                "\n\tPostal code: " + postalCode +
                "\n\tName: " + name;
    }
}
