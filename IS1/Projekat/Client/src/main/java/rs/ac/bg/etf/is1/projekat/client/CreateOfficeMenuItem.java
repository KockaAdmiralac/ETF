package rs.ac.bg.etf.is1.projekat.client;

import java.util.Scanner;
import retrofit2.Call;
import rs.ac.bg.etf.is1.projekat.client.rest.Service;

public class CreateOfficeMenuItem extends MenuItem {
    @Override
    public String name() {
        return "Create office";
    }
    @Override
    public Call<?> execute(Scanner scanner, Service service) {
        String name = readString(scanner, "Name");
        String address = readString(scanner, "Address");
        int placeId = readInt(scanner, "Place ID");
        return service.createOffice(name, address, placeId);
    }
}
