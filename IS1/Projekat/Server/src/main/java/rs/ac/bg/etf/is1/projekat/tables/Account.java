package rs.ac.bg.etf.is1.projekat.tables;

import java.io.Serializable;
import java.util.Date;
import javax.persistence.Basic;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.NamedQueries;
import javax.persistence.NamedQuery;
import javax.persistence.Table;
import javax.persistence.Temporal;
import javax.persistence.TemporalType;
import javax.validation.constraints.NotNull;
import javax.validation.constraints.Size;

@Entity
@Table(name = "account")
@NamedQueries({
    @NamedQuery(name = "Account.findAll", query = "SELECT a FROM Account a"),
    @NamedQuery(name = "Account.findById", query = "SELECT a FROM Account a WHERE a.id = :id AND a.status != 'closed'"),
    @NamedQuery(name = "Account.findByBalance", query = "SELECT a FROM Account a WHERE a.balance = :balance AND a.status != 'closed'"),
    @NamedQuery(name = "Account.findByOverdraft", query = "SELECT a FROM Account a WHERE a.overdraft = :overdraft AND a.status != 'closed'"),
    @NamedQuery(name = "Account.findByCreationDate", query = "SELECT a FROM Account a WHERE a.creationDate = :creationDate AND a.status != 'closed'"),
    @NamedQuery(name = "Account.findByTransactionCount", query = "SELECT a FROM Account a WHERE a.transactionCount = :transactionCount AND a.status != 'closed'"),
    @NamedQuery(name = "Account.findByPlaceId", query = "SELECT a FROM Account a WHERE a.placeId = :placeId AND a.status != 'closed'"),
    @NamedQuery(name = "Account.findByClientId", query = "SELECT a FROM Account a WHERE a.clientId = :clientId AND a.status != 'closed'")})
public class Account implements Serializable {
    private static final long serialVersionUID = 1L;
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Basic(optional = false)
    @Column(name = "id")
    private Integer id;
    @Basic(optional = false)
    @NotNull
    @Size(min = 1, max = 7)
    @Column(name = "status")
    private String status = "active";
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
    
    public String getStatus() {
        return status;
    }
    
    public void setStatus(String status) {
        this.status = status;
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
