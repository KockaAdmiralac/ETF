package rs.ac.bg.etf.is1.projekat.subsystem2;

import javax.persistence.EntityManager;
import rs.ac.bg.etf.is1.projekat.commands.Command;
import rs.ac.bg.etf.is1.projekat.commands.DeleteAccountCommand;
import rs.ac.bg.etf.is1.projekat.responses.CommandHandler;
import rs.ac.bg.etf.is1.projekat.responses.FailureResponse;
import rs.ac.bg.etf.is1.projekat.responses.JMSResponse;
import rs.ac.bg.etf.is1.projekat.responses.OKResponse;
import rs.ac.bg.etf.is1.projekat.tables.Account;

public class DeleteAccountHandler extends CommandHandler {
    public DeleteAccountHandler(EntityManager em) {
        super(em);
    }
    @Override
    public JMSResponse handle(Command cmd) {
        DeleteAccountCommand data = (DeleteAccountCommand)cmd;
        Account account = em.find(Account.class, data.getAccountId());
        if (account == null) {
            return new FailureResponse(cmd, "Account with specified ID not found.");
        }
        em.getTransaction().begin();
        em.remove(account);
        em.getTransaction().commit();
        em.clear();
        return new OKResponse(cmd);
    }
}
