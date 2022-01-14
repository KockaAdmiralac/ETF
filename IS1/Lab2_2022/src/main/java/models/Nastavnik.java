package models;

import java.io.Serializable;
import java.util.List;
import javax.persistence.Basic;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.JoinTable;
import javax.persistence.ManyToMany;
import javax.persistence.NamedQueries;
import javax.persistence.NamedQuery;
import javax.persistence.OneToOne;
import javax.persistence.Table;
import javax.validation.constraints.NotNull;
import javax.validation.constraints.Size;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlTransient;

@Entity
@Table(name = "nastavnik")
@XmlRootElement
@NamedQueries({
    @NamedQuery(name = "Nastavnik.findAll", query = "SELECT n FROM Nastavnik n"),
    @NamedQuery(name = "Nastavnik.findByKorisnikId", query = "SELECT n FROM Nastavnik n WHERE n.korisnikId = :korisnikId"),
    @NamedQuery(name = "Nastavnik.findByImePrezime", query = "SELECT n FROM Nastavnik n WHERE n.imePrezime = :imePrezime")})
public class Nastavnik implements Serializable {

    @Size(max = 45)
    @Column(name = "ime_prezime")
    private String imePrezime;

    private static final long serialVersionUID = 1L;
    @Id
    @Basic(optional = false)
    @NotNull
    @Column(name = "korisnik_id")
    private Integer korisnikId;
    @JoinTable(name = "predaje", joinColumns = {
        @JoinColumn(name = "nastavnik_korisnik_id", referencedColumnName = "korisnik_id")}, inverseJoinColumns = {
        @JoinColumn(name = "predmet_id", referencedColumnName = "id")})
    @ManyToMany
    private List<Predmet> predmetList;
    @JoinColumn(name = "korisnik_id", referencedColumnName = "id", insertable = false, updatable = false)
    @OneToOne(optional = false)
    private Korisnik korisnik;

    public Nastavnik() {
    }

    public Nastavnik(Integer korisnikId) {
        this.korisnikId = korisnikId;
    }

    public Integer getKorisnikId() {
        return korisnikId;
    }

    public void setKorisnikId(Integer korisnikId) {
        this.korisnikId = korisnikId;
    }

    public String getImePrezime() {
        return imePrezime;
    }

    public void setImePrezime(String imePrezime) {
        this.imePrezime = imePrezime;
    }

    @XmlTransient
    public List<Predmet> getPredmetList() {
        return predmetList;
    }

    public void setPredmetList(List<Predmet> predmetList) {
        this.predmetList = predmetList;
    }

    public Korisnik getKorisnik() {
        return korisnik;
    }

    public void setKorisnik(Korisnik korisnik) {
        this.korisnik = korisnik;
    }

    @Override
    public int hashCode() {
        int hash = 0;
        hash += (korisnikId != null ? korisnikId.hashCode() : 0);
        return hash;
    }

    @Override
    public boolean equals(Object object) {
        // TODO: Warning - this method won't work in the case the id fields are not set
        if (!(object instanceof Nastavnik)) {
            return false;
        }
        Nastavnik other = (Nastavnik) object;
        if ((this.korisnikId == null && other.korisnikId != null) || (this.korisnikId != null && !this.korisnikId.equals(other.korisnikId))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "models.Nastavnik[ korisnikId=" + korisnikId + " ]";
    }
    
}
