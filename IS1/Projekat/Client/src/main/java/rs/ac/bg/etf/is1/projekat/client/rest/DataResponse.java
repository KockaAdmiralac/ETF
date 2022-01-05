package rs.ac.bg.etf.is1.projekat.client.rest;

import java.util.List;

public class DataResponse<T> extends Response {
    public T data;
    private static <T> void formatList(StringBuilder sb, List<T> list) {
        list.forEach(t -> {
            sb.append("\n");
            sb.append(t);
        });
    }
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append(super.toString());
        sb.append(" Response data is:\n");
        if (data instanceof List<?>) {
            formatList(sb, (List<?>)data);
        } else {
            sb.append(data);
        }
        return sb.toString();
    }
}
