package rs.ac.bg.etf.is1.projekat.subsystem1;

import java.util.List;
import javax.persistence.EntityManager;
import javax.persistence.TypedQuery;
import rs.ac.bg.etf.is1.projekat.commands.Command;
import rs.ac.bg.etf.is1.projekat.responses.CommandHandler;
import rs.ac.bg.etf.is1.projekat.responses.DataResponse;
import rs.ac.bg.etf.is1.projekat.responses.JMSResponse;
import rs.ac.bg.etf.is1.projekat.tables.Office;

public class GetOfficesHandler extends CommandHandler {
    public GetOfficesHandler(EntityManager em) {
        super(em);
    }
    @Override
    public JMSResponse handle(Command cmd) {
        TypedQuery<Office> query = em.createNamedQuery("Office.findAll", Office.class);
        List<Office> results = query.getResultList();
        results.forEach(result -> {
            em.detach(result);
            result.setPlaceId(null);
        });
        return new DataResponse<>(cmd, results);
    }
}
