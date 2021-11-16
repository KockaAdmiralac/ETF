package radniktester;

import automobil.Automobil;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.annotation.Resource;
import javax.jms.ConnectionFactory;
import javax.jms.JMSConsumer;
import javax.jms.JMSContext;
import javax.jms.JMSException;
import javax.jms.Message;
import javax.jms.ObjectMessage;
import javax.jms.Topic;

public class Main {
    @Resource(lookup="jms/__defaultConnectionFactory")
    private static ConnectionFactory connectionFactory;

    @Resource(lookup="MyTopic")
    private static Topic myTopic;

    public static void main(String[] args) {
        JMSContext context = connectionFactory.createContext();
        JMSConsumer consumer = context.createSharedDurableConsumer(myTopic, "sub1");
        while (true) {
            try {
                Message msg = consumer.receive();
                System.out.println("Received car");
                if (msg instanceof ObjectMessage) {
                    Automobil auto = (Automobil)((ObjectMessage) msg).getObject();
                    System.out.println("Received " + auto);
                }
            } catch (JMSException ex) {
                Logger.getLogger(Main.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
    }    
}
