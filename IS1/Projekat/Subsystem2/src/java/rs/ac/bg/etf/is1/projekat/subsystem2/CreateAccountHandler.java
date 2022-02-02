package rs.ac.bg.etf.is1.projekat.subsystem2;

import javax.persistence.EntityManager;
import rs.ac.bg.etf.is1.projekat.commands.Command;
import rs.ac.bg.etf.is1.projekat.commands.CreateAccountCommand;
import rs.ac.bg.etf.is1.projekat.responses.CommandHandler;
import rs.ac.bg.etf.is1.projekat.responses.DataResponse;
import rs.ac.bg.etf.is1.projekat.responses.FailureResponse;
import rs.ac.bg.etf.is1.projekat.responses.JMSResponse;
import rs.ac.bg.etf.is1.projekat.tables.Account;
import rs.ac.bg.etf.is1.projekat.tables.Client;

public class CreateAccountHandler extends CommandHandler {
    public CreateAccountHandler(EntityManager em) {
        super(em);
    }
    @Override
    public JMSResponse handle(Command cmd) {
        CreateAccountCommand data = (CreateAccountCommand)cmd;
        Client client = em.find(Client.class, data.getClientId());
        if (client == null) {
            return new FailureResponse(cmd, "Client with given ID not found.");
        }
        Account account = new Account();
        account.setClientId(client.getId());
        account.setPlaceId(data.getPlaceId());
        account.setOverdraft(data.getOverdraft());
        em.getTransaction().begin();
        em.persist(account);
        em.getTransaction().commit();
        em.clear();
        return new DataResponse<>(cmd, account);
    }
}
