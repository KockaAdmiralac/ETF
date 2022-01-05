package rs.ac.bg.etf.is1.projekat.client;

import java.util.Scanner;
import retrofit2.Call;
import rs.ac.bg.etf.is1.projekat.client.rest.Service;

public class GetBackupDiffMenuItem extends MenuItem {
    @Override
    public String name() {
        return "Get differences between backup and real data";
    }
    @Override
    public Call<?> execute(Scanner scanner, Service service) {
        return service.backupDiff();
    }
}
