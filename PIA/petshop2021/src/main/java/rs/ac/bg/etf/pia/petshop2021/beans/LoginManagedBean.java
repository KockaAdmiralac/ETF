package rs.ac.bg.etf.pia.petshop2021.beans;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.inject.Named;
import javax.enterprise.context.RequestScoped;
import javax.faces.annotation.FacesConfig;
import javax.servlet.http.HttpSession;
import rs.ac.bg.etf.pia.petshop2021.util.DB;
import rs.ac.bg.etf.pia.petshop2021.util.SessionUtils;

@Named(value = "loginManagedBean")
@RequestScoped
@FacesConfig(version = FacesConfig.Version.JSF_2_3)
public class LoginManagedBean {
    private String username;
    private String password;
    private String tip;
    private String error;

    public LoginManagedBean() {}

    public String login() {
        if (username.isEmpty() || password.isEmpty() || tip.isEmpty()) {
            error = "Niste uneli sve podatke.";
            return null;
        }
        Connection conn = DB.getInstance().getConnection();
        try (PreparedStatement stmt = conn.prepareStatement("SELECT * FROM korisnici WHERE kor_ime = ? AND lozinka = ? AND tip = ?")) {
            stmt.setString(1, username);
            stmt.setString(2, password);
            stmt.setString(3, tip);
            try (ResultSet rs = stmt.executeQuery()) {
                if (rs.next()) {
                    HttpSession session = SessionUtils.getSession();
                    session.setAttribute("kor_ime", username);
                    session.setAttribute("ime", rs.getString("ime"));
                    session.setAttribute("prezime", rs.getString("prezime"));
                    session.setAttribute("datum_rodjenja", rs.getDate("datum_rodjenja").toLocalDate());
                    return tip + ".xhtml?faces-redirect=true";
                } else {
                    error = "Nije ispravno korisničko ime, lozinka ili tip.";
                    return null;
                }
            }
        } catch (SQLException ex) {
            Logger.getLogger(LoginManagedBean.class.getName()).log(Level.SEVERE, null, ex);
        } finally {
            DB.getInstance().putConnection(conn);
        }
        error = "Nepoznata greška.";
        return null;
    }
    
    public String logout() {
        HttpSession session = SessionUtils.getSession();
        session.removeAttribute("kor_ime");
        session.removeAttribute("ime");
        session.removeAttribute("prezime");
        session.removeAttribute("datum_rodjenja");
        return "index.xhtml?faces-redirect=true";
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

    public String getTip() {
        return tip;
    }

    public void setTip(String tip) {
        this.tip = tip;
    }

    public String getError() {
        return error;
    }

    public void setError(String error) {
        this.error = error;
    }
}
