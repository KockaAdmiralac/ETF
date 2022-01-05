package rs.ac.bg.etf.is1.projekat.responses;

import rs.ac.bg.etf.is1.projekat.commands.Command;

public abstract class SuccessfulResponse extends JMSResponse {
    public SuccessfulResponse(Command cmd) {
        super(cmd);
    }
    @Override
    public boolean isSuccessful() {
        return true;
    }
    @Override
    public String toString() {
        return "SuccessfulResponse[id=" + getId() + ", type=" + cmd.getType() + ", from=" + cmd.getDestination() + "]";
    }
}
