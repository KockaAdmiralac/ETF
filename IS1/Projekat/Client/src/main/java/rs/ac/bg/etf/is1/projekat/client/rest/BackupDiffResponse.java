package rs.ac.bg.etf.is1.projekat.client.rest;

public class BackupDiffResponse extends Response {
    public DiffResult<Account> accounts;
    public DiffResult<Client> clients;
    public DiffResult<Office> offices;
    public DiffResult<Place> places;
    public DiffResult<Transaction> transactions;
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("======================== ACCOUNTS ======================\n");
        sb.append(accounts);
        sb.append("\n========================= CLIENTS ======================\n");
        sb.append(clients);
        sb.append("\n========================= OFFICES ======================\n");
        sb.append(offices);
        sb.append("\n========================= PLACES =======================\n");
        sb.append(places);
        sb.append("\n====================== TRANSACTIONS ====================\n");
        sb.append(transactions);
        return sb.toString();
    }
}
