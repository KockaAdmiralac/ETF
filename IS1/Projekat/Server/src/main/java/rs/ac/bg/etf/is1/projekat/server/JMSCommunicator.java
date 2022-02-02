package rs.ac.bg.etf.is1.projekat.server;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.annotation.Resource;
import javax.inject.Singleton;
import javax.jms.ConnectionFactory;
import javax.jms.JMSConsumer;
import javax.jms.JMSContext;
import javax.jms.JMSException;
import javax.jms.JMSProducer;
import javax.jms.Message;
import javax.jms.ObjectMessage;
import javax.jms.Queue;
import rs.ac.bg.etf.is1.projekat.commands.Command;
import rs.ac.bg.etf.is1.projekat.responses.AggregateResponse;
import rs.ac.bg.etf.is1.projekat.responses.FailureResponse;
import rs.ac.bg.etf.is1.projekat.responses.JMSResponse;

@Singleton
public class JMSCommunicator {
    @Resource(lookup="jms/__defaultConnectionFactory")
    private ConnectionFactory connectionFactory;

    @Resource(lookup="s1Queue")
    private Queue s1Queue;

    @Resource(lookup="s2Queue")
    private Queue s2Queue;

    @Resource(lookup="s3Queue")
    private Queue s3Queue;

    @Resource(lookup="serverQueue")
    private Queue serverQueue;
    
    private Queue[] getQueuesForDestination(Command.Destination destination) {
        switch (destination) {
            case S1: return new Queue[] {s1Queue};
            case S2: return new Queue[] {s2Queue};
            case S3: return new Queue[] {s3Queue};
            case ALL: return new Queue[] {s1Queue, s2Queue, s3Queue};
        }
        return new Queue[] {};
    }
    public JMSResponse exchange(Command cmd) {
        List<JMSResponse> responses = new ArrayList<>();
        try (JMSContext context = connectionFactory.createContext()) {
            for (Queue q : getQueuesForDestination(cmd.getDestination())) {
                ObjectMessage objMsg = context.createObjectMessage(cmd);
                try (JMSConsumer consumer = context.createConsumer(serverQueue, "JMSCorrelationID = '" + cmd.getId() + "'")) {
                    objMsg.setJMSReplyTo(serverQueue);
                    objMsg.setJMSCorrelationID(String.valueOf(cmd.getId()));
                    System.out.println("JMSCommunicator sending " + cmd);
                    JMSProducer producer = context.createProducer();
                    producer.send(q, objMsg);
                    // 5 seconds because I can't be bothered to change the
                    // default timeout in Retrofit lol
                    Message recvMsg = consumer.receive(5000);
                    if (!(recvMsg instanceof ObjectMessage)) {
                        System.err.println("Received message is not an ObjectMessage: " + recvMsg);
                        continue;
                    }
                    Serializable obj = ((ObjectMessage)recvMsg).getObject();
                    if (!(obj instanceof JMSResponse)) {
                        System.err.println("Response is not a JMSResponse: " + obj);
                        continue;
                    }
                    System.out.println("Response: " + obj);
                    responses.add((JMSResponse)obj);
                } catch (JMSException ex) {
                    Logger.getLogger(JMSCommunicator.class.getName()).log(Level.SEVERE, null, ex);
                }
            }
        }
        if (responses.isEmpty()) {
            return new FailureResponse(cmd, "No responses.");
        }
        if (responses.size() == 1) {
            return responses.get(0);
        }
        return new AggregateResponse(cmd, responses);
    }
}
