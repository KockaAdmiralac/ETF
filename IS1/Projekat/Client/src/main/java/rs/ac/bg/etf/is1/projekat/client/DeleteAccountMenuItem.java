package rs.ac.bg.etf.is1.projekat.client;

import java.util.Scanner;
import retrofit2.Call;
import rs.ac.bg.etf.is1.projekat.client.rest.Service;

public class DeleteAccountMenuItem extends MenuItem {
    @Override
    public String name() {
        return "Close account";
    }
    @Override
    public Call<?> execute(Scanner scanner, Service service) {
        int accountId = readInt(scanner, "Account ID");
        return service.deleteAccount(accountId);
    }
}
