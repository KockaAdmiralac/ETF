package rs.ac.bg.etf.is1.projekat.client;

import java.util.Scanner;
import retrofit2.Call;
import rs.ac.bg.etf.is1.projekat.client.rest.Service;

public class CreateAccountMenuItem extends MenuItem {
    @Override
    public String name() {
        return "Create account";
    }
    @Override
    public Call<?> execute(Scanner scanner, Service service) {
        int clientId = readInt(scanner, "Client ID");
        int placeId = readInt(scanner, "Place ID");
        int overdraft = readInt(scanner, "Overdraft");
        return service.createAccount(clientId, placeId, overdraft);
    }
}
