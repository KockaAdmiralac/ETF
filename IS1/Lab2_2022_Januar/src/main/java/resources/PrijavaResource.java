package resources;

import java.util.List;
import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import javax.ws.rs.POST;
import javax.ws.rs.Path;
import javax.ws.rs.PathParam;
import javax.ws.rs.core.Context;
import javax.ws.rs.core.HttpHeaders;
import javax.ws.rs.core.Response;
import models.Prati;
import models.Predmet;
import models.Prijava;
import models.Rok;

@Stateless
@Path("prijava")
public class PrijavaResource {
    @PersistenceContext(unitName = "mypu")
    EntityManager em;
    
    @POST
    @Path("{idPredmeta}")
    public Response prijavi(@PathParam("idPredmeta") int idPredmeta, @Context HttpHeaders headers) {
        List<String> idHeaders = headers.getRequestHeaders().get("X-User-ID");
        if (idHeaders.size() != 1) {
            // The user may have passed our internal header in the request as
            // an attempt to identify as someone else.
            return Response
                .status(Response.Status.BAD_REQUEST)
                .entity("Zaglavlje X-User-ID je interno i ne sme se slati u zahtevima.")
                .build();
        }
        List<Rok> rokovi = em
            .createNamedQuery("Rok.findByStatus")
            .setParameter("status", "P")
            .getResultList();
        if (rokovi.isEmpty()) {
            return Response
                .status(Response.Status.BAD_REQUEST)
                .entity("Prijava nije u toku.")
                .build();
        }
        Rok rok = rokovi.get(0);
        int idStudenta = Integer.parseInt(idHeaders.get(0));
        Predmet predmet = em.find(Predmet.class, idPredmeta);
        if (predmet == null) {
            return Response
                .status(Response.Status.BAD_REQUEST)
                .entity("Ne postoji zadati predmet.")
                .build();
        }
        Prati prati = null;
        for (Prati p : predmet.getPratiList()) {
            if (p.getStudentKorisnikId().getKorisnikId() == idStudenta) {
                prati = p;
                break;
            }
        }
        if (prati == null) {
            return Response
                .status(Response.Status.BAD_REQUEST)
                .entity("Student ne prati predmet.")
                .build();
        }
        if (!predmet.getSemestarId().equals(rok.getSemestarId())) {
            return Response
                .status(Response.Status.BAD_REQUEST)
                .entity("Predmet i rok nisu u istom semestru.")
                .build();
        }
        for (Prijava prijava : prati.getPrijavaList()) {
            if (prijava.getRokId().equals(rok)) {
                return Response
                    .status(Response.Status.BAD_REQUEST)
                    .entity("Student je već prijavljen.")
                    .build();
            }
        }
        Prijava prijava = new Prijava();
        prijava.setPratiId(prati);
        prijava.setRokId(rok);
        em.persist(prijava);
        return Response.noContent().build();
    }
}
