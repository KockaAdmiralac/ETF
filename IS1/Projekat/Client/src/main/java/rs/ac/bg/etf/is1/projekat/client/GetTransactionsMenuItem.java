package rs.ac.bg.etf.is1.projekat.client;

import java.util.Scanner;
import retrofit2.Call;
import rs.ac.bg.etf.is1.projekat.client.rest.Service;

public class GetTransactionsMenuItem extends MenuItem {
    @Override
    public String name() {
        return "Get transactions for account";
    }
    @Override
    public Call<?> execute(Scanner scanner, Service service) {
        int accountId = readInt(scanner, "Account ID");
        return service.transactions(accountId);
    }
}
