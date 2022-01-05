package rs.ac.bg.etf.is1.projekat.commands;

public class CreateOfficeCommand extends Command {
    private final String name;
    private final String address;
    private final int placeId;
    public CreateOfficeCommand(String name, String address, int placeId) {
        this.name = name;
        this.address = address;
        this.placeId = placeId;
    }
    public String getName() {
        return name;
    }
    public String getAddress() {
        return address;
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
        return Command.Type.CREATE_OFFICE;
    }
}
