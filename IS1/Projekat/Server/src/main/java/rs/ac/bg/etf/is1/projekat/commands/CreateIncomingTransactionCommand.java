package rs.ac.bg.etf.is1.projekat.commands;

public class CreateIncomingTransactionCommand extends CreateTransactionCommand {
    private final int officeId;
    public CreateIncomingTransactionCommand(int amount, int accountIdFrom, int accountIdTo, String purpose, int officeId) {
        super(amount, accountIdFrom, accountIdTo, purpose);
        this.officeId = officeId;
    }
    public int getOfficeId() {
        return officeId;
    }
    @Override
    public String getTransactionType() {
        return "incoming";
    }
}
