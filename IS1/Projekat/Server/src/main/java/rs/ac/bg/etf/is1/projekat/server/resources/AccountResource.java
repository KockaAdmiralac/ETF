package rs.ac.bg.etf.is1.projekat.server.resources;

import javax.ejb.EJB;
import javax.ejb.Stateless;
import javax.ws.rs.DELETE;
import javax.ws.rs.FormParam;
import javax.ws.rs.GET;
import javax.ws.rs.PUT;
import javax.ws.rs.Path;
import javax.ws.rs.PathParam;
import javax.ws.rs.Produces;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;
import rs.ac.bg.etf.is1.projekat.commands.CreateAccountCommand;
import rs.ac.bg.etf.is1.projekat.commands.DeleteAccountCommand;
import rs.ac.bg.etf.is1.projekat.commands.GetAccountsForClientCommand;
import rs.ac.bg.etf.is1.projekat.responses.JMSResponse;
import rs.ac.bg.etf.is1.projekat.server.JMSCommunicator;

@Stateless
@Path("account")
@Produces(MediaType.APPLICATION_JSON)
public class AccountResource {
    @EJB
    JMSCommunicator communicator;

    @GET
    @Path("{clientId}")
    public Response getClientAccounts(@PathParam("clientId") int clientId) {
        JMSResponse r = communicator.exchange(new GetAccountsForClientCommand(clientId));
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
    @PUT
    public Response createAccount(
            @FormParam("clientId") int clientId,
            @FormParam("placeId") int placeId,
            @FormParam("overdraft") int overdraft) {
        JMSResponse r = communicator.exchange(new CreateAccountCommand(clientId, placeId, overdraft));
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
    @DELETE
    @Path("{id}")
    public Response deleteAccount(@PathParam("id") int accountId) {
        JMSResponse r = communicator.exchange(new DeleteAccountCommand(accountId));
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
}
