package rs.ac.bg.etf.is1.projekat.client.rest;

import java.util.UUID;

public class Response {
    public UUID id;
    public boolean successful;
    public String reason;
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("Request ID ");
        sb.append(id);
        if (successful) {
            sb.append("was successful.");
        } else {
            sb.append("was not successful. Reason: ");
            sb.append(reason);
        }
        return sb.toString();
    }
}
