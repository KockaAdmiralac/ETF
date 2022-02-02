package rs.ac.bg.etf.is1.projekat.client.rest;

import java.util.Date;

public class Transaction {
    public int id;
    public String type;
    public Date processingDate;
    public int amount;
    public int transactionNumber;
    public String purpose;
    public int officeId;
    public Account account;
    @Override
    public String toString() {
        return "Transaction:" +
                "\n\tID: " + id +
                "\n\tType: " + type +
                "\n\tAmount: " + amount +
                "\n\tTransaction number: " + transactionNumber +
                "\n\tPurpose: " + (purpose == null ? "null" : purpose) +
                "\n\tOffice ID: " + officeId +
                "\n\tAccount: " + (account == null ? "null" : account);
    }
}
