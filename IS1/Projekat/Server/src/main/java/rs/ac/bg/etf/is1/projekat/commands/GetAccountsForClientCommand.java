package rs.ac.bg.etf.is1.projekat.commands;

public class GetAccountsForClientCommand extends Command {
    private final int clientId;
    public GetAccountsForClientCommand(int clientId) {
        this.clientId = clientId;
    }
    public int getClientId() {
        return clientId;
    }
    @Override
    public Command.Destination getDestination() {
        return Command.Destination.S2;
    }
    @Override
    public Command.Type getType() {
        return Command.Type.GET_ACCOUNTS_FOR_CLIENT;
    }
}
