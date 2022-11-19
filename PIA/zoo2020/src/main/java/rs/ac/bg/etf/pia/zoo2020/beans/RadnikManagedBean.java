package rs.ac.bg.etf.pia.zoo2020.beans;

import rs.ac.bg.etf.pia.zoo2020.entities.Predlog;
import jakarta.annotation.PostConstruct;
import jakarta.inject.Named;
import jakarta.enterprise.context.SessionScoped;
import java.io.Serializable;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;
import rs.ac.bg.etf.pia.zoo2020.util.DB;
import rs.ac.bg.etf.pia.zoo2020.util.SessionUtils;

@Named(value = "radnikManagedBean")
@SessionScoped
public class RadnikManagedBean implements Serializable {
    private List<Predlog> predlozi = new ArrayList<>();
    private String naziv;
    private String tezina;
    private int idP;
    
    @PostConstruct
    public void getData() {
        DB inst = DB.getInstance();
        Connection db = inst.getConnection();
        try (
            Statement stmt2 = db.createStatement();
            ResultSet rs2 = stmt2.executeQuery("SELECT * FROM predlozi");
            PreparedStatement stmt3 = db.prepareStatement("SELECT * FROM glasovi WHERE posetilac = ? and idP = ?");
        ) {
            while (rs2.next()) {
                Predlog p = new Predlog();
                p.setGlasovi(rs2.getInt("glasovi"));
                p.setKomentar(rs2.getString("komentar"));
                p.setPosetilac(rs2.getString("posetilac"));
                p.setZivotinja(rs2.getString("zivotinja"));
                p.setIdP(rs2.getInt("idP"));
                stmt3.setString(1, SessionUtils.getSession().getAttribute("kor_ime").toString());
                stmt3.setInt(2, rs2.getInt("idP"));
                predlozi.add(p);
            }
        } catch (SQLException ex) {
            Logger.getLogger(PosetilacManagedBean.class.getName()).log(Level.SEVERE, null, ex);
        } finally {
            inst.putConnection(db);
        }
    }
    
    public String approve(Predlog p) {
        naziv = p.getZivotinja();
        idP = p.getIdP();
        return "dodaj.xhtml?faces-redirect=true";
    }

    public String reject(Predlog p) {
        DB inst = DB.getInstance();
        Connection db = inst.getConnection();
        try (
            PreparedStatement stmt = db.prepareStatement("DELETE FROM predlozi WHERE idP = ?");
        ) {
            stmt.setInt(1, p.getIdP());
            stmt.execute();
        } catch (SQLException ex) {
            Logger.getLogger(PosetilacManagedBean.class.getName()).log(Level.SEVERE, null, ex);
        } finally {
            inst.putConnection(db);
        }
        return "radnik.xhtml?faces-redirect=true";
    }

    public String add() {
        DB inst = DB.getInstance();
        Connection db = inst.getConnection();
        try (
            PreparedStatement stmt = db.prepareStatement("INSERT INTO zivotinje (naziv, tezina) VALUES (?, ?)");
            PreparedStatement stmt2 = db.prepareStatement("UPDATE predlozi SET odobren = 1 WHERE idP = ?");
        ) {
            stmt.setString(1, naziv);
            stmt.setInt(2, Integer.parseInt(tezina));
            stmt.execute();
            stmt2.setInt(1, idP);
            stmt2.execute();
        } catch (SQLException ex) {
            Logger.getLogger(PosetilacManagedBean.class.getName()).log(Level.SEVERE, null, ex);
        } finally {
            inst.putConnection(db);
        }
        return "radnik.xhtml?faces-redirect=true";
    }
    
    public String getTezina() {
        return tezina;
    }

    public void setTezina(String tezina) {
        this.tezina = tezina;
    }

    public String getNaziv() {
        return naziv;
    }

    public void setNaziv(String naziv) {
        this.naziv = naziv;
    }

    public List<Predlog> getPredlozi() {
        return predlozi;
    }

    public void setPredlozi(List<Predlog> predlozi) {
        this.predlozi = predlozi;
    }
    
}
