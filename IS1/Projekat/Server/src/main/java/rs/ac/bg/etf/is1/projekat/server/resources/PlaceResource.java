package rs.ac.bg.etf.is1.projekat.server.resources;

import javax.inject.Inject;
import javax.ws.rs.FormParam;
import javax.ws.rs.GET;
import javax.ws.rs.POST;
import javax.ws.rs.Path;
import javax.ws.rs.Produces;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;
import rs.ac.bg.etf.is1.projekat.commands.CreatePlaceCommand;
import rs.ac.bg.etf.is1.projekat.commands.GetPlacesCommand;
import rs.ac.bg.etf.is1.projekat.responses.JMSResponse;
import rs.ac.bg.etf.is1.projekat.server.JMSCommunicator;

@Path("place")
@Produces(MediaType.APPLICATION_JSON)
public class PlaceResource {
    @Inject
    JMSCommunicator communicator;
    
    @GET
    public Response getAllPlaces() {
        JMSResponse r = communicator.exchange(new GetPlacesCommand());
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
    public Response createPlace(
            @FormParam("postalCode") int postalCode,
            @FormParam("name") String name) {
        JMSResponse r = communicator.exchange(new CreatePlaceCommand(postalCode, name));
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
