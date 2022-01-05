package rs.ac.bg.etf.is1.projekat.responses;

import java.util.List;
import rs.ac.bg.etf.is1.projekat.commands.Command;
import rs.ac.bg.etf.is1.projekat.tables.Client;
import rs.ac.bg.etf.is1.projekat.tables.Office;
import rs.ac.bg.etf.is1.projekat.tables.Place;
import rs.ac.bg.etf.is1.projekat.tables.Account;
import rs.ac.bg.etf.is1.projekat.tables.Transaction;

public class S3BackupResponse extends SuccessfulResponse {
    private final List<Account> accounts;
    private final List<Client> clients;
    private final List<Office> offices;
    private final List<Place> places;
    private final List<Transaction> transactions;
    public S3BackupResponse(Command cmd, List<Account> accounts,
            List<Client> clients, List<Office> offices, List<Place> places,
            List<Transaction> transactions) {
        super(cmd);
        this.accounts = accounts;
        this.clients = clients;
        this.offices = offices;
        this.places = places;
        this.transactions = transactions;
    }
    public List<Account> getAccounts() {
        return accounts;
    }
    public List<Client> getClients() {
        return clients;
    }
    public List<Office> getOffices() {
        return offices;
    }
    public List<Place> getPlaces() {
        return places;
    }
    public List<Transaction> getTransactions() {
        return transactions;
    }
}
