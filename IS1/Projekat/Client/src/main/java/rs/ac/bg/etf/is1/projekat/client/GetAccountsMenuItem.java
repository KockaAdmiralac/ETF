package rs.ac.bg.etf.is1.projekat.client;

import java.util.Scanner;
import retrofit2.Call;
import rs.ac.bg.etf.is1.projekat.client.rest.Service;

public class GetAccountsMenuItem extends MenuItem {
    @Override
    public String name() {
        return "Get client's accounts";
    }
    @Override
    public Call<?> execute(Scanner scanner, Service service) {
        int clientId = readInt(scanner, "Client ID");
        return service.accounts(clientId);
    }
}
