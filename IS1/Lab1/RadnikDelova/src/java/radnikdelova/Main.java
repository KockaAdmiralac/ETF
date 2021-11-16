package radnikdelova;

import java.io.Serializable;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.annotation.Resource;
import javax.jms.ConnectionFactory;
import javax.jms.JMSContext;
import javax.jms.JMSException;
import javax.jms.JMSProducer;
import javax.jms.Queue;
import javax.jms.ObjectMessage;
import delovi.*;

public class Main {
    @Resource(lookup="jms/__defaultConnectionFactory")
    private static ConnectionFactory connectionFactory;
    
    @Resource(lookup="myQueue")
    private static Queue myQueue;
    
    private static final char PART_NAME = 'A';
    private static int staticId = 0;
    
    public static void main(String[] args) {
        JMSContext context = connectionFactory.createContext();
        JMSProducer producer = context.createProducer();
        while (true) {
            try {
                Serializable obj = null;
                switch (PART_NAME) {
                    case 'A':
                        obj = new A(staticId++);
                        break;
                    case 'B':
                        obj = new B(staticId++);
                        break;
                    case 'C':
                        obj = new C(staticId++);
                        break;
                }
                ObjectMessage objMsg = context.createObjectMessage(obj);
                objMsg.setStringProperty("Type", String.valueOf(PART_NAME));
                producer.send(myQueue, objMsg);
                System.out.println("Sent " + obj);
                int wait = (int)((Math.random() * 3 + 3) * 1000);
                Thread.sleep(wait);
            } catch (InterruptedException | JMSException ex) {
                Logger.getLogger(Main.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
    }
}
