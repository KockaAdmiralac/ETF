package rs.ac.bg.etf.is1.projekat.commands;

public class DeleteAccountCommand extends Command {
    private final int accountId;
    public DeleteAccountCommand(int accountId) {
        this.accountId = accountId;
    }
    public int getAccountId() {
        return accountId;
    }
    @Override
    public Command.Destination getDestination() {
        return Command.Destination.S2;
    }
    @Override
    public Command.Type getType() {
        return Command.Type.DELETE_ACCOUNT;
    }
}
