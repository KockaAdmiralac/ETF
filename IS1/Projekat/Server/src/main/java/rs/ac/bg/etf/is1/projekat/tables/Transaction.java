package rs.ac.bg.etf.is1.projekat.tables;

import java.io.Serializable;
import java.util.Date;
import javax.json.bind.annotation.JsonbTransient;
import javax.persistence.Basic;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.ManyToOne;
import javax.persistence.NamedQueries;
import javax.persistence.NamedQuery;
import javax.persistence.Table;
import javax.persistence.Temporal;
import javax.persistence.TemporalType;
import javax.validation.constraints.NotNull;
import javax.validation.constraints.Size;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlTransient;

@Entity
@Table(name = "transaction")
@XmlRootElement
@NamedQueries({
    @NamedQuery(name = "Transaction.findAll", query = "SELECT t FROM Transaction t"),
    @NamedQuery(name = "Transaction.findById", query = "SELECT t FROM Transaction t WHERE t.id = :id"),
    @NamedQuery(name = "Transaction.findByType", query = "SELECT t FROM Transaction t WHERE t.type = :type"),
    @NamedQuery(name = "Transaction.findByProcessingDate", query = "SELECT t FROM Transaction t WHERE t.processingDate = :processingDate"),
    @NamedQuery(name = "Transaction.findByAmount", query = "SELECT t FROM Transaction t WHERE t.amount = :amount"),
    @NamedQuery(name = "Transaction.findByTransactionNumber", query = "SELECT t FROM Transaction t WHERE t.transactionNumber = :transactionNumber"),
    @NamedQuery(name = "Transaction.findByPurpose", query = "SELECT t FROM Transaction t WHERE t.purpose = :purpose"),
    @NamedQuery(name = "Transaction.findByOfficeId", query = "SELECT t FROM Transaction t WHERE t.officeId = :officeId"),
    @NamedQuery(name = "Transaction.findByAccountId", query = "SELECT t FROM Transaction t WHERE t.accountIdFrom = :accountId")})
public class Transaction implements Serializable {

    private static final long serialVersionUID = 1L;
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Basic(optional = false)
    @Column(name = "id")
    private Integer id;
    @Basic(optional = false)
    @NotNull
    @Size(min = 1, max = 8)
    @Column(name = "type")
    private String type;
    @Basic(optional = false)
    @NotNull
    @Column(name = "processing_date")
    @Temporal(TemporalType.TIMESTAMP)
    private Date processingDate = new Date();
    @Basic(optional = false)
    @NotNull
    @Column(name = "amount")
    private int amount;
    @Basic(optional = false)
    @NotNull
    @Column(name = "transaction_number")
    private int transactionNumber;
    @Size(max = 255)
    @Column(name = "purpose")
    private String purpose;
    @Column(name = "office_id")
    private Integer officeId;
    @JoinColumn(name = "account_id_from", referencedColumnName = "id")
    @ManyToOne(optional = false)
    @XmlTransient
    @JsonbTransient
    private Account accountIdFrom;
    @JoinColumn(name = "account_id_to", referencedColumnName = "id")
    @ManyToOne(optional = false)
    @XmlTransient
    @JsonbTransient
    private Account accountIdTo;

    public Transaction() {
    }

    public Transaction(Integer id) {
        this.id = id;
    }

    public Transaction(Integer id, String type, Date processingDate, int amount, int transactionNumber) {
        this.id = id;
        this.type = type;
        this.processingDate = processingDate;
        this.amount = amount;
        this.transactionNumber = transactionNumber;
    }

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public Date getProcessingDate() {
        return processingDate;
    }

    public void setProcessingDate(Date processingDate) {
        this.processingDate = processingDate;
    }

    public int getAmount() {
        return amount;
    }

    public void setAmount(int amount) {
        this.amount = amount;
    }

    public int getTransactionNumber() {
        return transactionNumber;
    }

    public void setTransactionNumber(int transactionNumber) {
        this.transactionNumber = transactionNumber;
    }

    public String getPurpose() {
        return purpose;
    }

    public void setPurpose(String purpose) {
        this.purpose = purpose;
    }

    public Integer getOfficeId() {
        return officeId;
    }

    public void setOfficeId(Integer officeId) {
        this.officeId = officeId;
    }

    @XmlTransient
    @JsonbTransient
    public Account getAccountIdFrom() {
        return accountIdFrom;
    }

    public void setAccountIdFrom(Account accountIdFrom) {
        this.accountIdFrom = accountIdFrom;
    }

    @XmlTransient
    @JsonbTransient
    public Account getAccountIdTo() {
        return accountIdTo;
    }

    public void setAccountIdTo(Account accountIdTo) {
        this.accountIdTo = accountIdTo;
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
        if (!(object instanceof Transaction)) {
            return false;
        }
        Transaction other = (Transaction) object;
        if ((this.id == null && other.id != null) || (this.id != null && !this.id.equals(other.id))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "rs.ac.bg.etf.is1.projekat.tables.Transaction[ id=" + id + " ]";
    }
    
}
