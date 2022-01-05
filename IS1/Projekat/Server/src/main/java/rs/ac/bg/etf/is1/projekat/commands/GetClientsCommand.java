package rs.ac.bg.etf.is1.projekat.commands;

public class GetClientsCommand extends Command {
    @Override
    public Command.Destination getDestination() {
        return Command.Destination.S1;
    }
    @Override
    public Command.Type getType() {
        return Command.Type.GET_CLIENTS;
    }
}
