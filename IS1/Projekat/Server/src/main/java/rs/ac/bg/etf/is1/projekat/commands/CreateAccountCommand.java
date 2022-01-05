package rs.ac.bg.etf.is1.projekat.commands;

public class CreateAccountCommand extends Command {
    private final int clientId;
    private final int placeId;
    private final int overdraft;
    public CreateAccountCommand(int clientId, int placeId, int overdraft) {
        this.clientId = clientId;
        this.placeId = placeId;
        this.overdraft = overdraft;
    }
    public int getClientId() {
        return clientId;
    }
    public int getPlaceId() {
        return placeId;
    }
    public int getOverdraft() {
        return overdraft;
    }
    @Override
    public Command.Destination getDestination() {
        return Command.Destination.S2;
    }
    @Override
    public Command.Type getType() {
        return Command.Type.CREATE_ACCOUNT;
    }
}
