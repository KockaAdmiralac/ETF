/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package models;

import java.io.Serializable;
import java.util.List;
import javax.persistence.Basic;
import javax.persistence.CascadeType;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.NamedQueries;
import javax.persistence.NamedQuery;
import javax.persistence.OneToMany;
import javax.persistence.OneToOne;
import javax.persistence.Table;
import javax.validation.constraints.NotNull;
import javax.validation.constraints.Size;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlTransient;

/**
 *
 * @author perapisar
 */
@Entity
@Table(name = "student")
@XmlRootElement
@NamedQueries({
    @NamedQuery(name = "Student.findAll", query = "SELECT s FROM Student s"),
    @NamedQuery(name = "Student.findByKorisnikId", query = "SELECT s FROM Student s WHERE s.korisnikId = :korisnikId"),
    @NamedQuery(name = "Student.findByIndeks", query = "SELECT s FROM Student s WHERE s.indeks = :indeks"),
    @NamedQuery(name = "Student.findByImePrezime", query = "SELECT s FROM Student s WHERE s.imePrezime = :imePrezime"),
    @NamedQuery(name = "Student.findByGodina", query = "SELECT s FROM Student s WHERE s.godina = :godina")})
public class Student implements Serializable {

    private static final long serialVersionUID = 1L;
    @Id
    @Basic(optional = false)
    @NotNull
    @Column(name = "korisnik_id")
    private Integer korisnikId;
    @Size(max = 45)
    @Column(name = "indeks")
    private String indeks;
    @Basic(optional = false)
    @NotNull
    @Size(min = 1, max = 45)
    @Column(name = "ime_prezime")
    private String imePrezime;
    @Column(name = "godina")
    private Integer godina;
    @JoinColumn(name = "korisnik_id", referencedColumnName = "id", insertable = false, updatable = false)
    @OneToOne(optional = false)
    private Korisnik korisnik;
    @OneToMany(cascade = CascadeType.ALL, mappedBy = "studentKorisnikId")
    private List<Prati> pratiList;

    public Student() {
    }

    public Student(Integer korisnikId) {
        this.korisnikId = korisnikId;
    }

    public Student(Integer korisnikId, String imePrezime) {
        this.korisnikId = korisnikId;
        this.imePrezime = imePrezime;
    }

    public Integer getKorisnikId() {
        return korisnikId;
    }

    public void setKorisnikId(Integer korisnikId) {
        this.korisnikId = korisnikId;
    }

    public String getIndeks() {
        return indeks;
    }

    public void setIndeks(String indeks) {
        this.indeks = indeks;
    }

    public String getImePrezime() {
        return imePrezime;
    }

    public void setImePrezime(String imePrezime) {
        this.imePrezime = imePrezime;
    }

    public Integer getGodina() {
        return godina;
    }

    public void setGodina(Integer godina) {
        this.godina = godina;
    }

    public Korisnik getKorisnik() {
        return korisnik;
    }

    public void setKorisnik(Korisnik korisnik) {
        this.korisnik = korisnik;
    }

    @XmlTransient
    public List<Prati> getPratiList() {
        return pratiList;
    }

    public void setPratiList(List<Prati> pratiList) {
        this.pratiList = pratiList;
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
        if (!(object instanceof Student)) {
            return false;
        }
        Student other = (Student) object;
        if ((this.korisnikId == null && other.korisnikId != null) || (this.korisnikId != null && !this.korisnikId.equals(other.korisnikId))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "models.Student[ korisnikId=" + korisnikId + " ]";
    }
    
}
