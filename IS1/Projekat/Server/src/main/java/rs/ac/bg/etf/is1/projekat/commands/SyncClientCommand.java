package rs.ac.bg.etf.is1.projekat.commands;

import rs.ac.bg.etf.is1.projekat.tables.Client;

public class SyncClientCommand extends Command {
    private final Client client;
    public SyncClientCommand(Client client) {
        this.client = client;
    }
    @Override
    public Destination getDestination() {
        return Destination.S2;
    }
    public Client getClient() {
        return client;
    }
    @Override
    public Type getType() {
        return Type.SYNC_CLIENT;
    }
}
