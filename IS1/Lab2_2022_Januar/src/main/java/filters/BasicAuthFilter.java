package filters;

import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.util.Base64;
import java.util.List;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import javax.ws.rs.container.ContainerRequestContext;
import javax.ws.rs.container.ContainerRequestFilter;
import javax.ws.rs.core.MultivaluedMap;
import javax.ws.rs.core.Response;
import javax.ws.rs.ext.Provider;
import models.Korisnik;

@Provider
public class BasicAuthFilter implements ContainerRequestFilter {
    @PersistenceContext(unitName = "mypu")
    EntityManager em;

    @Override
    public void filter(ContainerRequestContext context) throws IOException {
        context.getHeaders().getFirst("Authorization");
        MultivaluedMap<String, String> headers = context.getHeaders();
        if (!headers.containsKey("Authorization")) {
            context.abortWith(
                Response
                    .status(Response.Status.UNAUTHORIZED)
                    .entity("Korisničko ime i lozinka nisu prosleđeni.")
                    .build()
            );
            return;
        }
        List<String> authHeaders = context.getHeaders().get("Authorization");
        if (authHeaders.isEmpty()) {
            context.abortWith(
                Response
                    .status(Response.Status.UNAUTHORIZED)
                    .entity("Korisničko ime i lozinka nisu prosleđeni.")
                    .build()
            );
            return;
        }
        String[] authorization = new String(Base64.getDecoder().decode(authHeaders.get(0).replace("Basic ", "")), StandardCharsets.UTF_8).split(":");
        if (authorization.length != 2) {
            context.abortWith(
                Response
                    .status(Response.Status.BAD_REQUEST)
                    .entity("Pogrešno prosleđeno korisničko ime ili lozinka.")
                    .build()
            );
            return;            
        }
        String username = authorization[0];
        String password = authorization[1];
        List<Korisnik> korisnici = em.createNamedQuery("Korisnik.findByKorisnickoIme", Korisnik.class)
            .setParameter("korisnickoIme", username)
            .getResultList();
        if (korisnici.isEmpty() || !korisnici.get(0).getSifra().equals(password)) {
            context.abortWith(
                Response
                    .status(Response.Status.BAD_REQUEST)
                    .entity("Pogrešno korisničko ime ili lozinka.")
                    .build()
            );
            return;
        }
        // Pass headers to resources.
        Korisnik korisnik = korisnici.get(0);
        String endpoint = context
            .getUriInfo()
            .getPathSegments()
            .get(0)
            .getPath();
        if (
            (endpoint.equals("prijava") && korisnik.getStudent() == null) ||
            (endpoint.equals("admin") && korisnik.getAdmin() == null)
        ) {
            context.abortWith(
                Response
                    .status(Response.Status.FORBIDDEN)
                    .entity("Nije vam dozvoljen pristup ovom resursu.")
                    .build()
            );
            return;
        }
        context.getHeaders().add("X-User-ID", korisnik.getId().toString());
    }
}
