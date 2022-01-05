package rs.ac.bg.etf.is1.projekat.commands;

public abstract class CreateTransactionCommand extends Command {
    private final int amount;
    private final int accountIdFrom;
    private final int accountIdTo;
    private final String purpose;
    public CreateTransactionCommand(int amount, int accountIdFrom, int accountIdTo, String purpose) {
        this.amount = amount;
        this.accountIdFrom = accountIdFrom;
        this.accountIdTo = accountIdTo;
        this.purpose = purpose;
    }
    public int getAmount() {
        return amount;
    }
    public int getAccountIdFrom() {
        return accountIdFrom;
    }
    public int getAccountIdTo() {
        return accountIdTo;
    }
    public String getPurpose() {
        return purpose;
    }
    @Override
    public Command.Destination getDestination() {
        return Command.Destination.S2;
    }
    @Override
    public Type getType() {
        return Type.CREATE_TRANSACTION;
    }
    public abstract String getTransactionType();
}
