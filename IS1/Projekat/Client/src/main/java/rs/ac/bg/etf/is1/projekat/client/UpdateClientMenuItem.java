package rs.ac.bg.etf.is1.projekat.client;

import java.util.Scanner;
import retrofit2.Call;
import rs.ac.bg.etf.is1.projekat.client.rest.Service;

public class UpdateClientMenuItem extends MenuItem {
    @Override
    public String name() {
        return "Change client's residence";
    }
    @Override
    public Call<?> execute(Scanner scanner, Service service) {
        int clientId = readInt(scanner, "Client ID");
        int placeId = readInt(scanner, "Place ID");
        return service.updateClient(clientId, placeId);
    }
}
