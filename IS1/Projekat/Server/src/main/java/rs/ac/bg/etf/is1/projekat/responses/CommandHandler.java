package rs.ac.bg.etf.is1.projekat.responses;

import javax.persistence.EntityManager;
import rs.ac.bg.etf.is1.projekat.commands.Command;

public abstract class CommandHandler {
    protected final EntityManager em;
    public CommandHandler(EntityManager em) {
        this.em = em;
    }
    abstract public JMSResponse handle(Command cmd);
}
