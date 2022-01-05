package rs.ac.bg.etf.is1.projekat.subsystem2;

import javax.persistence.EntityManager;
import javax.persistence.TypedQuery;
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
        Account accountFrom = em.find(Account.class, data.getAccountIdFrom());
        if (accountFrom == null) {
            return new FailureResponse(cmd, "Source account with specified ID does not exist.");
        }
        if (accountFrom.getStatus() == Account.Status.BLOCKED) {
            return new FailureResponse(cmd, "Source account is blocked.");
        }
        Account accountTo = em.find(Account.class, data.getAccountIdTo());
        if (accountTo == null) {
            return new FailureResponse(cmd, "Destination account with specified ID does not exist.");
        }
        // This is not efficient...
        TypedQuery<Transaction> query = em.createNamedQuery("Transaction.findByAccountId", Transaction.class);
        query.setParameter("accountId", accountFrom);
        int transactionNumber = query.getResultList().size();

        Transaction transaction = new Transaction();
        transaction.setType(data.getTransactionType());
        transaction.setAmount(data.getAmount());
        transaction.setTransactionNumber(transactionNumber);
        transaction.setPurpose(data.getPurpose());
        transaction.setAccountIdFrom(accountFrom);
        transaction.setAccountIdTo(accountTo);
        if (data.getTransactionType().equals("incoming")) {
            transaction.setOfficeId(((CreateIncomingTransactionCommand)data).getOfficeId());
        } else if (data.getTransactionType().equals("outgoing")) {
            transaction.setOfficeId(((CreateOutgoingTransactionCommand)data).getOfficeId());
        }
        em.getTransaction().begin();
        em.persist(transaction);
        em.getTransaction().commit();
        em.clear();
        return new DataResponse<>(cmd, transaction);
    }
}
