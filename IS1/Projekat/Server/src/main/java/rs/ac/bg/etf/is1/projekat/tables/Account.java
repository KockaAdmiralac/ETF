package rs.ac.bg.etf.is1.projekat.tables;

import java.io.Serializable;
import java.util.Date;
import java.util.List;
import javax.json.bind.annotation.JsonbTransient;
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
import javax.persistence.Temporal;
import javax.persistence.TemporalType;
import javax.validation.constraints.NotNull;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlTransient;

@Entity
@Table(name = "account")
@XmlRootElement
@NamedQueries({
    @NamedQuery(name = "Account.findAll", query = "SELECT a FROM Account a"),
    @NamedQuery(name = "Account.findById", query = "SELECT a FROM Account a WHERE a.id = :id"),
    @NamedQuery(name = "Account.findByBalance", query = "SELECT a FROM Account a WHERE a.balance = :balance"),
    @NamedQuery(name = "Account.findByOverdraft", query = "SELECT a FROM Account a WHERE a.overdraft = :overdraft"),
    @NamedQuery(name = "Account.findByCreationDate", query = "SELECT a FROM Account a WHERE a.creationDate = :creationDate"),
    @NamedQuery(name = "Account.findByTransactionCount", query = "SELECT a FROM Account a WHERE a.transactionCount = :transactionCount"),
    @NamedQuery(name = "Account.findByPlaceId", query = "SELECT a FROM Account a WHERE a.placeId = :placeId"),
    @NamedQuery(name = "Account.findByClientId", query = "SELECT a FROM Account a WHERE a.clientId = :clientId")})
public class Account implements Serializable {
    public enum Status {
        ACTIVE,
        BLOCKED
    };
    
    private static final long serialVersionUID = 1L;
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Basic(optional = false)
    @Column(name = "id")
    private Integer id;
    @Basic(optional = false)
    @NotNull
    @Column(name = "balance")
    private int balance = 0;
    @Basic(optional = false)
    @NotNull
    @Column(name = "overdraft")
    private int overdraft;
    @Basic(optional = false)
    @NotNull
    @Column(name = "creation_date")
    @Temporal(TemporalType.TIMESTAMP)
    private Date creationDate = new Date();
    @Basic(optional = false)
    @NotNull
    @Column(name = "transaction_count")
    private int transactionCount = 0;
    @Basic(optional = false)
    @NotNull
    @Column(name = "place_id")
    private int placeId;
    @Basic(optional = false)
    @NotNull
    @Column(name = "client_id")
    private int clientId;
    @OneToMany(cascade = CascadeType.ALL, mappedBy = "accountIdFrom")
    @XmlTransient
    @JsonbTransient
    private List<Transaction> transactionList;
    @OneToMany(cascade = CascadeType.ALL, mappedBy = "accountIdTo")
    @XmlTransient
    @JsonbTransient
    private List<Transaction> transactionList1;

    public Account() {
    }

    public Account(Integer id) {
        this.id = id;
    }

    public Account(Integer id, int balance, int overdraft, Date creationDate, int transactionCount, int placeId) {
        this.id = id;
        this.balance = balance;
        this.overdraft = overdraft;
        this.creationDate = creationDate;
        this.transactionCount = transactionCount;
        this.placeId = placeId;
    }

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public int getBalance() {
        return balance;
    }

    public void setBalance(int balance) {
        this.balance = balance;
    }

    public int getOverdraft() {
        return overdraft;
    }

    public void setOverdraft(int overdraft) {
        this.overdraft = overdraft;
    }

    public Date getCreationDate() {
        return creationDate;
    }

    public void setCreationDate(Date creationDate) {
        this.creationDate = creationDate;
    }

    public int getTransactionCount() {
        return transactionCount;
    }

    public void setTransactionCount(int transactionCount) {
        this.transactionCount = transactionCount;
    }

    public int getPlaceId() {
        return placeId;
    }

    public void setPlaceId(int placeId) {
        this.placeId = placeId;
    }

    public int getClientId() {
        return clientId;
    }

    public void setClientId(int clientId) {
        this.clientId = clientId;
    }

    @XmlTransient
    @JsonbTransient
    public List<Transaction> getTransactionList() {
        return transactionList;
    }

    public void setTransactionList(List<Transaction> transactionList) {
        this.transactionList = transactionList;
    }
    
    public Status getStatus() {
        if (balance <= -overdraft) {
            return Status.BLOCKED;
        }
        return Status.ACTIVE;
    }

    @XmlTransient
    @JsonbTransient
    public List<Transaction> getTransactionList1() {
        return transactionList1;
    }

    public void setTransactionList1(List<Transaction> transactionList1) {
        this.transactionList1 = transactionList1;
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
        if (!(object instanceof Account)) {
            return false;
        }
        Account other = (Account) object;
        if ((this.id == null && other.id != null) || (this.id != null && !this.id.equals(other.id))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "rs.ac.bg.etf.is1.projekat.tables.Account[ id=" + id + " ]";
    }
    
}
