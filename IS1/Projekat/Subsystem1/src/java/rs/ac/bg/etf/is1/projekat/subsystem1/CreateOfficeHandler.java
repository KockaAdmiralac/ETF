package rs.ac.bg.etf.is1.projekat.subsystem1;

import javax.persistence.EntityManager;
import rs.ac.bg.etf.is1.projekat.commands.Command;
import rs.ac.bg.etf.is1.projekat.commands.CreateOfficeCommand;
import rs.ac.bg.etf.is1.projekat.responses.CommandHandler;
import rs.ac.bg.etf.is1.projekat.responses.DataResponse;
import rs.ac.bg.etf.is1.projekat.responses.FailureResponse;
import rs.ac.bg.etf.is1.projekat.responses.JMSResponse;
import rs.ac.bg.etf.is1.projekat.tables.Office;
import rs.ac.bg.etf.is1.projekat.tables.Place;

public class CreateOfficeHandler extends CommandHandler {
    public CreateOfficeHandler(EntityManager em) {
        super(em);
    }
    @Override
    public JMSResponse handle(Command cmd) {
        CreateOfficeCommand data = (CreateOfficeCommand)cmd;
        Place place = em.find(Place.class, data.getPlaceId());
        if (place == null) {
            return new FailureResponse(cmd, "No place with given ID exists.");
        }
        Office office = new Office();
        office.setAddress(data.getAddress());
        office.setName(data.getName());
        office.setPlace(place);
        em.getTransaction().begin();
        em.persist(office);
        em.getTransaction().commit();
        em.clear();
        return new DataResponse<>(cmd, office);
    }
}
