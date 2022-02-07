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
@Table(name = "rok")
@XmlRootElement
@NamedQueries({
    @NamedQuery(name = "Rok.findAll", query = "SELECT r FROM Rok r"),
    @NamedQuery(name = "Rok.findById", query = "SELECT r FROM Rok r WHERE r.id = :id"),
    @NamedQuery(name = "Rok.findByNaziv", query = "SELECT r FROM Rok r WHERE r.naziv = :naziv"),
    @NamedQuery(name = "Rok.findByStatus", query = "SELECT r FROM Rok r WHERE r.status = :status")})
public class Rok implements Serializable {

    private static final long serialVersionUID = 1L;
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Basic(optional = false)
    @Column(name = "id")
    private Integer id;
    @Basic(optional = false)
    @NotNull
    @Size(min = 1, max = 45)
    @Column(name = "naziv")
    private String naziv;
    @Size(max = 1)
    @Column(name = "status")
    private String status;
    @OneToMany(cascade = CascadeType.ALL, mappedBy = "rokId")
    private List<Prijava> prijavaList;
    @JoinColumn(name = "semestar_id", referencedColumnName = "id")
    @ManyToOne(optional = false)
    private Semestar semestarId;

    public Rok() {
    }

    public Rok(Integer id) {
        this.id = id;
    }

    public Rok(Integer id, String naziv) {
        this.id = id;
        this.naziv = naziv;
    }

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
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

    @XmlTransient
    public List<Prijava> getPrijavaList() {
        return prijavaList;
    }

    public void setPrijavaList(List<Prijava> prijavaList) {
        this.prijavaList = prijavaList;
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
        if (!(object instanceof Rok)) {
            return false;
        }
        Rok other = (Rok) object;
        if ((this.id == null && other.id != null) || (this.id != null && !this.id.equals(other.id))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "models.Rok[ id=" + id + " ]";
    }
    
}
