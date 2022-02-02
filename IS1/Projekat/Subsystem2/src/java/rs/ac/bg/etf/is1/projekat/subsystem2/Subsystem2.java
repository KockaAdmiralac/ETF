package rs.ac.bg.etf.is1.projekat.subsystem2;

import java.io.Serializable;
import java.util.EnumMap;
import java.util.Map;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.annotation.Resource;
import javax.jms.ConnectionFactory;
import javax.jms.Destination;
import javax.jms.JMSConsumer;
import javax.jms.JMSContext;
import javax.jms.JMSProducer;
import javax.jms.Message;
import javax.jms.ObjectMessage;
import javax.jms.Queue;
import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;
import javax.persistence.Persistence;
import rs.ac.bg.etf.is1.projekat.commands.Command;
import rs.ac.bg.etf.is1.projekat.responses.CommandHandler;
import rs.ac.bg.etf.is1.projekat.responses.JMSResponse;

public class Subsystem2 {
    @Resource(lookup="jms/__defaultConnectionFactory")
    private static ConnectionFactory connectionFactory;

    @Resource(lookup="s2Queue")
    private static Queue s2Queue;

    private static final Map<Command.Type, CommandHandler> handlers = assignHandlers();

    private static Map<Command.Type, CommandHandler> assignHandlers() {
        EntityManagerFactory emf = Persistence.createEntityManagerFactory("Subsystem2PU");
        EntityManager em = emf.createEntityManager();
        Map<Command.Type, CommandHandler> map = new EnumMap<>(Command.Type.class);
        map.put(Command.Type.CREATE_ACCOUNT, new CreateAccountHandler(em));
        map.put(Command.Type.DELETE_ACCOUNT, new DeleteAccountHandler(em));
        map.put(Command.Type.CREATE_TRANSACTION, new CreateTransactionHandler(em));
        map.put(Command.Type.GET_ACCOUNTS_FOR_CLIENT, new GetAccountsForClientHandler(em));
        map.put(Command.Type.GET_TRANSACTIONS_FOR_ACCOUNT, new GetTransactionsForAccountHandler(em));
        map.put(Command.Type.GET_BACKUP, new GetBackupHandler(em));
        map.put(Command.Type.SYNC_CLIENT, new SyncClientHandler(em));
        return map;
    }
    
    public static void main(String[] args) {
        JMSContext context = connectionFactory.createContext();
        JMSProducer producer = context.createProducer();
        JMSConsumer consumer = context.createConsumer(s2Queue);
        Message msg;
        while ((msg = consumer.receiveNoWait()) != null) {
            System.out.println("Discarding message " + msg);
        }
        System.out.println("Subsystem 2 started.");
        while (true) {
            try {
                msg = consumer.receive();
                Destination replyTo = msg.getJMSReplyTo();
                if (replyTo == null || !(replyTo instanceof Queue)) {
                    System.err.println("JMS-Reply-To is invalid: " + msg);
                    continue;
                }
                if (!(msg instanceof ObjectMessage)) {
                    System.err.println("Message is not an ObjectMessage: " + msg);
                    continue;
                }
                Serializable obj = ((ObjectMessage)msg).getObject();
                if (!(obj instanceof Command)) {
                    System.err.println("Received object is not a command: " + obj);
                    continue;
                }
                Command cmd = (Command)obj;
                CommandHandler handler = handlers.get(cmd.getType());
                if (handler == null) {
                    System.err.println("No handler found for command: " + cmd);
                    continue;
                }
                System.out.println("Handling command " + cmd);
                JMSResponse response = handler.handle(cmd);
                ObjectMessage responseMsg = context.createObjectMessage(response);
                responseMsg.setJMSCorrelationID(msg.getJMSCorrelationID());
                System.out.println("Sending response " + response);
                producer.send(replyTo, responseMsg);
            } catch (Exception ex) {
                Logger.getLogger(Subsystem2.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
    }
}
