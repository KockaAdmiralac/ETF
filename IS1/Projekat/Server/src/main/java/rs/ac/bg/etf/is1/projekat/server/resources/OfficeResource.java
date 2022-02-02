package rs.ac.bg.etf.is1.projekat.server.resources;

import javax.inject.Inject;
import javax.ws.rs.FormParam;
import javax.ws.rs.GET;
import javax.ws.rs.POST;
import javax.ws.rs.Path;
import javax.ws.rs.Produces;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;
import rs.ac.bg.etf.is1.projekat.commands.CreateOfficeCommand;
import rs.ac.bg.etf.is1.projekat.commands.GetOfficesCommand;
import rs.ac.bg.etf.is1.projekat.responses.JMSResponse;
import rs.ac.bg.etf.is1.projekat.server.JMSCommunicator;

@Path("office")
@Produces(MediaType.APPLICATION_JSON)
public class OfficeResource {
    @Inject
    JMSCommunicator communicator;

    @GET
    public Response getAllOffices() {
        JMSResponse r = communicator.exchange(new GetOfficesCommand());
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
    public Response createOffice(
            @FormParam("name") String name,
            @FormParam("address") String address,
            @FormParam("placeId") int placeId) {
        JMSResponse r = communicator.exchange(new CreateOfficeCommand(name, address, placeId));
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
