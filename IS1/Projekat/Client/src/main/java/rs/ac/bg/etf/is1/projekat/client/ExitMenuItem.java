package rs.ac.bg.etf.is1.projekat.client;

import java.util.Scanner;
import retrofit2.Call;
import rs.ac.bg.etf.is1.projekat.client.rest.Service;

public class ExitMenuItem extends MenuItem {
    @Override
    public String name() {
        return "Exit program";
    }
    @Override
    public Call<?> execute(Scanner scanner, Service service) {
        System.out.println("Exiting");
        System.exit(0);
        return null;
    }
}
