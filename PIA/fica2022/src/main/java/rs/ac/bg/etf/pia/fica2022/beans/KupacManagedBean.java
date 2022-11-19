package rs.ac.bg.etf.pia.fica2022.beans;

import rs.ac.bg.etf.pia.fica2022.entities.Automobil;
import jakarta.annotation.PostConstruct;
import jakarta.enterprise.context.SessionScoped;
import jakarta.inject.Named;
import java.io.Serializable;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.text.ParseException;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;
import rs.ac.bg.etf.pia.fica2022.util.DB;
import rs.ac.bg.etf.pia.fica2022.util.DateUtil;
import rs.ac.bg.etf.pia.fica2022.util.SessionUtils;

@Named(value = "kmb")
@SessionScoped
public class KupacManagedBean implements Serializable {
    
    private int ponuda;
    private String marka;
    private String name;
    private String surname;
    private List<Automobil> automobili = new ArrayList<>();
    private String datum;
    private String snaga;
    private boolean tehnicki;
    private boolean polisa;
    private String error;
    private String success;
    private int idA;

    public int getPonuda() {
        return ponuda;
    }

    public void setPonuda(int ponuda) {
        this.ponuda = ponuda;
    }

    public String getMarka() {
        return marka;
    }

    public void setMarka(String marka) {
        this.marka = marka;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getSurname() {
        return surname;
    }

    public void setSurname(String surname) {
        this.surname = surname;
    }

    public List<Automobil> getAutomobili() {
        return automobili;
    }

    public void setAutomobili(List<Automobil> automobili) {
        this.automobili = automobili;
    }

    public String getDatum() {
        return datum;
    }

    public void setDatum(String datum) {
        this.datum = datum;
    }

    public String getSnaga() {
        return snaga;
    }

    public void setSnaga(String snaga) {
        this.snaga = snaga;
    }

    public boolean isTehnicki() {
        return tehnicki;
    }

    public void setTehnicki(boolean tehnicki) {
        this.tehnicki = tehnicki;
    }

    public boolean isPolisa() {
        return polisa;
    }

    public void setPolisa(boolean polisa) {
        this.polisa = polisa;
    }

    public String getError() {
        return error;
    }

    public void setError(String error) {
        this.error = error;
    }

    public String getSuccess() {
        return success;
    }

    public void setSuccess(String success) {
        this.success = success;
    }
 
    @PostConstruct
    public void retrieveData() {
        name = SessionUtils.getAttribute("name").toString();
        surname = SessionUtils.getAttribute("surname").toString();
        DB inst = DB.getInstance();
        Connection db = inst.getConnection();
        try (
            Statement stmt = db.createStatement();
            ResultSet rs = stmt.executeQuery("SELECT * FROM automobili");
        ) {
            while (rs.next()) {
                Automobil a = new Automobil();
                a.setCena(rs.getInt("cena_registracije"));
                a.setMarka(rs.getString("marka"));
                a.setId(rs.getInt("idA"));
                automobili.add(a);
            }
        } catch (SQLException ex) {
            Logger.getLogger(LoginManagedBean.class.getName()).log(Level.SEVERE, null, ex);
        } finally {
            inst.putConnection(db);
        }
    }
    
    public String calculate() {
        success = "";
        ponuda = 0;
        Automobil auto = automobili.stream().filter(a -> a.getMarka().equals(marka)).findFirst().get();
        ponuda += auto.getCena();
        try {
            Date registracija = DateUtil.stringToUtil(datum, "yyyy-MM-dd");
            Date sada = DateUtil.currentUtil();
            long diff = sada.getTime() - registracija.getTime();
            if (diff < 0) {
                error = "Datum registracije mora biti u prošlosti.";
                return null;
            }
            long godine = diff / 1000 / 60 / 60 / 24 / 365;
            if (godine > 4) {
                ponuda += 5000;
            }
            int snagaBroj = Integer.parseInt(snaga);
            if (snagaBroj < 50) {
                error = "Snaga mora biti barem 50kW.";
                return null;
            } else if (snagaBroj < 100) {
                ponuda += 3000;
            } else {
                ponuda += 6000;
            }
            if (tehnicki) {
                ponuda += 6000;
            }
            if (polisa) {
                ponuda += 10000;
            }
            idA = auto.getId();
        } catch (ParseException ex) {
            error = "Datum nije u zadatom formatu";
            return null;
        } catch (NumberFormatException ex) {
            error = "Snaga mora biti ceo broj.";
            return null;
        }
        return "ponuda.xhtml?faces-redirect=true";
    }
    
    public String accept() {
        DB inst = DB.getInstance();
        Connection db = inst.getConnection();
        try (
            PreparedStatement stmt = db.prepareStatement("INSERT INTO zahtevi (kupac, automobil, datum, iznos) VALUES (?, ?, NOW(), ?)");
        ) {
            stmt.setString(1, SessionUtils.getAttribute("username").toString());
            stmt.setInt(2, idA);
            stmt.setInt(3, ponuda);
            stmt.execute();
            error = "";
            success = "Uspešno sačuvan zahtev.";
        } catch (SQLException ex) {
            Logger.getLogger(LoginManagedBean.class.getName()).log(Level.SEVERE, null, ex);
        } finally {
            inst.putConnection(db);
        }
        marka = "";
        datum = "";
        snaga = "";
        polisa = false;
        tehnicki = false;
        return "kupac.xhtml?faces-redirect=true";
    }
    
    public String back() {
        return "kupac.xhtml?faces-redirect=true";
    }
    
}
