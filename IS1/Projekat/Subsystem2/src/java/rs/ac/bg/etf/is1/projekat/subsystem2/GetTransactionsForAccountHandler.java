package rs.ac.bg.etf.is1.projekat.subsystem2;

import java.util.List;
import javax.persistence.EntityManager;
import javax.persistence.TypedQuery;
import rs.ac.bg.etf.is1.projekat.commands.Command;
import rs.ac.bg.etf.is1.projekat.commands.GetTransactionsForAccountCommand;
import rs.ac.bg.etf.is1.projekat.responses.CommandHandler;
import rs.ac.bg.etf.is1.projekat.responses.DataResponse;
import rs.ac.bg.etf.is1.projekat.responses.FailureResponse;
import rs.ac.bg.etf.is1.projekat.responses.JMSResponse;
import rs.ac.bg.etf.is1.projekat.tables.Account;
import rs.ac.bg.etf.is1.projekat.tables.Transaction;

public class GetTransactionsForAccountHandler extends CommandHandler {
    public GetTransactionsForAccountHandler(EntityManager em) {
        super(em);
    }
    @Override
    public JMSResponse handle(Command cmd) {
        GetTransactionsForAccountCommand data = (GetTransactionsForAccountCommand)cmd;
        Account account = em.find(Account.class, data.getAccountId());
        if (account == null || account.getStatus().equals("closed")) {
            return new FailureResponse(cmd, "No account with given ID exists.");
        }
        List<Transaction> results = em.createNamedQuery("Transaction.findByAccount", Transaction.class)
            .setParameter("account", account)
            .getResultList();
        return new DataResponse<>(cmd, results);
    }
}
