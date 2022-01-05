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
        int accountIdFrom = readInt(scanner, "Account ID from");
        int accountIdTo = readInt(scanner, "Account ID to");
        String purpose = readString(scanner, "Purpose");
        int officeId = 0;
        if (!type.equals("internal")) {
            officeId = readInt(scanner, "Office ID");
        }
        switch (type) {
            case "internal":
                return service.createInternalTransaction(amount, accountIdFrom, accountIdTo, purpose);
            case "incoming":
                return service.createIncomingTransaction(amount, accountIdFrom, accountIdTo, purpose, officeId);
            case "outgoing":
                return service.createOutgoingTransaction(amount, accountIdFrom, accountIdTo, purpose, officeId);
        }
        return null;
    }
}
