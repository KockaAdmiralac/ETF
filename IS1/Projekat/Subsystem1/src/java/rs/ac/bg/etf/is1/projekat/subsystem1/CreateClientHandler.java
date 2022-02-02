package rs.ac.bg.etf.is1.projekat.subsystem1;

import javax.persistence.EntityManager;
import rs.ac.bg.etf.is1.projekat.commands.Command;
import rs.ac.bg.etf.is1.projekat.commands.CreateClientCommand;
import rs.ac.bg.etf.is1.projekat.responses.CommandHandler;
import rs.ac.bg.etf.is1.projekat.responses.DataResponse;
import rs.ac.bg.etf.is1.projekat.responses.FailureResponse;
import rs.ac.bg.etf.is1.projekat.responses.JMSResponse;
import rs.ac.bg.etf.is1.projekat.tables.Client;
import rs.ac.bg.etf.is1.projekat.tables.Place;

public class CreateClientHandler extends CommandHandler {
    public CreateClientHandler(EntityManager em) {
        super(em);
    }
    @Override
    public JMSResponse handle(Command cmd) {
        CreateClientCommand data = (CreateClientCommand)cmd;
        Place place = em.find(Place.class, data.getPlaceId());
        if (place == null) {
            return new FailureResponse(cmd, "No place with given ID exists.");
        }
        Client client = new Client();
        client.setAddress(data.getAddress());
        client.setName(data.getName());
        client.setPlaceId(place.getId());
        em.getTransaction().begin();
        em.persist(client);
        em.getTransaction().commit();
        em.clear();
        return new DataResponse<>(cmd, client);
    }
}
