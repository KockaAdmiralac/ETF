class SkupljanjeGajbica {
    final int prikolica_kapacitet = 100;
    int broj_gajbica = 0;
    Condition pokupi;
    int maxrank = 1;

    synchronized void spreman_da_pokupim() {
        if (broj_gajbica < prikolica_kapacitet) {
            pokupi.wait(maxrank++);
        }
        broj_gajbica -= prikolica_kapacitet;
    }

    synchronized void ostavljam_gajbice(int broj) {
        broj_gajbica += broj;
        int broj_signala = broj_gajbica / prikolica_kapacitet;
        for (int i = 0; i < broj_signala; ++i) {
            pokupi.signal();
        }
    }
}
