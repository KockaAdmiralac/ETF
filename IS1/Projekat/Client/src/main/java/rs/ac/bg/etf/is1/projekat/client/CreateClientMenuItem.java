package rs.ac.bg.etf.is1.projekat.client;

import java.util.Scanner;
import retrofit2.Call;
import rs.ac.bg.etf.is1.projekat.client.rest.Service;

public class CreateClientMenuItem extends MenuItem {
    @Override
    public String name() {
        return "Create client";
    }
    @Override
    public Call<?> execute(Scanner scanner, Service service) {
        String name = readString(scanner, "Name");
        String address = readString(scanner, "Address");
        int placeId = readInt(scanner, "Place ID");
        return service.createClient(name, address, placeId);
    }
}
