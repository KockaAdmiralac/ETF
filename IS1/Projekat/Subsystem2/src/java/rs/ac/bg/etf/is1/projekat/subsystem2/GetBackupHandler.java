package rs.ac.bg.etf.is1.projekat.subsystem2;

import java.util.List;
import javax.persistence.EntityManager;
import rs.ac.bg.etf.is1.projekat.commands.Command;
import rs.ac.bg.etf.is1.projekat.responses.CommandHandler;
import rs.ac.bg.etf.is1.projekat.responses.JMSResponse;
import rs.ac.bg.etf.is1.projekat.responses.S2BackupResponse;
import rs.ac.bg.etf.is1.projekat.tables.Account;
import rs.ac.bg.etf.is1.projekat.tables.Transaction;

public class GetBackupHandler extends CommandHandler {
    public GetBackupHandler(EntityManager em) {
        super(em);
    }
    @Override
    public JMSResponse handle(Command cmd) {
        List<Account> accounts = em.createNamedQuery("Account.findAll", Account.class).getResultList();
        List<Transaction> transactions = em.createNamedQuery("Transaction.findAll", Transaction.class).getResultList();
        return new S2BackupResponse(cmd, accounts, transactions);
    }
}
