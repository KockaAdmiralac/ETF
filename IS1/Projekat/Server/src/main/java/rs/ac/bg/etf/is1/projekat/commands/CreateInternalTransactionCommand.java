package rs.ac.bg.etf.is1.projekat.commands;

public class CreateInternalTransactionCommand extends CreateTransactionCommand {
    public CreateInternalTransactionCommand(int amount, int accountIdFrom, int accountIdTo, String purpose) {
        super(amount, accountIdFrom, accountIdTo, purpose);
    }
    @Override
    public String getTransactionType() {
        return "internal";
    }
}
