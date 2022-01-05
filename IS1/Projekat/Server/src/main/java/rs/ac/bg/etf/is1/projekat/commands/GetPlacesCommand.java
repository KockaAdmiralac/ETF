package rs.ac.bg.etf.is1.projekat.commands;

public class GetPlacesCommand extends Command {
    @Override
    public Destination getDestination() {
        return Destination.S1;
    }
    @Override
    public Type getType() {
        return Type.GET_PLACES;
    }
}
