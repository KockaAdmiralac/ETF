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
import models.Admin;
import models.Nastavnik;
import models.Ocena;
import models.Prati;
import models.Predmet;
import models.Prijava;
import models.Rok;

@Path("ocena")
@Stateless
public class OcenaResource {
    @PersistenceContext(unitName = "mypu")
    EntityManager em;
    
    @POST
    @Path("{idPrijave}")
    public Response oceni(@PathParam("idPrijave") int idPrijave, @Context HttpHeaders headers, String body) {
        // Get authenticated user.
        List<String> idHeaders = headers.getRequestHeaders().get("X-User-ID");
        if (idHeaders.size() != 1) {
            // The user may have passed our internal header in the request as
            // an attempt to identify as someone else.
            return Response
                .status(Response.Status.BAD_REQUEST)
                .entity("Zaglavlje X-User-ID je interno i ne sme se slati u zahtevima.")
                .build();
        }
        int korisnikId = Integer.parseInt(idHeaders.get(0));
        List<Prijava> prijave = em.createNamedQuery("Prijava.findById", Prijava.class)
            .setParameter("id", idPrijave)
            .getResultList();
        if (prijave.isEmpty()) {
            return Response
                .status(Response.Status.BAD_REQUEST)
                .entity("Nije validan ID prijave.")
                .build();
        }
        Prijava prijava = prijave.get(0);
        Rok rok = prijava.getRokId();
        if (!rok.getStatus().equals("T")) {
            return Response
                .status(Response.Status.BAD_REQUEST)
                .entity("Ne može se oceniti ispit u roku za koji su još uvek otvorene prijave.")
                .build();
        }
        Prati prati = prijava.getPratiId();
        Predmet predmet = prati.getPredmetId();
        List<Nastavnik> nastavnici = predmet.getNastavnikList();
        boolean found = false;
        for (Nastavnik nastavnik : nastavnici) {
            if (nastavnik.getKorisnikId() == korisnikId) {
                found = true;
                break;
            }
        }
        if (!found) {
            boolean isNotAdmin = em.createNamedQuery("Admin.findByKorisnikId", Admin.class)
                .setParameter("korisnikId", korisnikId)
                .getResultList()
                .isEmpty();
            if (isNotAdmin) {
                return Response
                    .status(Response.Status.FORBIDDEN)
                    .entity("Niste nastavnik na tom predmetu.")
                    .build();
            }
        }
        // Duplicate grades not handled.
        Ocena ocena = new Ocena();
        ocena.setOcena(Integer.parseInt(body));
        ocena.setPrijavaId(prijava);
        em.persist(ocena);
        return Response
            .noContent()
            .build();
    }
}
