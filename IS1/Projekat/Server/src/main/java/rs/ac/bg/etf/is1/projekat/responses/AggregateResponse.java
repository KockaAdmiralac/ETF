package rs.ac.bg.etf.is1.projekat.responses;

import java.util.List;
import rs.ac.bg.etf.is1.projekat.commands.Command;

public class AggregateResponse extends JMSResponse {
    private final List<JMSResponse> responses;
    public AggregateResponse(Command cmd, List<JMSResponse> responses) {
        super(cmd);
        this.responses = responses;
    }
    public List<JMSResponse> getResponses() {
        return responses;
    }
    @Override
    public boolean isSuccessful() {
        return responses.stream().noneMatch(r -> !r.isSuccessful());
    }
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("AggregateResponse[");
        for (int i = 0; i < responses.size(); ++i) {
            sb.append(i);
            sb.append("=");
            sb.append(responses.get(i));
            if (i != responses.size() - 1) {
                sb.append(", ");
            }
        }
        sb.append("]");
        return sb.toString();
    }
}
