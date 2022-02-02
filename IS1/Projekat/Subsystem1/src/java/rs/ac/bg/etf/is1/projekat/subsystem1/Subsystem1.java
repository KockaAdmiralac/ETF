package rs.ac.bg.etf.is1.projekat.subsystem1;

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
import rs.ac.bg.etf.is1.projekat.commands.SyncClientCommand;
import rs.ac.bg.etf.is1.projekat.responses.CommandHandler;
import rs.ac.bg.etf.is1.projekat.responses.DataResponse;
import rs.ac.bg.etf.is1.projekat.responses.JMSResponse;
import rs.ac.bg.etf.is1.projekat.tables.Client;

public class Subsystem1 {
    @Resource(lookup="jms/__defaultConnectionFactory")
    private static ConnectionFactory connectionFactory;

    @Resource(lookup="s1Queue")
    private static Queue s1Queue;

    @Resource(lookup="s2Queue")
    private static Queue s2Queue;
    
    private static final Map<Command.Type, CommandHandler> handlers = assignHandlers();

    private static Map<Command.Type, CommandHandler> assignHandlers() {
        EntityManagerFactory emf = Persistence.createEntityManagerFactory("Subsystem1PU");
        EntityManager em = emf.createEntityManager();
        Map<Command.Type, CommandHandler> map = new EnumMap<>(Command.Type.class);
        map.put(Command.Type.CREATE_PLACE, new CreatePlaceHandler(em));
        map.put(Command.Type.CREATE_OFFICE, new CreateOfficeHandler(em));
        map.put(Command.Type.CREATE_CLIENT, new CreateClientHandler(em));
        map.put(Command.Type.UPDATE_CLIENT, new UpdateClientHandler(em));
        map.put(Command.Type.GET_PLACES, new GetPlacesHandler(em));
        map.put(Command.Type.GET_OFFICES, new GetOfficesHandler(em));
        map.put(Command.Type.GET_CLIENTS, new GetClientsHandler(em));
        map.put(Command.Type.GET_BACKUP, new GetBackupHandler(em));
        return map;
    }
    
    public static void main(String[] args) {
        JMSContext context = connectionFactory.createContext();
        JMSProducer producer = context.createProducer();
        JMSConsumer consumer = context.createConsumer(s1Queue);
        Message msg;
        while ((msg = consumer.receiveNoWait()) != null) {
            System.out.println("Discarding message " + msg);
        }
        System.out.println("Subsystem 1 started.");
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
                if (cmd.getType() == Command.Type.CREATE_CLIENT && response instanceof DataResponse) {
                    System.out.println("Sending created client to S2...");
                    DataResponse<Client> dataResponseMsg = (DataResponse<Client>) response;
                    SyncClientCommand scc = new SyncClientCommand(dataResponseMsg.getData());
                    ObjectMessage s2Msg = context.createObjectMessage(scc);
                    s2Msg.setJMSCorrelationID(msg.getJMSCorrelationID());
                    s2Msg.setJMSReplyTo(s1Queue);
                    producer.send(s2Queue, s2Msg);
                    // Consume response
                    Message s2Response = consumer.receive(10000);
                    if (s2Response == null) {
                        System.err.println("S2 did not respond!");
                    } else {
                        System.out.println("Client sent!");
                    }
                }
            } catch (Exception ex) {
                Logger.getLogger(Subsystem1.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
    }
}
