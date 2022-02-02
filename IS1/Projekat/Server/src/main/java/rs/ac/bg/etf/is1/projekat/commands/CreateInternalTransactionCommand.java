package rs.ac.bg.etf.is1.projekat.commands;

public class CreateInternalTransactionCommand extends CreateTransactionCommand {
    private final int accountIdTo;
    public CreateInternalTransactionCommand(int amount, int accountId, String purpose, int accountIdTo) {
        super(amount, accountId, purpose);
        this.accountIdTo = accountIdTo;
    }
    public int getAccountIdTo() {
        return accountIdTo;
    }
    @Override
    public String getTransactionType() {
        return "internal";
    }
}
