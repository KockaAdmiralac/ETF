package rs.ac.bg.etf.is1.projekat.client.rest;

public class Client {
    public int id;
    public String name;
    public String address;
    public int placeId;
    @Override
    public String toString() {
        return "Client:" +
                "\n\tID: " + id +
                "\n\tName: " + name +
                "\n\tAddress: " + address +
                "\n\tPlace ID: " + placeId;
    }
}
