package resources;

import java.util.List;
import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import javax.ws.rs.POST;
import javax.ws.rs.Path;
import javax.ws.rs.core.Response;
import models.Admin;
import models.Korisnik;
import requests.CreateAdminRequest;

@Stateless
@Path("admin")
public class AdminResource {
    @PersistenceContext(unitName = "mypu")
    EntityManager em;

    @POST
    public Response napraviAdmina(CreateAdminRequest request) {
        if (request == null) {
            return Response
                .status(Response.Status.BAD_REQUEST)
                .entity("Podaci o novom adminu nisu ispravno prosleđeni.")
                .build();
        }
        List<Korisnik> korisnici = em
            .createNamedQuery("Korisnik.findByKorisnickoIme")
            .setParameter("korisnickoIme", request.imeKor)
            .getResultList();
        if (korisnici.stream().anyMatch(k -> k.getAdmin() != null)) {
            return Response
                .status(Response.Status.BAD_REQUEST)
                .entity("Admin sa zadatim korisničkim imenom već postoji.")
                .build();
        }
        Korisnik noviKorisnik = new Korisnik();
        noviKorisnik.setKorisnickoIme(request.imeKor);
        noviKorisnik.setSifra(request.sifra);
        em.persist(noviKorisnik);
        // We're flushing writes to the database so JPA updates our User object
        // and we can successfully obtain the new ID.
        em.flush();
        Admin noviAdmin = new Admin();
        noviAdmin.setKorisnikId(noviKorisnik.getId());
        em.persist(noviAdmin);
        return Response
            .status(Response.Status.NO_CONTENT)
            .build();
    }
}
