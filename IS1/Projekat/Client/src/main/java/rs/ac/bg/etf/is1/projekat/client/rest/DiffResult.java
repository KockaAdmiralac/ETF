package rs.ac.bg.etf.is1.projekat.client.rest;

import java.util.List;

public class DiffResult<T> {
    public List<T> missing;
    public List<Diff<T>> differences;
    @Override
    public String toString() {
        if (missing.isEmpty() && differences.isEmpty()) {
            return "There are no differences between these entities.";
        }
        StringBuilder sb = new StringBuilder();
        if (!missing.isEmpty()) {
            sb.append("Missing entities:");
            missing.forEach(m -> {
                sb.append("\n");
                sb.append(m);
            });
        }
        if (!missing.isEmpty() && !differences.isEmpty()) {
            sb.append("\n");
        }
        if (!differences.isEmpty()) {
            sb.append("Different entities:");
            differences.forEach(d -> {
                sb.append("\n");
                sb.append(d);
            });
        }
        return sb.toString();
    }
}
