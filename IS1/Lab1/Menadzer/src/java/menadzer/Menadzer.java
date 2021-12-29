package menadzer;

import java.util.logging.Level;
import java.util.logging.Logger;
import javax.annotation.Resource;
import javax.jms.*;

public class Menadzer {
    @Resource(lookup="jms/__defaultConnectionFactory")
    private static ConnectionFactory connectionFactory;

    @Resource(lookup="myTopic")
    private static Topic myTopic;

    private static void sendRequest(JMSContext context, JMSProducer producer, String type) throws JMSException {
        int amount = (int)(Math.random() * 5) + 1;
        TextMessage msg = context.createTextMessage(type + " " + amount);
        msg.setStringProperty("Type", type);
        producer.send(myTopic, msg);
        System.out.println("Sent " + type + " x" + amount);
    }

    public static void main(String[] args) {
        JMSContext context = connectionFactory.createContext();
        JMSProducer producer = context.createProducer();
        while (true) {
            try {
                sendRequest(context, producer, "Ratluk");
                sendRequest(context, producer, "Cokoladica");
                sendRequest(context, producer, "Bombona");
                Thread.sleep(5000);
            } catch (InterruptedException | JMSException ex) {
                Logger.getLogger(Menadzer.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
    }
}
