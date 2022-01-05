package rs.ac.bg.etf.is1.projekat.responses;

import rs.ac.bg.etf.is1.projekat.commands.Command;

public class FailureResponse extends JMSResponse {
    private final String reason;
    public FailureResponse(Command cmd, String reason) {
        super(cmd);
        this.reason = reason;
    }
    public String getReason() {
        return reason;
    }
    @Override
    public boolean isSuccessful() {
        return false;
    }
    @Override
    public String toString() {
        return "FailureResponse[id=" + getId() + ", type=" + cmd.getType() + ", from=" + cmd.getDestination() + ", reason=" + reason + "]";
    }
}
