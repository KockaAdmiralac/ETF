package rs.ac.bg.etf.is1.projekat.client;

import java.util.Scanner;
import retrofit2.Call;
import rs.ac.bg.etf.is1.projekat.client.rest.Service;

public class GetPlacesMenuItem extends MenuItem {
    @Override
    public String name() {
        return "Get places";
    }
    @Override
    public Call<?> execute(Scanner scanner, Service service) {
        return service.places();
    }
}
