package rs.ac.bg.etf.is1.projekat.subsystem1;

import java.util.List;
import javax.persistence.EntityManager;
import javax.persistence.TypedQuery;
import rs.ac.bg.etf.is1.projekat.commands.Command;
import rs.ac.bg.etf.is1.projekat.responses.CommandHandler;
import rs.ac.bg.etf.is1.projekat.responses.DataResponse;
import rs.ac.bg.etf.is1.projekat.responses.JMSResponse;
import rs.ac.bg.etf.is1.projekat.tables.Place;

public class GetPlacesHandler extends CommandHandler {
    public GetPlacesHandler(EntityManager em) {
        super(em);
    }
    @Override
    public JMSResponse handle(Command cmd) {
        TypedQuery<Place> query = em.createNamedQuery("Place.findAll", Place.class);
        List<Place> results = query.getResultList();
        results.forEach(result -> {
            em.detach(result);
//            result.setClientList(null);
            result.setOfficeList(null);
        });
        return new DataResponse<>(cmd, results);
    }
}
