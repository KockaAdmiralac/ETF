class SkupljanjeGajbica {
    private static final int prikolica_kapacitet = 100;
    private int broj_gajbica = 0;
    private Condition pokupi;
    private int maxrank = 1;
    private int waiting = 0;

    public synchronized void spreman_da_pokupim() {
        if (broj_gajbica < prikolica_kapacitet || waiting > 0) {
            ++waiting;
            pokupi.wait(maxrank++);
            --waiting;
        }
        broj_gajbica -= prikolica_kapacitet;
    }

    public synchronized void ostavljam_gajbice(int broj) {
        broj_gajbica += broj;
        int broj_signala = broj_gajbica / prikolica_kapacitet;
        for (int i = 0; i < broj_signala; ++i) {
            pokupi.signal();
        }
    }
}
