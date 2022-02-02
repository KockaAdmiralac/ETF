package rs.ac.bg.etf.is1.projekat.tables;

import java.io.Serializable;
import javax.persistence.Basic;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.NamedQueries;
import javax.persistence.NamedQuery;
import javax.persistence.Table;
import javax.validation.constraints.NotNull;
import javax.validation.constraints.Size;

@Entity
@Table(name = "place")
@NamedQueries({
    @NamedQuery(name = "Place.findAll", query = "SELECT p FROM Place p"),
    @NamedQuery(name = "Place.findById", query = "SELECT p FROM Place p WHERE p.id = :id"),
    @NamedQuery(name = "Place.findByPostalCode", query = "SELECT p FROM Place p WHERE p.postalCode = :postalCode"),
    @NamedQuery(name = "Place.findByName", query = "SELECT p FROM Place p WHERE p.name = :name")})
public class Place implements Serializable {

    private static final long serialVersionUID = 1L;
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Basic(optional = false)
    @Column(name = "id")
    private Integer id;
    @Basic(optional = false)
    @NotNull
    @Column(name = "postal_code")
    private int postalCode;
    @Basic(optional = false)
    @NotNull
    @Size(min = 1, max = 255)
    @Column(name = "name")
    private String name;

    public Place() {
    }

    public Place(Integer id) {
        this.id = id;
    }

    public Place(Integer id, int postalCode, String name) {
        this.id = id;
        this.postalCode = postalCode;
        this.name = name;
    }

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public int getPostalCode() {
        return postalCode;
    }

    public void setPostalCode(int postalCode) {
        this.postalCode = postalCode;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    @Override
    public int hashCode() {
        int hash = 0;
        hash += (id != null ? id.hashCode() : 0);
        return hash;
    }

    @Override
    public boolean equals(Object object) {
        // TODO: Warning - this method won't work in the case the id fields are not set
        if (!(object instanceof Place)) {
            return false;
        }
        Place other = (Place) object;
        if ((this.id == null && other.id != null) || (this.id != null && !this.id.equals(other.id))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "rs.ac.bg.etf.is1.projekat.tables.Place[ id=" + id + " ]";
    }
    
}
