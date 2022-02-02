package rs.ac.bg.etf.is1.projekat.client;

import java.util.Scanner;
import retrofit2.Call;
import rs.ac.bg.etf.is1.projekat.client.rest.Service;

public class CreateTransactionMenuItem extends MenuItem {
    private final String type;
    public CreateTransactionMenuItem(String type) {
        this.type = type;
    }
    @Override
    public String name() {
        return "Create " + type + " transaction";
    }
    @Override
    public Call<?> execute(Scanner scanner, Service service) {
        int amount = readInt(scanner, "Amount");
        int accountId = readInt(scanner, "Account ID");
        String purpose = readString(scanner, "Purpose");
        int officeId = 0;
        int accountIdTo = 0;
        if (type.equals("internal")) {
            accountIdTo = readInt(scanner, "Account ID to");
        } else {
            officeId = readInt(scanner, "Office ID");
        }
        switch (type) {
            case "internal":
                return service.createInternalTransaction(amount, accountId, purpose, accountIdTo);
            case "incoming":
                return service.createIncomingTransaction(amount, accountId, purpose, officeId);
            case "outgoing":
                return service.createOutgoingTransaction(amount, accountId, purpose, officeId);
        }
        return null;
    }
}
