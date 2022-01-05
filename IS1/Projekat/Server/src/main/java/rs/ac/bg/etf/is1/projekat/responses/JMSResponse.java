package rs.ac.bg.etf.is1.projekat.responses;

import java.io.Serializable;
import rs.ac.bg.etf.is1.projekat.commands.Command;

public abstract class JMSResponse implements Serializable {
    protected final Command cmd;
    public JMSResponse(Command cmd) {
        this.cmd = cmd;
    }
    public String getId() {
        return cmd.getId();
    }
    abstract public boolean isSuccessful();
    @Override
    public String toString() {
        return "Response[id=" + getId() + ", type=" + cmd.getType() + ", from=" + cmd.getDestination() + "]";
    }
}
