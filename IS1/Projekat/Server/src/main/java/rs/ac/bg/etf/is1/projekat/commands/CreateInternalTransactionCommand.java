package rs.ac.bg.etf.is1.projekat.commands;

public class CreateInternalTransactionCommand extends CreateTransactionCommand {
    public CreateInternalTransactionCommand(int amount, int accountId, String purpose) {
        super(amount, accountId, purpose);
    }
    @Override
    public String getTransactionType() {
        return "internal";
    }
}
