package rs.ac.bg.etf.is1.projekat.responses;

import java.io.Serializable;
import java.util.List;
import rs.ac.bg.etf.is1.projekat.commands.Command;
import rs.ac.bg.etf.is1.projekat.tables.Account;
import rs.ac.bg.etf.is1.projekat.tables.Client;
import rs.ac.bg.etf.is1.projekat.tables.Office;
import rs.ac.bg.etf.is1.projekat.tables.Place;
import rs.ac.bg.etf.is1.projekat.tables.Transaction;

public class BackupDiffResponse extends SuccessfulResponse {
    public static class EntityComparisonResult<T extends Serializable> {
        public static class EntityDifference<T extends Serializable> {
            private final T first;
            private final T second;
            public EntityDifference(T first, T second) {
                this.first = first;
                this.second = second;
            }
            public T getFirst() {
                return first;
            }
            public T getSecond() {
                return second;
            }
        }
        private final List<T> missing;
        private final List<EntityDifference<T>> differences;
        public EntityComparisonResult(List<T> missing,
                List<EntityDifference<T>> differences) {
            this.missing = missing;
            this.differences = differences;
        }
        public EntityComparisonResult() {
            this.missing = null;
            this.differences = null;
        }
        public List<T> getMissing() {
            return missing;
        }
        public List<EntityDifference<T>> getDifferences() {
            return differences;
        }
    }
    
    private final EntityComparisonResult<Account> accounts;
    private final EntityComparisonResult<Client> clients;
    private final EntityComparisonResult<Office> offices;
    private final EntityComparisonResult<Place> places;
    private final EntityComparisonResult<Transaction> transactions;
    public BackupDiffResponse(
        Command cmd,
        EntityComparisonResult<Account> accounts,
        EntityComparisonResult<Client> clients,
        EntityComparisonResult<Office> offices,
        EntityComparisonResult<Place> places,
        EntityComparisonResult<Transaction> transactions
    ) {
        super(cmd);
        this.accounts = accounts;
        this.clients = clients;
        this.offices = offices;
        this.places = places;
        this.transactions = transactions;
    }
    public EntityComparisonResult<Account> getAccounts() {
        return accounts;
    }
    public EntityComparisonResult<Client> getClients() {
        return clients;
    }
    public EntityComparisonResult<Office> getOffices() {
        return offices;
    }
    public EntityComparisonResult<Place> getPlaces() {
        return places;
    }
    public EntityComparisonResult<Transaction> getTransactions() {
        return transactions;
    }
}
