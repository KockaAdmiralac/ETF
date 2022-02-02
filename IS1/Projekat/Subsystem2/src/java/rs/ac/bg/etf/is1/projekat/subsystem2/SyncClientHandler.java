package rs.ac.bg.etf.is1.projekat.subsystem2;

import javax.persistence.EntityManager;
import rs.ac.bg.etf.is1.projekat.commands.Command;
import rs.ac.bg.etf.is1.projekat.commands.SyncClientCommand;
import rs.ac.bg.etf.is1.projekat.responses.CommandHandler;
import rs.ac.bg.etf.is1.projekat.responses.JMSResponse;
import rs.ac.bg.etf.is1.projekat.responses.OKResponse;

public class SyncClientHandler extends CommandHandler {
    public SyncClientHandler(EntityManager em) {
        super(em);
    }
    @Override
    public JMSResponse handle(Command cmd) {
        SyncClientCommand data = (SyncClientCommand) cmd;
        em.getTransaction().begin();
        em.merge(data.getClient());
        em.getTransaction().commit();
        return new OKResponse(cmd);
    }
}
