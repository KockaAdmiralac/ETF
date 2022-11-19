package rs.ac.bg.etf.pia.fica2022.beans;

import rs.ac.bg.etf.pia.fica2022.entities.Zahtev;
import jakarta.annotation.PostConstruct;
import jakarta.enterprise.context.RequestScoped;
import jakarta.inject.Named;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;
import rs.ac.bg.etf.pia.fica2022.util.DB;

@Named(value = "zmb")
@RequestScoped
public class ZaposleniManagedBean {
    private List<Zahtev> requests = new ArrayList<>();

    public List<Zahtev> getRequests() {
        return requests;
    }

    public void setRequests(List<Zahtev> requests) {
        this.requests = requests;
    }

    @PostConstruct
    public void retrieveData() {
        DB inst = DB.getInstance();
        Connection db = inst.getConnection();
        try (
            Statement stmt = db.createStatement();
            ResultSet rs = stmt.executeQuery("SELECT z.datum AS datum, z.iznos AS iznos, z.kupac AS kupac, z.idZ AS id, a.marka AS marka FROM zahtevi z JOIN automobili a ON z.automobil = a.idA");
        ) {
            while (rs.next()) {
                Zahtev z = new Zahtev();
                z.setDatum(rs.getString("datum"));
                z.setIznos(rs.getInt("iznos"));
                z.setKupac(rs.getString("kupac"));
                z.setMarka(rs.getString("marka"));
                z.setId(rs.getInt("id"));
                requests.add(z);
            }
        } catch (SQLException ex) {
            Logger.getLogger(LoginManagedBean.class.getName()).log(Level.SEVERE, null, ex);
        } finally {
            inst.putConnection(db);
        }
    }
    
    public String delete(Zahtev z) {
        DB inst = DB.getInstance();
        Connection db = inst.getConnection();
        try (
            PreparedStatement stmt = db.prepareStatement("DELETE FROM zahtevi WHERE idZ = ?");
        ) {
            stmt.setInt(1, z.getId());
            stmt.execute();
        } catch (SQLException ex) {
            Logger.getLogger(LoginManagedBean.class.getName()).log(Level.SEVERE, null, ex);
        } finally {
            inst.putConnection(db);
        }
        return "zaposleni.xhtml?faces-redirect=true";
    }
}
