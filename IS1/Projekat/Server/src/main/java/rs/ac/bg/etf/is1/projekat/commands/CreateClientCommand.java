package rs.ac.bg.etf.is1.projekat.commands;

public class CreateClientCommand extends Command {
    private final String name;
    private final String address;
    private final int placeId;
    public CreateClientCommand(String name, String address, int placeId) {
        this.name = name;
        this.address = address;
        this.placeId = placeId;
    }
    public String getAddress() {
        return address;
    }
    public String getName() {
        return name;
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
        return Command.Type.CREATE_CLIENT;
    }
}
