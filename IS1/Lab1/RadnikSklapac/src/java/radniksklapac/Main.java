package radniksklapac;

import automobil.Automobil;
import delovi.*;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.annotation.Resource;
import javax.jms.ConnectionFactory;
import javax.jms.JMSConsumer;
import javax.jms.JMSContext;
import javax.jms.JMSException;
import javax.jms.JMSProducer;
import javax.jms.Message;
import javax.jms.Queue;
import javax.jms.ObjectMessage;
import javax.jms.Topic;

public class Main {
    @Resource(lookup="jms/__defaultConnectionFactory")
    private static ConnectionFactory connectionFactory;
    
    @Resource(lookup="myQueue")
    private static Queue myQueue;
    
    @Resource(lookup="MyTopic")
    private static Topic myTopic;
    
    public static void main(String[] args) {
        JMSContext context = connectionFactory.createContext();
        JMSConsumer consumerA = context.createConsumer(myQueue, "Type = 'A'");
        JMSConsumer consumerB = context.createConsumer(myQueue, "Type = 'B'");
        JMSConsumer consumerC = context.createConsumer(myQueue, "Type = 'C'");
        JMSProducer producer = context.createProducer();
        while (true) {
            Message msgA = consumerA.receive();
            System.out.println("Received A");
            Message msgB = consumerB.receive();
            System.out.println("Received B");
            Message msgC = consumerC.receive();
            System.out.println("Received C");
            if (msgA instanceof ObjectMessage && msgB instanceof ObjectMessage && msgC instanceof ObjectMessage) {
                try {
                    ObjectMessage objMsgA = (ObjectMessage)msgA;
                    ObjectMessage objMsgB = (ObjectMessage)msgB;
                    ObjectMessage objMsgC = (ObjectMessage)msgC;
                    A a = (A)objMsgA.getObject();
                    B b = (B)objMsgB.getObject();
                    C c = (C)objMsgC.getObject();
                    Automobil auto = new Automobil(a, b, c);
                    Thread.sleep(5000);
                    System.out.println("Produced " + auto);
                    ObjectMessage autoMsg = context.createObjectMessage(auto);
                    producer.send(myTopic, autoMsg);
                } catch (JMSException | InterruptedException ex) {
                    Logger.getLogger(Main.class.getName()).log(Level.SEVERE, null, ex);
                }
            }
        }
    }
}
