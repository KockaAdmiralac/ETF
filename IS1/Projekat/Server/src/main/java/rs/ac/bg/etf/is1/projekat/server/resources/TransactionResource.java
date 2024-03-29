package rs.ac.bg.etf.is1.projekat.server.resources;

import javax.inject.Inject;
import javax.ws.rs.FormParam;
import javax.ws.rs.GET;
import javax.ws.rs.POST;
import javax.ws.rs.Path;
import javax.ws.rs.PathParam;
import javax.ws.rs.Produces;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;
import rs.ac.bg.etf.is1.projekat.commands.CreateIncomingTransactionCommand;
import rs.ac.bg.etf.is1.projekat.commands.CreateInternalTransactionCommand;
import rs.ac.bg.etf.is1.projekat.commands.CreateOutgoingTransactionCommand;
import rs.ac.bg.etf.is1.projekat.commands.GetTransactionsForAccountCommand;
import rs.ac.bg.etf.is1.projekat.responses.JMSResponse;
import rs.ac.bg.etf.is1.projekat.server.JMSCommunicator;

@Path("transaction")
@Produces(MediaType.APPLICATION_JSON)
public class TransactionResource {
    @Inject
    JMSCommunicator communicator;

    @GET
    @Path("{accountId}")
    public Response getAccountTransactions(@PathParam("accountId") int accountId) {
        JMSResponse r = communicator.exchange(new GetTransactionsForAccountCommand(accountId));
        if (!r.isSuccessful()) {
            return Response
                .status(Response.Status.NOT_FOUND)
                .entity(r)
                .build();
        }
        return Response
            .ok(r)
            .build();
    }
    @POST
    @Path("internal")
    public Response createInternalTransaction(
            @FormParam("amount") int amount,
            @FormParam("accountId") int accountId,
            @FormParam("accountIdTo") int accountIdTo,
            @FormParam("purpose") String purpose) {
        JMSResponse r = communicator.exchange(new CreateInternalTransactionCommand(amount, accountId, purpose, accountIdTo));
        if (!r.isSuccessful()) {
            return Response
                .status(Response.Status.BAD_REQUEST)
                .entity(r)
                .build();
        }
        return Response
            .ok(r)
            .build();
    }
    @POST
    @Path("incoming")
    public Response createIncomingTransaction(
            @FormParam("amount") int amount,
            @FormParam("accountId") int accountId,
            @FormParam("purpose") String purpose,
            @FormParam("officeId") int officeId) {
        JMSResponse r = communicator.exchange(new CreateIncomingTransactionCommand(amount, accountId, purpose, officeId));
        if (!r.isSuccessful()) {
            return Response
                .status(Response.Status.BAD_REQUEST)
                .entity(r)
                .build();
        }
        return Response
            .ok(r)
            .build();
    }
    @POST
    @Path("outgoing")
    public Response createOutgoingTransaction(
            @FormParam("amount") int amount,
            @FormParam("accountId") int accountId,
            @FormParam("purpose") String purpose,
            @FormParam("officeId") int officeId) {
        JMSResponse r = communicator.exchange(new CreateOutgoingTransactionCommand(amount, accountId, purpose, officeId));
        if (!r.isSuccessful()) {
            return Response
                .status(Response.Status.BAD_REQUEST)
                .entity(r)
                .build();
        }
        return Response
            .ok(r)
            .build();
    }
}
