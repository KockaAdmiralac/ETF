package rs.ac.bg.etf.is1.projekat.subsystem1;

import java.util.List;
import javax.persistence.EntityManager;
import rs.ac.bg.etf.is1.projekat.commands.Command;
import rs.ac.bg.etf.is1.projekat.responses.CommandHandler;
import rs.ac.bg.etf.is1.projekat.responses.DataResponse;
import rs.ac.bg.etf.is1.projekat.responses.JMSResponse;
import rs.ac.bg.etf.is1.projekat.tables.Client;

public class GetClientsHandler extends CommandHandler {
    public GetClientsHandler(EntityManager em) {
        super(em);
    }
    @Override
    public JMSResponse handle(Command cmd) {
        List<Client> results = em.createNamedQuery("Client.findAll", Client.class).getResultList();
        return new DataResponse<>(cmd, results);
    }
}
