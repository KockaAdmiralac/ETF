package rs.ac.bg.etf.is1.projekat.client.rest;

import java.util.Date;

public class Account {
    public int id;
    public int balance;
    public int overdraft;
    public Date creationDate;
    public int transactionCount;
    public int placeId;
    public String status;
    public int clientId;
    @Override
    public String toString() {
        return "Account:" +
                "\n\tID: " + id +
                "\n\tBalance: " + balance +
                "\n\tOverdraft: " + overdraft +
                "\n\tCreation date: " + creationDate +
                "\n\tTransaction count: " + transactionCount +
                "\n\tPlace ID: " + placeId +
                "\n\tStatus: " + status +
                "\n\tClient ID: " + clientId;
    }
}
