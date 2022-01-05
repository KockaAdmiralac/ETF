package rs.ac.bg.etf.is1.projekat.subsystem1;

import javax.persistence.EntityManager;
import rs.ac.bg.etf.is1.projekat.commands.Command;
import rs.ac.bg.etf.is1.projekat.commands.UpdateClientCommand;
import rs.ac.bg.etf.is1.projekat.responses.CommandHandler;
import rs.ac.bg.etf.is1.projekat.responses.DataResponse;
import rs.ac.bg.etf.is1.projekat.responses.FailureResponse;
import rs.ac.bg.etf.is1.projekat.responses.JMSResponse;
import rs.ac.bg.etf.is1.projekat.tables.Client;
import rs.ac.bg.etf.is1.projekat.tables.Place;

public class UpdateClientHandler extends CommandHandler {
    public UpdateClientHandler(EntityManager em) {
        super(em);
    }
    @Override
    public JMSResponse handle(Command cmd) {
        UpdateClientCommand data = (UpdateClientCommand)cmd;
        Client client = em.find(Client.class, data.getClientId());
        if (client == null) {
            return new FailureResponse(cmd, "No client with given ID exists.");
        }
        Place place = em.find(Place.class, data.getPlaceId());
        if (place == null) {
            return new FailureResponse(cmd, "No place with given ID exists.");
        }
        // Not a foreign key here
        client.setPlaceId(place.getId());
        em.getTransaction().begin();
        em.persist(client);
        em.getTransaction().commit();
        em.clear();
        return new DataResponse<>(cmd, client);
    }
}
