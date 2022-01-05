package rs.ac.bg.etf.is1.projekat.responses;

import rs.ac.bg.etf.is1.projekat.commands.Command;

public class DataResponse<T> extends SuccessfulResponse {
    private final T data;
    public DataResponse(Command cmd, T data) {
        super(cmd);
        this.data = data;
    }
    public T getData() {
        return data;
    }
}
