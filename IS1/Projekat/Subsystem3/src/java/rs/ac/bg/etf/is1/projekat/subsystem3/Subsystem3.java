package rs.ac.bg.etf.is1.projekat.subsystem3;

import java.io.Serializable;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.annotation.Resource;
import javax.jms.ConnectionFactory;
import javax.jms.Destination;
import javax.jms.JMSConsumer;
import javax.jms.JMSContext;
import javax.jms.JMSException;
import javax.jms.JMSProducer;
import javax.jms.Message;
import javax.jms.ObjectMessage;
import javax.jms.Queue;
import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;
import javax.persistence.Persistence;
import rs.ac.bg.etf.is1.projekat.commands.GetBackupCommand;
import rs.ac.bg.etf.is1.projekat.responses.S1BackupResponse;
import rs.ac.bg.etf.is1.projekat.responses.S2BackupResponse;
import rs.ac.bg.etf.is1.projekat.responses.S3BackupResponse;
import rs.ac.bg.etf.is1.projekat.tables.Account;
import rs.ac.bg.etf.is1.projekat.tables.Client;
import rs.ac.bg.etf.is1.projekat.tables.Office;
import rs.ac.bg.etf.is1.projekat.tables.Place;
import rs.ac.bg.etf.is1.projekat.tables.Transaction;

public class Subsystem3 {
    @Resource(lookup="jms/__defaultConnectionFactory")
    private static ConnectionFactory connectionFactory;

    @Resource(lookup="s1Queue")
    private static Queue s1Queue;

    @Resource(lookup="s2Queue")
    private static Queue s2Queue;

    @Resource(lookup="s3Queue")
    private static Queue s3Queue;
    
    private static EntityManager em;

    private static void handleS1BackupResponse(S1BackupResponse r) {
        em.getTransaction().begin();
        r.getPlaces().forEach(p -> em.merge(p));
        em.flush();
        r.getClients().forEach(c -> em.merge(c));
        em.flush();
        r.getOffices().forEach(o -> em.merge(o));
        em.getTransaction().commit();
        em.clear();
    }

    private static void handleS2BackupResponse(S2BackupResponse r) {
        em.getTransaction().begin();
        r.getAccounts().forEach(a -> em.merge(a));
        em.flush();
        r.getTransactions().forEach(t -> em.merge(t));
        em.getTransaction().commit();
        em.clear();
    }
    
    private static S3BackupResponse handleGetBackupCommand(GetBackupCommand cmd) {
        List<Account> accounts = em.createNamedQuery("Account.findAll", Account.class).getResultList();
        List<Client> clients = em.createNamedQuery("Client.findAll", Client.class).getResultList();
        List<Office> offices = em.createNamedQuery("Office.findAll", Office.class).getResultList();
        List<Place> places = em.createNamedQuery("Place.findAll", Place.class).getResultList();
        List<Transaction> transactions = em.createNamedQuery("Transaction.findAll", Transaction.class).getResultList();
        return new S3BackupResponse(cmd, accounts, clients, offices, places, transactions);
    }
    
    public static void main(String[] args) {
        JMSContext context = connectionFactory.createContext();
        JMSProducer producer = context.createProducer();
        JMSConsumer consumer = context.createConsumer(s3Queue);
        EntityManagerFactory emf = Persistence.createEntityManagerFactory("Subsystem3PU");
        em = emf.createEntityManager();
        Message msg;
        while ((msg = consumer.receiveNoWait()) != null) {
            System.out.println("Discarding message " + msg);
        }
        System.out.println("Subsystem 3 started.");
        new Thread(() -> {
            try {
                while (true) {
                    Thread.sleep(2 * 60 * 1000);
                    System.out.println("Requesting backups.");
                    GetBackupCommand cmd = new GetBackupCommand();
                    ObjectMessage s1Msg = context.createObjectMessage(cmd);
                    ObjectMessage s2Msg = context.createObjectMessage(cmd);
                    s1Msg.setJMSReplyTo(s3Queue);
                    s2Msg.setJMSReplyTo(s3Queue);
                    producer.send(s1Queue, s1Msg);
                    producer.send(s2Queue, s2Msg);
                }
            } catch (InterruptedException | JMSException ex) {
                Logger.getLogger(Subsystem3.class.getName()).log(Level.SEVERE, null, ex);
            }
        }).start();
        while (true) {
            try {
                msg = consumer.receive();
                if (!(msg instanceof ObjectMessage)) {
                    System.err.println("Message is not an ObjectMessage: " + msg);
                    continue;
                }
                Serializable obj = ((ObjectMessage)msg).getObject();
                if (obj instanceof GetBackupCommand) {
                    Destination replyTo = msg.getJMSReplyTo();
                    if (replyTo == null || !(replyTo instanceof Queue)) {
                        System.err.println("JMS-Reply-To is invalid: " + msg);
                        continue;
                    }
                    System.out.println("Responding to backup request");
                    S3BackupResponse response = handleGetBackupCommand((GetBackupCommand)obj);
                    ObjectMessage responseMessage = context.createObjectMessage(response);
                    responseMessage.setJMSCorrelationID(msg.getJMSCorrelationID());
                    producer.send(msg.getJMSReplyTo(), responseMessage);
                } else if (obj instanceof S1BackupResponse) {
                    System.out.println("Got backup response from S1");
                    handleS1BackupResponse((S1BackupResponse)obj);
                } else if (obj instanceof S2BackupResponse) {
                    System.out.println("Got backup response from S2");
                    handleS2BackupResponse((S2BackupResponse)obj);
                } else {
                    System.err.println("Unhandled message: " + msg);
                }
            } catch (Exception ex) {
                Logger.getLogger(Subsystem3.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
    }
}
