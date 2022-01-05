package rs.ac.bg.etf.is1.projekat.commands;

public class UpdateClientCommand extends Command {
    private final int clientId;
    private final int placeId;
    public UpdateClientCommand(int clientId, int placeId) {
        this.clientId = clientId;
        this.placeId = placeId;
    }
    public int getClientId() {
        return clientId;
    }
    public int getPlaceId() {
        return placeId;
    }
    @Override
    public Command.Destination getDestination() {
        return Command.Destination.S1;
    }
    @Override
    public Command.Type getType() {
        return Command.Type.UPDATE_CLIENT;
    }
}
