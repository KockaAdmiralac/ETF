package rs.ac.bg.etf.is1.projekat.client.rest;

public class Office {
    public int id;
    public String name;
    public String address;
    public Place place;
    @Override
    public String toString() {
        return "Office:" +
                "\n\tID: " + id +
                "\n\tName: " + name +
                "\n\tAddress: " + address +
                "\n\tPlace: " + place;
    }
}
