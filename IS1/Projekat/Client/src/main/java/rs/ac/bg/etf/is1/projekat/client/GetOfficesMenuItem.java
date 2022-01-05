package rs.ac.bg.etf.is1.projekat.client;

import java.util.Scanner;
import retrofit2.Call;
import rs.ac.bg.etf.is1.projekat.client.rest.Service;

public class GetOfficesMenuItem extends MenuItem {
    @Override
    public String name() {
        return "Get offices";
    }
    @Override
    public Call<?> execute(Scanner scanner, Service service) {
        return service.offices();
    }
}
