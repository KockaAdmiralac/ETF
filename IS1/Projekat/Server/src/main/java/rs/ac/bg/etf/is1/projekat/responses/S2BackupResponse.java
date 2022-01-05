package rs.ac.bg.etf.is1.projekat.responses;

import java.util.List;
import rs.ac.bg.etf.is1.projekat.commands.Command;
import rs.ac.bg.etf.is1.projekat.tables.Account;
import rs.ac.bg.etf.is1.projekat.tables.Transaction;

public class S2BackupResponse extends SuccessfulResponse {
    private final List<Account> accounts;
    private final List<Transaction> transactions;
    public S2BackupResponse(Command cmd, List<Account> accounts,
            List<Transaction> transactions) {
        super(cmd);
        this.accounts = accounts;
        this.transactions = transactions;
    }
    public List<Account> getAccounts() {
        return accounts;
    }
    public List<Transaction> getTransactions() {
        return transactions;
    }
}
