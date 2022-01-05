package rs.ac.bg.etf.is1.projekat.client;

import java.util.Scanner;
import retrofit2.Call;
import rs.ac.bg.etf.is1.projekat.client.rest.Service;

public abstract class MenuItem {
    public abstract String name();
    public abstract Call<?> execute(Scanner scanner, Service service);
    protected int readInt(Scanner scanner, String prompt) {
        System.out.println(prompt + ":");
        return Integer.parseInt(scanner.nextLine());
    }
    protected String readString(Scanner scanner, String prompt) {
        System.out.println(prompt + ":");
        return scanner.nextLine();
    }
}
