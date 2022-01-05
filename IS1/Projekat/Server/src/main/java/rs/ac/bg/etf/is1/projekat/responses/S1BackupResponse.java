package rs.ac.bg.etf.is1.projekat.responses;

import java.util.List;
import rs.ac.bg.etf.is1.projekat.commands.Command;
import rs.ac.bg.etf.is1.projekat.tables.Client;
import rs.ac.bg.etf.is1.projekat.tables.Office;
import rs.ac.bg.etf.is1.projekat.tables.Place;

public class S1BackupResponse extends SuccessfulResponse {
    private final List<Client> clients;
    private final List<Office> offices;
    private final List<Place> places;
    public S1BackupResponse(Command cmd, List<Client> clients,
            List<Office> offices, List<Place> places) {
        super(cmd);
        this.clients = clients;
        this.offices = offices;
        this.places = places;
    }
    public List<Client> getClients() {
        return clients;
    }
    public List<Office> getOffices() {
        return offices;
    }
    public List<Place> getPlaces() {
        return places;
    }
}
