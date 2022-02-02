package rs.ac.bg.etf.is1.projekat.subsystem2;

import javax.persistence.EntityManager;
import rs.ac.bg.etf.is1.projekat.commands.Command;
import rs.ac.bg.etf.is1.projekat.commands.CreateIncomingTransactionCommand;
import rs.ac.bg.etf.is1.projekat.commands.CreateOutgoingTransactionCommand;
import rs.ac.bg.etf.is1.projekat.commands.CreateTransactionCommand;
import rs.ac.bg.etf.is1.projekat.responses.CommandHandler;
import rs.ac.bg.etf.is1.projekat.responses.DataResponse;
import rs.ac.bg.etf.is1.projekat.responses.FailureResponse;
import rs.ac.bg.etf.is1.projekat.responses.JMSResponse;
import rs.ac.bg.etf.is1.projekat.tables.Account;
import rs.ac.bg.etf.is1.projekat.tables.Transaction;

public class CreateTransactionHandler extends CommandHandler {
    public CreateTransactionHandler(EntityManager em) {
        super(em);
    }
    @Override
    public JMSResponse handle(Command cmd) {
        CreateTransactionCommand data = (CreateTransactionCommand)cmd;
        Account account = em.find(Account.class, data.getAccountId());
        if (account == null || account.getStatus().equals("closed")) {
            return new FailureResponse(cmd, "Account with specified ID does not exist.");
        }
        if (account.getStatus().equals("blocked") && !data.getTransactionType().equals("incoming")) {
            return new FailureResponse(cmd, "Account is not active.");
        }
        int transactionNumber = account.getTransactionCount() + 1;
        account.setTransactionCount(transactionNumber);
        int newBalance = account.getBalance();
        if (data.getTransactionType().equals("incoming")) {
            newBalance += data.getAmount();
        } else {
            newBalance -= data.getAmount();
        }
        account.setBalance(newBalance);
        if (newBalance < -account.getOverdraft()) {
            account.setStatus("blocked");
        } else {
            account.setStatus("active");
        }
        Transaction transaction = new Transaction();
        transaction.setType(data.getTransactionType());
        transaction.setAmount(data.getAmount());
        transaction.setTransactionNumber(transactionNumber);
        transaction.setPurpose(data.getPurpose());
        transaction.setAccount(account);
        if (data.getTransactionType().equals("incoming")) {
            transaction.setOffice(((CreateIncomingTransactionCommand)data).getOfficeId());
        } else if (data.getTransactionType().equals("outgoing")) {
            transaction.setOffice(((CreateOutgoingTransactionCommand)data).getOfficeId());
        }
        em.getTransaction().begin();
        em.persist(transaction);
        em.persist(account);
        em.getTransaction().commit();
        em.clear();
        return new DataResponse<>(cmd, transaction);
    }
}
