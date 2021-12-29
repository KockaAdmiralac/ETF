package vilenjak;

import java.io.Serializable;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.annotation.Resource;
import javax.jms.*;

public class Vilenjak {
    @Resource(lookup="jms/__defaultConnectionFactory")
    private static ConnectionFactory connectionFactory;

    @Resource(lookup="myQueue")
    private static Queue myQueue;

    public static void main(String[] args) {
        JMSContext context = connectionFactory.createContext();
        JMSConsumer consumer = context.createConsumer(myQueue);
        while (true) {
            try {
                Message msg = consumer.receiveNoWait();
                if (msg == null) {
                    System.out.println("Nothing in queue, sleeping");
                    Thread.sleep(60000);
                } else if (msg instanceof ObjectMessage) {
                    System.out.println("Received " + ((ObjectMessage)msg).getObject());
                } else {
                    System.err.println("Received non-object message!");
                }
            } catch (InterruptedException | JMSException ex) {
                Logger.getLogger(Vilenjak.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
    }
}
