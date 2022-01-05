package rs.ac.bg.etf.is1.projekat.client.rest;

public class Diff<T> {
    T first;
    T second;
    @Override
    public String toString() {
        return "Differences between two entities:\nNew " + first + "\nOld " + second;
    }
}
