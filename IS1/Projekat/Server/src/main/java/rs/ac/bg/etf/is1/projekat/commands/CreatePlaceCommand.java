package rs.ac.bg.etf.is1.projekat.commands;

public class CreatePlaceCommand extends Command {
    private final int postalCode;
    private final String name;
    public CreatePlaceCommand(int postalCode, String name) {
        this.postalCode = postalCode;
        this.name = name;
    }
    public int getPostalCode() {
        return postalCode;
    }
    public String getName() {
        return name;
    }
    @Override
    public Destination getDestination() {
        return Destination.S1;
    }
    @Override
    public Type getType() {
        return Type.CREATE_PLACE;
    }
}
