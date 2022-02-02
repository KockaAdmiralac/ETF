package rs.ac.bg.etf.is1.projekat.commands;

public class CreateOutgoingTransactionCommand extends CreateTransactionCommand {
    private final int officeId;
    public CreateOutgoingTransactionCommand(int amount, int accountId, String purpose, int officeId) {
        super(amount, accountId, purpose);
        this.officeId = officeId;
    }
    public int getOfficeId() {
        return officeId;
    }
    @Override
    public String getTransactionType() {
        return "outgoing";
    }
}
