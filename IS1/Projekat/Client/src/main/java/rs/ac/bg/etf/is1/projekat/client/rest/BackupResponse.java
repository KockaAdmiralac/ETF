package rs.ac.bg.etf.is1.projekat.client.rest;

import java.util.List;

public class BackupResponse {
    public List<Account> accounts;
    public List<Client> clients;
    public List<Office> offices;
    public List<Place> places;
    public List<Transaction> transactions;
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append(super.toString());
        sb.append(" Backed up data follows:\n");
        sb.append("======================== ACCOUNTS ======================\n");
        accounts.forEach(a -> {
            sb.append(a);
            sb.append("\n");
        });
        sb.append("========================= CLIENTS ======================\n");
        clients.forEach(c -> {
            sb.append(c);
            sb.append("\n");
        });
        sb.append("========================= OFFICES ======================\n");
        offices.forEach(o -> {
            sb.append(o);
            sb.append("\n");
        });
        sb.append("========================= PLACES =======================\n");
        places.forEach(p -> {
            sb.append(p);
            sb.append("\n");
        });
        sb.append("====================== TRANSACTIONS ====================\n");
        transactions.forEach(t -> {
            sb.append(t);
            sb.append("\n");
        });
        return sb.toString();
    }
}
