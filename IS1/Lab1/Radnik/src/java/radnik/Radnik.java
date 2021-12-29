package radnik;

import java.io.Serializable;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.annotation.Resource;
import javax.jms.*;
import slatkisi.*;

public class Radnik {
    @Resource(lookup="jms/__defaultConnectionFactory")
    private static ConnectionFactory connectionFactory;

    @Resource(lookup="myTopic")
    private static Topic myTopic;
    
    @Resource(lookup="myQueue")
    private static Queue myQueue;

    private static int staticId = 0;
    
    private static Serializable getCandy(String name) {
        switch (name) {
            case "Ratluk": return new Ratluk(staticId++);
            case "Cokoladica": return new Cokoladica(staticId++);
            case "Bombona": return new Bombona(staticId++);
        }
        return null;
    }
    
    public static void main(String[] args) {
        if (args.length != 1) {
            throw new RuntimeException("Must pass candy name as first command-line argument!");
        }
        String candy = args[0];
        if (!(candy.equals("Ratluk") || candy.equals("Cokoladica") || candy.equals("Bombona"))) {
            throw new RuntimeException("Invalid candy name!");
        }
        JMSContext context = connectionFactory.createContext();
        JMSProducer producer = context.createProducer();
        JMSConsumer consumer = context.createSharedDurableConsumer(myTopic, "sub" + candy, "Type = '" + candy + "'");
        while (true) {
            try {
                Message msg = consumer.receive();
                if (msg instanceof TextMessage) {
                    String text = ((TextMessage)msg).getText();
                    System.out.println("Received " + text);
                    int amount = Integer.parseInt(text.split(" ")[1]);
                    for (int i = 0; i < amount; ++i) {
                        Serializable candyObj = getCandy(candy);
                        producer.send(myQueue, context.createObjectMessage(candyObj));
                        System.out.println("Sent " + candyObj);
                    }
                } else {
                    System.err.println("Received non-text message!");
                }
            } catch (JMSException ex) {
                Logger.getLogger(Radnik.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
    }
}
