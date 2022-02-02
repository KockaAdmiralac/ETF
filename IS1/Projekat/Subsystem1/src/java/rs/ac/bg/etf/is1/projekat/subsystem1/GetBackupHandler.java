package rs.ac.bg.etf.is1.projekat.subsystem1;

import java.util.List;
import javax.persistence.EntityManager;
import rs.ac.bg.etf.is1.projekat.commands.Command;
import rs.ac.bg.etf.is1.projekat.responses.CommandHandler;
import rs.ac.bg.etf.is1.projekat.responses.JMSResponse;
import rs.ac.bg.etf.is1.projekat.responses.S1BackupResponse;
import rs.ac.bg.etf.is1.projekat.tables.Client;
import rs.ac.bg.etf.is1.projekat.tables.Office;
import rs.ac.bg.etf.is1.projekat.tables.Place;

public class GetBackupHandler extends CommandHandler {
    public GetBackupHandler(EntityManager em) {
        super(em);
    }
    @Override
    public JMSResponse handle(Command cmd) {
        List<Client> clients = em.createNamedQuery("Client.findAll", Client.class).getResultList();
        List<Office> offices = em.createNamedQuery("Office.findAll", Office.class).getResultList();
        List<Place> places = em.createNamedQuery("Place.findAll", Place.class).getResultList();
        return new S1BackupResponse(cmd, clients, offices, places);
    }
}
