package resources;

import java.util.ArrayList;
import java.util.List;
import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.PathParam;
import javax.ws.rs.Produces;
import javax.ws.rs.QueryParam;
import javax.ws.rs.core.Context;
import javax.ws.rs.core.HttpHeaders;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;
import models.Predmet;
import responses.PrijavaResponse;
import responses.PrijaveResponse;

@Stateless
@Path("prijave")
public class PrijaveResource {
    @PersistenceContext(unitName = "mypu")
    EntityManager em;
    
    @GET
    @Path("{idPredmeta}")
    @Produces(MediaType.TEXT_XML)
    public Response getPrijave(@PathParam("idPredmeta") int idPredmeta, @QueryParam("idRoka") Integer idRoka, @Context HttpHeaders headers) {
        List<String> roleHeaders = headers.getRequestHeaders().get("X-User-Role");
        if (roleHeaders.size() != 1) {
            // The user may have passed our internal header in the request as
            // an attempt to identify as someone else.
            return Response
                .status(Response.Status.BAD_REQUEST)
                .entity("Zaglavlje X-User-Role je interno i ne sme se slati u zahtevima.")
                .build();
        }
        if (!roleHeaders.get(0).equals("nastavnik")) {
            return Response
                .status(Response.Status.FORBIDDEN)
                .entity("Morate biti nastavnik.")
                .build();
        }
        Predmet predmet = em.find(Predmet.class, idPredmeta);
        if (predmet == null) {
            return Response
                .status(Response.Status.BAD_REQUEST)
                .entity("Ne postoji zadati predmet.")
                .build();
        }
        List<PrijavaResponse> prijave = new ArrayList<>();
        predmet.getPratiList().forEach(prati -> {
            prati.getPrijavaList().forEach(prijava -> {
                if (idRoka != null && !prijava.getRokId().getId().equals(idRoka)) {
                    return;
                }
                prijave.add(
                    new PrijavaResponse()
                        .setImePrezimeStudenta(prati.getStudentKorisnikId().getImePrezime())
                        .setBrojIndeksaStudenta(prati.getStudentKorisnikId().getIndeks())
                        .setSifraPredmeta(predmet.getSifra())
                        .setNazivPredmeta(predmet.getNaziv())
                        .setNazivRoka(prijava.getRokId().getNaziv())
                );
            });
        });
        PrijaveResponse prijaveResponse = new PrijaveResponse();
        prijaveResponse.setPrijave(prijave);
        return Response
            .ok(prijaveResponse)
            .build();
    }
}
