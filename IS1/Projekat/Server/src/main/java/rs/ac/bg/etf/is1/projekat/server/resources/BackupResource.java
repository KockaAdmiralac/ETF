package rs.ac.bg.etf.is1.projekat.server.resources;

import java.util.List;
import javax.ejb.EJB;
import javax.ejb.Stateless;
import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.Produces;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;
import rs.ac.bg.etf.is1.projekat.commands.GetBackupCommand;
import rs.ac.bg.etf.is1.projekat.responses.AggregateResponse;
import rs.ac.bg.etf.is1.projekat.responses.BackupDiffResponse;
import rs.ac.bg.etf.is1.projekat.responses.JMSResponse;
import rs.ac.bg.etf.is1.projekat.responses.S1BackupResponse;
import rs.ac.bg.etf.is1.projekat.responses.S2BackupResponse;
import rs.ac.bg.etf.is1.projekat.responses.S3BackupResponse;
import rs.ac.bg.etf.is1.projekat.server.EntityComparator;
import rs.ac.bg.etf.is1.projekat.server.JMSCommunicator;

@Stateless
@Path("backup")
@Produces(MediaType.APPLICATION_JSON)
public class BackupResource {
    @EJB
    EntityComparator comparator;
    @EJB
    JMSCommunicator communicator;

    @GET
    public Response getBackup() {
        JMSResponse r = communicator.exchange(new GetBackupCommand(true));
        if (!r.isSuccessful()) {
            return Response
                .serverError()
                .entity(r)
                .build();
        }
        return Response
            .ok(r)
            .build();
    }
    @GET
    @Path("diff")
    public Response getDiff() {
        GetBackupCommand cmd = new GetBackupCommand();
        JMSResponse r = communicator.exchange(cmd);
        if (!r.isSuccessful() || !(r instanceof AggregateResponse)) {
            return Response
                .serverError()
                .entity(r)
                .build();
        }
        List<JMSResponse> responses = ((AggregateResponse)r).getResponses();
        if (
            responses.isEmpty() ||
            !(responses.get(0) instanceof S1BackupResponse) ||
            !(responses.get(1) instanceof S2BackupResponse) ||
            !(responses.get(2) instanceof S3BackupResponse)
        ) {
            return Response
                .serverError()
                .entity(r)
                .build();
        }
        S1BackupResponse r1 = (S1BackupResponse)responses.get(0);
        S2BackupResponse r2 = (S2BackupResponse)responses.get(1);
        S3BackupResponse r3 = (S3BackupResponse)responses.get(2);
        BackupDiffResponse response = new BackupDiffResponse(
            cmd,
            comparator.compare(r3.getAccounts(), r2.getAccounts(), (e1, e2) -> {
                return e1.getBalance() == e2.getBalance() &&
                       e1.getClientId() == e2.getClientId() &&
                       e1.getCreationDate().equals(e2.getCreationDate()) &&
                       e1.getOverdraft() == e2.getOverdraft() &&
                       e1.getPlaceId() == e2.getPlaceId() &&
                       e1.getTransactionCount() == e2.getTransactionCount();
            }),
            comparator.compare(r3.getClients(), r1.getClients(), (e1, e2) -> {
                return e1.getAddress().equals(e2.getAddress()) &&
                       e1.getName().equals(e2.getName()) &&
                       e1.getPlaceId() == e2.getPlaceId();
            }),
            comparator.compare(r3.getOffices(), r1.getOffices(), (e1, e2) -> {
                return e1.getAddress().equals(e2.getAddress()) &&
                       e1.getName().equals(e2.getName()) &&
                       e1.getPlaceId().equals(e2.getPlaceId());
            }),
            comparator.compare(r3.getPlaces(), r1.getPlaces(), (e1, e2) -> {
                return e1.getName().equals(e2.getName()) &&
                       e1.getPostalCode() == e2.getPostalCode();
            }),
            comparator.compare(r3.getTransactions(), r2.getTransactions(), (e1, e2) -> {
                return // e1.getAccountIdFrom().equals(e2.getAccountIdFrom()) &&
                       // e1.getAccountIdTo().equals(e2.getAccountIdFrom()) &&
                       e1.getAmount() == e2.getAmount() &&
                       // e1.getOfficeId().equals(e2.getOfficeId()) &&
                       e1.getProcessingDate().equals(e2.getProcessingDate()) &&
                       e1.getPurpose().equals(e2.getPurpose()) &&
                       e1.getTransactionNumber() == e2.getTransactionNumber() &&
                       e1.getType().equals(e2.getType());
            })
        );
        return Response
            .ok(response)
            .build();
    }
}
