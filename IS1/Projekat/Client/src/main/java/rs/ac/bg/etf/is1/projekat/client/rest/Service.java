package rs.ac.bg.etf.is1.projekat.client.rest;

import java.util.List;
import retrofit2.Call;
import retrofit2.http.DELETE;
import retrofit2.http.Field;
import retrofit2.http.FormUrlEncoded;
import retrofit2.http.GET;
import retrofit2.http.PATCH;
import retrofit2.http.PUT;
import retrofit2.http.Path;

public interface Service {
    // Accounts
    @GET("account/{clientId}")
    Call<DataResponse<List<Account>>> accounts(@Path("clientId") int clientId);

    @PUT("account")
    @FormUrlEncoded
    Call<DataResponse<Account>> createAccount(@Field("clientId") int clientId,
            @Field("placeId") int placeId, @Field("overdraft") int overdraft);

    @DELETE("account/{accountId}")
    Call<Response> deleteAccount(@Path("accountId") int accountId);

    // Backups
    @GET("backup")
    Call<BackupResponse> backup();

    @GET("backup/diff")
    Call<BackupDiffResponse> backupDiff();
    
    // Clients
    @GET("client")
    Call<DataResponse<List<Client>>> clients();

    @PUT("client")
    @FormUrlEncoded
    Call<DataResponse<Client>> createClient(@Field("name") String name,
            @Field("address") String address, @Field("placeId") int placeId);

    @PATCH("client/{clientId}")
    @FormUrlEncoded
    Call<DataResponse<Client>> updateClient(@Path("clientId") int clientId,
            @Field("placeId") int placeId);
    
    // Offices
    @GET("office")
    Call<DataResponse<List<Office>>> offices();

    @PUT("office")
    @FormUrlEncoded
    Call<DataResponse<Office>> createOffice(@Field("name") String name,
            @Field("address") String address, @Field("placeId") int placeId);
    
    // Places
    @GET("place")
    Call<DataResponse<List<Place>>> places();
    
    @PUT("place")
    @FormUrlEncoded
    Call<DataResponse<Place>> createPlace(@Field("postalCode") int postalCode,
            @Field("name") String name);
    
    // Transactions
    @GET("transaction/{accountId}")
    Call<DataResponse<List<Transaction>>> transactions(
            @Path("accountId") int accountId);
    
    @PUT("transaction/internal")
    @FormUrlEncoded
    Call<DataResponse<Transaction>> createInternalTransaction(
            @Field("amount") int amount,
            @Field("accountIdFrom") int accountIdFrom,
            @Field("accountIdTo") int accountIdTo,
            @Field("purpose") String purpose);

    @PUT("transaction/incoming")
    @FormUrlEncoded
    Call<DataResponse<Transaction>> createIncomingTransaction(
            @Field("amount") int amount,
            @Field("accountIdFrom") int accountIdFrom,
            @Field("accountIdTo") int accountIdTo,
            @Field("purpose") String purpose, @Field("officeId") int officeId);

    @PUT("transaction/outgoing")
    @FormUrlEncoded
    Call<DataResponse<Transaction>> createOutgoingTransaction(
            @Field("amount") int amount,
            @Field("accountIdFrom") int accountIdFrom,
            @Field("accountIdTo") int accountIdTo,
            @Field("purpose") String purpose, @Field("officeId") int officeId);
}
