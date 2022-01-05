package rs.ac.bg.etf.is1.projekat.client;

import com.google.gson.Gson;
import com.google.gson.reflect.TypeToken;
import java.lang.reflect.Type;
import java.util.Scanner;
import java.util.logging.Level;
import java.util.logging.Logger;
import java.util.stream.IntStream;
import okhttp3.ResponseBody;
import retrofit2.Retrofit;
import retrofit2.converter.gson.GsonConverterFactory;
import rs.ac.bg.etf.is1.projekat.client.rest.Response;
import rs.ac.bg.etf.is1.projekat.client.rest.Service;

public class Client {
    private static final MenuItem[] items = {
        new ExitMenuItem(),
        new CreatePlaceMenuItem(),
        new CreateOfficeMenuItem(),
        new CreateClientMenuItem(),
        new UpdateClientMenuItem(),
        new CreateAccountMenuItem(),
        new DeleteAccountMenuItem(),
        new CreateTransactionMenuItem("internal"),
        new CreateTransactionMenuItem("incoming"),
        new CreateTransactionMenuItem("outgoing"),
        new GetPlacesMenuItem(),
        new GetOfficesMenuItem(),
        new GetClientsMenuItem(),
        new GetAccountsMenuItem(),
        new GetTransactionsMenuItem(),
        new GetBackupMenuItem(),
        new GetBackupDiffMenuItem()
    };
    
    public static void main(String[] arguments) {
        Scanner scanner = new Scanner(System.in);
        Retrofit retrofit = new Retrofit.Builder()
            .baseUrl("http://localhost:8080/Server/")
            .addConverterFactory(GsonConverterFactory.create())
            .build();
        Gson gson = new Gson();
        Type errorResponseType = new TypeToken<Response>() {}.getType();
        Service service = retrofit.create(Service.class);
        while (true) {
            try {
                System.out.println("Choose an option:");
                IntStream.range(0, items.length).forEach(i -> {
                    System.out.format("\t%02d. %s\n", i, items[i].name());
                });
                int option = Integer.parseInt(scanner.nextLine());
                if (option > items.length || option < 0) {
                    System.err.println("Invalid option number!");
                    continue;
                }
                retrofit2.Response response = items[option]
                    .execute(scanner, service)
                    .execute();
                Object responseBody = response.body();
                if (!response.isSuccessful() || responseBody == null) {
                    System.err.println("Request failed!");
                    System.err.println("Error code: " + response.code());
                    ResponseBody errorBody = response.errorBody();
                    if (errorBody != null) {
                        Response errorResponse = gson.fromJson(errorBody.string(), errorResponseType);
                        System.err.println("Reason: " + errorResponse.reason);
                    }
                } else {
                    System.out.println(responseBody);
                }
            } catch (Exception ex) {
                Logger.getLogger(Client.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
    }
}
