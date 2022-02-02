package rs.ac.bg.etf.is1.projekat.subsystem2;

import java.util.List;
import javax.persistence.EntityManager;
import javax.persistence.TypedQuery;
import rs.ac.bg.etf.is1.projekat.commands.Command;
import rs.ac.bg.etf.is1.projekat.commands.GetAccountsForClientCommand;
import rs.ac.bg.etf.is1.projekat.responses.CommandHandler;
import rs.ac.bg.etf.is1.projekat.responses.DataResponse;
import rs.ac.bg.etf.is1.projekat.responses.FailureResponse;
import rs.ac.bg.etf.is1.projekat.responses.JMSResponse;
import rs.ac.bg.etf.is1.projekat.tables.Account;
import rs.ac.bg.etf.is1.projekat.tables.Client;

public class GetAccountsForClientHandler extends CommandHandler {
    public GetAccountsForClientHandler(EntityManager em) {
        super(em);
    }
    @Override
    public JMSResponse handle(Command cmd) {
        GetAccountsForClientCommand data = (GetAccountsForClientCommand)cmd;
        Client client = em.find(Client.class, data.getClientId());
        if (client == null) {
            return new FailureResponse(cmd, "No client with given ID exists.");
        }
        List<Account> results = em.createNamedQuery("Account.findByClientId", Account.class)
            .setParameter("clientId", client.getId())
            .getResultList();
        return new DataResponse<>(cmd, results);
    }
}
