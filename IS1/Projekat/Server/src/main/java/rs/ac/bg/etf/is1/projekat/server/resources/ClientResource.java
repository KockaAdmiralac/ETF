package rs.ac.bg.etf.is1.projekat.server.resources;

import javax.inject.Inject;
import javax.ws.rs.FormParam;
import javax.ws.rs.GET;
import javax.ws.rs.PATCH;
import javax.ws.rs.POST;
import javax.ws.rs.Path;
import javax.ws.rs.PathParam;
import javax.ws.rs.Produces;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;
import rs.ac.bg.etf.is1.projekat.commands.CreateClientCommand;
import rs.ac.bg.etf.is1.projekat.commands.GetClientsCommand;
import rs.ac.bg.etf.is1.projekat.commands.UpdateClientCommand;
import rs.ac.bg.etf.is1.projekat.responses.JMSResponse;
import rs.ac.bg.etf.is1.projekat.server.JMSCommunicator;

@Path("client")
@Produces(MediaType.APPLICATION_JSON)
public class ClientResource {
    @Inject
    JMSCommunicator communicator;

    @GET
    public Response getAllClients() {
        JMSResponse r = communicator.exchange(new GetClientsCommand());
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
    @POST
    public Response createClient(
            @FormParam("name") String name,
            @FormParam("address") String address,
            @FormParam("placeId") int placeId) {
        JMSResponse r = communicator.exchange(new CreateClientCommand(name, address, placeId));
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
    @PATCH
    @Path("{id}")
    public Response updateClient(
            @PathParam("id") int clientId,
            @FormParam("placeId") int placeId) {
        JMSResponse r = communicator.exchange(new UpdateClientCommand(clientId, placeId));
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
