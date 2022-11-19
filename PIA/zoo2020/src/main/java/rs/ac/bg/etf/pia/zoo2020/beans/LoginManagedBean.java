package rs.ac.bg.etf.pia.zoo2020.beans;

import jakarta.enterprise.context.RequestScoped;
import jakarta.inject.Named;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.logging.Level;
import java.util.logging.Logger;
import rs.ac.bg.etf.pia.zoo2020.util.DB;
import rs.ac.bg.etf.pia.zoo2020.util.SessionUtils;

@Named(value = "loginManagedBean")
@RequestScoped
public class LoginManagedBean {
    private String username;
    private String password;
    private String group;
    private String error;
    
    public String login() {
        if (username.isEmpty() || password.isEmpty() || group.isEmpty()) {
            error = "Niste uneli sve podatke.";
            return null;
        }
        DB inst = DB.getInstance();
        Connection db = inst.getConnection();
        try (PreparedStatement stmt = db.prepareStatement("SELECT ime, prezime FROM korisnici WHERE kor_ime = ? AND lozinka = ? AND tip = ?")) {
            stmt.setString(1, username);
            stmt.setString(2, password);
            stmt.setString(3, group);
            try (ResultSet rs = stmt.executeQuery()) {
                if (rs.next()) {
                    SessionUtils.getSession().setAttribute("kor_ime", username);
                    return group + ".xhtml?faces-redirect=true";
                } else {
                    error = "Pogrešno korisničko ime, lozinka ili grupa.";
                    return null;
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
        SessionUtils.getSession().removeAttribute("kor_ime");
        return "index.xhtml?faces-redirect=true";
    }
    
    public String getError() {
        return error;
    }

    public void setError(String error) {
        this.error = error;
    }

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

}
