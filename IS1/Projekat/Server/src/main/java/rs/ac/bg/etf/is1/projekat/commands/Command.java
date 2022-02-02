package rs.ac.bg.etf.is1.projekat.commands;

import java.io.Serializable;
import java.util.UUID;

public abstract class Command implements Serializable {
    public enum Type {
        CREATE_PLACE,
        CREATE_OFFICE,
        CREATE_CLIENT,
        UPDATE_CLIENT,
        CREATE_ACCOUNT,
        DELETE_ACCOUNT,
        CREATE_TRANSACTION,
        GET_PLACES,
        GET_OFFICES,
        GET_CLIENTS,
        GET_ACCOUNTS_FOR_CLIENT,
        GET_TRANSACTIONS_FOR_ACCOUNT,
        GET_BACKUP,
        SYNC_CLIENT
    };
    public enum Destination {
        S1,
        S2,
        S3,
        ALL
    };
    protected final UUID uuid;
    public Command() {
        this.uuid = UUID.randomUUID();
    }
    public String getId() {
        return uuid.toString();
    }
    @Override
    public String toString() {
        return "Command[type=" +
                getType() +
                ", id=" +
                uuid +
                ", dest=" +
                getDestination() +
                "]";
    }
    abstract public Destination getDestination();
    abstract public Type getType();
}
