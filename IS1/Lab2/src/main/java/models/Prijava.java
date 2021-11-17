package models;

import java.io.Serializable;
import java.util.List;
import javax.persistence.Basic;
import javax.persistence.CascadeType;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.ManyToOne;
import javax.persistence.NamedQueries;
import javax.persistence.NamedQuery;
import javax.persistence.OneToMany;
import javax.persistence.Table;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlTransient;

@Entity
@Table(name = "prijava")
@XmlRootElement
@NamedQueries({
    @NamedQuery(name = "Prijava.findAll", query = "SELECT p FROM Prijava p"),
    @NamedQuery(name = "Prijava.findById", query = "SELECT p FROM Prijava p WHERE p.id = :id")})
public class Prijava implements Serializable {

    private static final long serialVersionUID = 1L;
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Basic(optional = false)
    @Column(name = "id")
    private Integer id;
    @JoinColumn(name = "prati_id", referencedColumnName = "id")
    @ManyToOne(optional = false)
    private Prati pratiId;
    @JoinColumn(name = "rok_id", referencedColumnName = "id")
    @ManyToOne(optional = false)
    private Rok rokId;
    @OneToMany(cascade = CascadeType.ALL, mappedBy = "prijavaId")
    private List<Ocena> ocenaList;

    public Prijava() {
    }

    public Prijava(Integer id) {
        this.id = id;
    }

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public Prati getPratiId() {
        return pratiId;
    }

    public void setPratiId(Prati pratiId) {
        this.pratiId = pratiId;
    }

    public Rok getRokId() {
        return rokId;
    }

    public void setRokId(Rok rokId) {
        this.rokId = rokId;
    }

    @XmlTransient
    public List<Ocena> getOcenaList() {
        return ocenaList;
    }

    public void setOcenaList(List<Ocena> ocenaList) {
        this.ocenaList = ocenaList;
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
        if (!(object instanceof Prijava)) {
            return false;
        }
        Prijava other = (Prijava) object;
        if ((this.id == null && other.id != null) || (this.id != null && !this.id.equals(other.id))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "models.Prijava[ id=" + id + " ]";
    }
    
}
