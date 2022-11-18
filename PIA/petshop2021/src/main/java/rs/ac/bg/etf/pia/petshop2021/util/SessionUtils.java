package rs.ac.bg.etf.pia.petshop2021.util;

import jakarta.faces.context.FacesContext;
import jakarta.servlet.http.HttpSession;

public class SessionUtils {
    public static HttpSession getSession() {
        return (HttpSession) FacesContext.getCurrentInstance().getExternalContext().getSession(false);
    }
}
