package rs.ac.bg.etf.pia.fica2022.util;

import jakarta.faces.context.FacesContext;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpSession;

public class SessionUtils {

    public static HttpSession getSession() {
        return (HttpSession) FacesContext.getCurrentInstance().getExternalContext().getSession(false);
    }

    public static HttpServletRequest getRequest() {
        return (HttpServletRequest) FacesContext.getCurrentInstance().getExternalContext().getRequest();
    }

    public static Object getAttribute(String key) {
        HttpSession session = getSession();
        if (session != null) {
            return session.getAttribute(key);
        } else {
            return null;
        }
    }

    public static void setAttribute(String key, Object object) {
        HttpSession session = getSession();
        session.setAttribute(key, object);
    }

    public static void invalidate() {
        getSession().invalidate();
    }
}
