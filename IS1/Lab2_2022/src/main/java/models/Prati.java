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
@Table(name = "prati")
@XmlRootElement
@NamedQueries({
    @NamedQuery(name = "Prati.findAll", query = "SELECT p FROM Prati p"),
    @NamedQuery(name = "Prati.findById", query = "SELECT p FROM Prati p WHERE p.id = :id")})
public class Prati implements Serializable {

    private static final long serialVersionUID = 1L;
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Basic(optional = false)
    @Column(name = "id")
    private Integer id;
    @OneToMany(cascade = CascadeType.ALL, mappedBy = "pratiId")
    private List<Prijava> prijavaList;
    @JoinColumn(name = "predmet_id", referencedColumnName = "id")
    @ManyToOne(optional = false)
    private Predmet predmetId;
    @JoinColumn(name = "student_korisnik_id", referencedColumnName = "korisnik_id")
    @ManyToOne(optional = false)
    private Student studentKorisnikId;

    public Prati() {
    }

    public Prati(Integer id) {
        this.id = id;
    }

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    @XmlTransient
    public List<Prijava> getPrijavaList() {
        return prijavaList;
    }

    public void setPrijavaList(List<Prijava> prijavaList) {
        this.prijavaList = prijavaList;
    }

    public Predmet getPredmetId() {
        return predmetId;
    }

    public void setPredmetId(Predmet predmetId) {
        this.predmetId = predmetId;
    }

    public Student getStudentKorisnikId() {
        return studentKorisnikId;
    }

    public void setStudentKorisnikId(Student studentKorisnikId) {
        this.studentKorisnikId = studentKorisnikId;
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
        if (!(object instanceof Prati)) {
            return false;
        }
        Prati other = (Prati) object;
        if ((this.id == null && other.id != null) || (this.id != null && !this.id.equals(other.id))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "models.Prati[ id=" + id + " ]";
    }
    
}
