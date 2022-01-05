package rs.ac.bg.etf.is1.projekat.subsystem1;

import javax.persistence.EntityManager;
import rs.ac.bg.etf.is1.projekat.commands.Command;
import rs.ac.bg.etf.is1.projekat.commands.CreatePlaceCommand;
import rs.ac.bg.etf.is1.projekat.responses.CommandHandler;
import rs.ac.bg.etf.is1.projekat.responses.DataResponse;
import rs.ac.bg.etf.is1.projekat.responses.JMSResponse;
import rs.ac.bg.etf.is1.projekat.tables.Place;

public class CreatePlaceHandler extends CommandHandler {
    public CreatePlaceHandler(EntityManager em) {
        super(em);
    }
    @Override
    public JMSResponse handle(Command cmd) {
        CreatePlaceCommand data = (CreatePlaceCommand)cmd;
        Place place = new Place();
        place.setPostalCode(data.getPostalCode());
        place.setName(data.getName());
        em.getTransaction().begin();
        em.persist(place);
        em.getTransaction().commit();
        em.clear();
        return new DataResponse<>(cmd, place);
    }
}
