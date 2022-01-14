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
import javax.persistence.NamedQueries;
import javax.persistence.NamedQuery;
import javax.persistence.OneToMany;
import javax.persistence.Table;
import javax.validation.constraints.NotNull;
import javax.validation.constraints.Size;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlTransient;

@Entity
@Table(name = "semestar")
@XmlRootElement
@NamedQueries({
    @NamedQuery(name = "Semestar.findAll", query = "SELECT s FROM Semestar s"),
    @NamedQuery(name = "Semestar.findById", query = "SELECT s FROM Semestar s WHERE s.id = :id"),
    @NamedQuery(name = "Semestar.findByNaziv", query = "SELECT s FROM Semestar s WHERE s.naziv = :naziv"),
    @NamedQuery(name = "Semestar.findByStatus", query = "SELECT s FROM Semestar s WHERE s.status = :status")})
public class Semestar implements Serializable {

    @Basic(optional = false)
    @NotNull
    @Size(min = 1, max = 45)
    @Column(name = "naziv")
    private String naziv;
    @Size(max = 1)
    @Column(name = "status")
    private String status;

    private static final long serialVersionUID = 1L;
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Basic(optional = false)
    @Column(name = "id")
    private Integer id;
    @OneToMany(cascade = CascadeType.ALL, mappedBy = "semestarId")
    private List<Predmet> predmetList;
    @OneToMany(cascade = CascadeType.ALL, mappedBy = "semestarId")
    private List<Rok> rokList;

    public Semestar() {
    }

    public Semestar(Integer id) {
        this.id = id;
    }

    public Semestar(Integer id, String naziv) {
        this.id = id;
        this.naziv = naziv;
    }

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }


    @XmlTransient
    public List<Predmet> getPredmetList() {
        return predmetList;
    }

    public void setPredmetList(List<Predmet> predmetList) {
        this.predmetList = predmetList;
    }

    @XmlTransient
    public List<Rok> getRokList() {
        return rokList;
    }

    public void setRokList(List<Rok> rokList) {
        this.rokList = rokList;
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
        if (!(object instanceof Semestar)) {
            return false;
        }
        Semestar other = (Semestar) object;
        if ((this.id == null && other.id != null) || (this.id != null && !this.id.equals(other.id))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "models.Semestar[ id=" + id + " ]";
    }

    public String getNaziv() {
        return naziv;
    }

    public void setNaziv(String naziv) {
        this.naziv = naziv;
    }

    public String getStatus() {
        return status;
    }

    public void setStatus(String status) {
        this.status = status;
    }
    
}
