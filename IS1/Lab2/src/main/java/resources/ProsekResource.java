package resources;

import java.util.List;
import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.Produces;
import javax.ws.rs.QueryParam;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;
import models.Ocena;
import models.Prati;
import models.Prijava;
import models.Student;

@Path("prosek")
@Stateless
public class ProsekResource {
    @PersistenceContext(unitName = "mypu")
    EntityManager em;

    @GET
    @Produces(MediaType.TEXT_PLAIN)
    public Response prosek(@QueryParam("idStudenta") int idStudenta) {
        List<Student> studenti = em.createNamedQuery("Student.findByKorisnikId", Student.class)
            .setParameter("korisnikId", idStudenta)
            .getResultList();
        if (studenti.isEmpty()) {
            return Response
                .status(Response.Status.BAD_REQUEST)
                .entity("Ne postoji student sa zadatim ID.")
                .build();
        }
        int sum = 0;
        int count = 0;
        double prosek = 0;
        Student student = studenti.get(0);
        for (Prati prati : student.getPratiList()) {
            int maxOcenaId = 0;
            int maxOcena = 0;
            for (Prijava prijava : prati.getPrijavaList()) {
                for (Ocena ocena : prijava.getOcenaList()) {
                    if (ocena.getOcena() > 5 && ocena.getId() > maxOcenaId) {
                        maxOcenaId = ocena.getId();
                        maxOcena = ocena.getOcena();
                    }
                }
            }
            if (maxOcena > 0) {
                sum += maxOcena;
                ++count;
            }
        }
        if (count != 0) {
            prosek = sum/count;
        }
        return Response
            .ok(prosek)
            .build();
    }
}
