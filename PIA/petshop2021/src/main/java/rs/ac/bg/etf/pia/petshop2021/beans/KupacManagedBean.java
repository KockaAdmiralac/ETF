package rs.ac.bg.etf.pia.petshop2021.beans;

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
import jakarta.annotation.PostConstruct;
import jakarta.enterprise.context.SessionScoped;
import jakarta.inject.Named;
import rs.ac.bg.etf.pia.petshop2021.entities.Product;
import rs.ac.bg.etf.pia.petshop2021.util.DB;
import rs.ac.bg.etf.pia.petshop2021.util.SessionUtils;

@Named(value = "kupacManagedBean")
@SessionScoped
public class KupacManagedBean implements Serializable {
    private List<Product> allProducts;

    public KupacManagedBean() {}

    @PostConstruct
    public void initData() {
        allProducts = new ArrayList<>();
        Connection conn = DB.getInstance().getConnection();
        try (
            Statement stmt = conn.createStatement();
            ResultSet rs = stmt.executeQuery("SELECT * FROM proizvodi");
        ) {
            while (rs.next()) {
                Product p = new Product();
                p.setNaziv(rs.getString("naziv"));
                p.setOpis(rs.getString("opis"));
                p.setCena(rs.getInt("cena"));
                p.setPromocija(rs.getBoolean("promocija"));
                allProducts.add(p);
            }
        } catch (SQLException ex) {
            Logger.getLogger(LoginManagedBean.class.getName()).log(Level.SEVERE, null, ex);
        } finally {
            DB.getInstance().putConnection(conn);
        }
    }

    public void remove(Product p) {
        p.setKoliko(0);
        p.setKupiti(false);
    }
    
    public String order() {
        Connection conn = DB.getInstance().getConnection();
        try (
            PreparedStatement stmt = conn.prepareStatement("INSERT INTO narudzbine (kupac, datum) VALUES (?, NOW())", Statement.RETURN_GENERATED_KEYS);
            PreparedStatement stmt2 = conn.prepareStatement("INSERT INTO narudzbinasadrzi (narudzbina, proizvod, kolicina) VALUES (?, ?, ?)");
        ) {
            stmt.setString(1, (String) SessionUtils.getSession().getAttribute("kor_ime"));
            stmt.executeUpdate();
            try (ResultSet rs = stmt.getGeneratedKeys()) {
                if (rs.next()) {
                    stmt2.setInt(1, rs.getInt(1));
                } else {
                    return null;
                }
            }
            for (Product p : allProducts) {
                if (p.getKoliko() <= 0 || !p.isKupiti()) {
                    continue;
                }
                stmt2.setString(2, p.getNaziv());
                stmt2.setInt(3, p.getKoliko());
                stmt2.executeUpdate();
                p.setKupiti(false);
                p.setKoliko(0);
            }
        } catch (SQLException ex) {
            Logger.getLogger(KupacManagedBean.class.getName()).log(Level.SEVERE, null, ex);
        } finally {
            DB.getInstance().putConnection(conn);
        }
        return "kupac?faces-redirect=true";
    }

    public List<Product> getAllProducts() {
        return allProducts;
    }

    public void setAllProducts(List<Product> allProducts) {
        this.allProducts = allProducts;
    }
}
