package rs.ac.bg.etf.is1.projekat.commands;

public abstract class CreateTransactionCommand extends Command {
    private final int amount;
    private final int accountId;
    private final String purpose;
    public CreateTransactionCommand(int amount, int accountId, String purpose) {
        this.amount = amount;
        this.accountId = accountId;
        this.purpose = purpose;
    }
    public int getAmount() {
        return amount;
    }
    public int getAccountId() {
        return accountId;
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
