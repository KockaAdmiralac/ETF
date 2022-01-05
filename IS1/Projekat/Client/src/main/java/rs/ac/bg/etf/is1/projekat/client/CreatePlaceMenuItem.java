package rs.ac.bg.etf.is1.projekat.client;

import java.util.Scanner;
import retrofit2.Call;
import rs.ac.bg.etf.is1.projekat.client.rest.Service;

public class CreatePlaceMenuItem extends MenuItem {
    @Override
    public String name() {
        return "Create place";
    }
    @Override
    public Call<?> execute(Scanner scanner, Service service) {
        int postalCode = readInt(scanner, "Postal code");
        String name = readString(scanner, "Name");
        return service.createPlace(postalCode, name);
    }
}
