package rs.ac.bg.etf.pia.fica2022.beans;

import jakarta.inject.Named;
import jakarta.enterprise.context.RequestScoped;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.logging.Level;
import java.util.logging.Logger;
import rs.ac.bg.etf.pia.fica2022.util.DB;
import rs.ac.bg.etf.pia.fica2022.util.SessionUtils;

@Named(value = "lmb")
@RequestScoped
public class LoginManagedBean {
    private String username;
    private String password;
    private String group;
    private String error;

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public String getGroup() {
        return group;
    }

    public void setGroup(String group) {
        this.group = group;
    }

    public String getError() {
        return error;
    }

    public void setError(String error) {
        this.error = error;
    }
    
    public String login() {
        if (username.isEmpty() || password.isEmpty() || group.isEmpty()) {
            error = "Potrebno je uneti sve podatke.";
            return null;
        }
        DB inst = DB.getInstance();
        Connection db = inst.getConnection();
        try (
            PreparedStatement stmt = db.prepareStatement("SELECT * FROM korisnici WHERE korisnicko_ime = ? AND lozinka = ? AND tip = ?");
        ) {
            stmt.setString(1, username);
            stmt.setString(2, password);
            stmt.setString(3, group);
            try (ResultSet rs = stmt.executeQuery()) {
                if (rs.next()) {
                    SessionUtils.setAttribute("username", username);
                    SessionUtils.setAttribute("name", rs.getString("ime"));
                    SessionUtils.setAttribute("surname", rs.getString("prezime"));
                    return group + ".xhtml?faces-redirect=true";
                } else {
                    error = "Korisničko ime, lozinka ili tip nisu tačno uneti.";
                }
            }
        } catch (SQLException ex) {
            Logger.getLogger(LoginManagedBean.class.getName()).log(Level.SEVERE, null, ex);
        } finally {
            inst.putConnection(db);
        }
        return null;
    }
    
    public String logout() {
        SessionUtils.getSession().removeAttribute("username");
        SessionUtils.getSession().removeAttribute("name");
        SessionUtils.getSession().removeAttribute("surname");
        return "index.xhtml?faces-redirect=true";
    }
    
}
