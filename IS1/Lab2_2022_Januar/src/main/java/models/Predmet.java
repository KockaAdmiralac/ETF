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
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.ManyToMany;
import javax.persistence.ManyToOne;
import javax.persistence.NamedQueries;
import javax.persistence.NamedQuery;
import javax.persistence.OneToMany;
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
@Table(name = "predmet")
@XmlRootElement
@NamedQueries({
    @NamedQuery(name = "Predmet.findAll", query = "SELECT p FROM Predmet p"),
    @NamedQuery(name = "Predmet.findById", query = "SELECT p FROM Predmet p WHERE p.id = :id"),
    @NamedQuery(name = "Predmet.findBySifra", query = "SELECT p FROM Predmet p WHERE p.sifra = :sifra"),
    @NamedQuery(name = "Predmet.findByNaziv", query = "SELECT p FROM Predmet p WHERE p.naziv = :naziv"),
    @NamedQuery(name = "Predmet.findByGodina", query = "SELECT p FROM Predmet p WHERE p.godina = :godina")})
public class Predmet implements Serializable {

    private static final long serialVersionUID = 1L;
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Basic(optional = false)
    @Column(name = "id")
    private Integer id;
    @Basic(optional = false)
    @NotNull
    @Size(min = 1, max = 45)
    @Column(name = "sifra")
    private String sifra;
    @Basic(optional = false)
    @NotNull
    @Size(min = 1, max = 45)
    @Column(name = "naziv")
    private String naziv;
    @Column(name = "godina")
    private Integer godina;
    @ManyToMany(mappedBy = "predmetList")
    private List<Nastavnik> nastavnikList;
    @OneToMany(cascade = CascadeType.ALL, mappedBy = "predmetId")
    private List<Prati> pratiList;
    @JoinColumn(name = "semestar_id", referencedColumnName = "id")
    @ManyToOne(optional = false)
    private Semestar semestarId;

    public Predmet() {
    }

    public Predmet(Integer id) {
        this.id = id;
    }

    public Predmet(Integer id, String sifra, String naziv) {
        this.id = id;
        this.sifra = sifra;
        this.naziv = naziv;
    }

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public String getSifra() {
        return sifra;
    }

    public void setSifra(String sifra) {
        this.sifra = sifra;
    }

    public String getNaziv() {
        return naziv;
    }

    public void setNaziv(String naziv) {
        this.naziv = naziv;
    }

    public Integer getGodina() {
        return godina;
    }

    public void setGodina(Integer godina) {
        this.godina = godina;
    }

    @XmlTransient
    public List<Nastavnik> getNastavnikList() {
        return nastavnikList;
    }

    public void setNastavnikList(List<Nastavnik> nastavnikList) {
        this.nastavnikList = nastavnikList;
    }

    @XmlTransient
    public List<Prati> getPratiList() {
        return pratiList;
    }

    public void setPratiList(List<Prati> pratiList) {
        this.pratiList = pratiList;
    }

    public Semestar getSemestarId() {
        return semestarId;
    }

    public void setSemestarId(Semestar semestarId) {
        this.semestarId = semestarId;
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
        if (!(object instanceof Predmet)) {
            return false;
        }
        Predmet other = (Predmet) object;
        if ((this.id == null && other.id != null) || (this.id != null && !this.id.equals(other.id))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "models.Predmet[ id=" + id + " ]";
    }
    
}
