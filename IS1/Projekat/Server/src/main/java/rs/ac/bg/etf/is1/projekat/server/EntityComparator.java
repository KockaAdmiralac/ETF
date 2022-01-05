package rs.ac.bg.etf.is1.projekat.server;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;
import javax.ejb.Singleton;
import rs.ac.bg.etf.is1.projekat.responses.BackupDiffResponse;

@Singleton
public class EntityComparator {
    public interface DeepEntityComparator<T extends Serializable> {
        public boolean deepEquals(T e1, T e2);
    }
    public <T extends Serializable> BackupDiffResponse.EntityComparisonResult<T> compare(
            List<T> shorterList, List<T> longerList,
            DeepEntityComparator<T> entityComparison) {
        List<T> missing = new ArrayList<>();
        List<BackupDiffResponse.EntityComparisonResult.EntityDifference<T>> differences = new ArrayList<>();
        longerList.forEach(e1 -> {
            Optional<T> matched = shorterList
                .stream()
                .filter(e2 -> e1.equals(e2))
                .findFirst();
            if (!matched.isPresent()) {
                missing.add(e1);
            } else if (!entityComparison.deepEquals(e1, matched.get())) {
                differences.add(new BackupDiffResponse.EntityComparisonResult.EntityDifference<>(e1, matched.get()));
            }
        });
        return new BackupDiffResponse.EntityComparisonResult<>(missing, differences);
    }
}
