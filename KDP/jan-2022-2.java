class Berbernica {
    final int ACA_ID = 0;
    final int BRACA_ID = 1;
    final int BILO_KO = 2;
    Condition[] sisanje = new Condition[3];
    Condition[] gotov = new Condition[2];
    boolean[] zauzet = new boolean[2];
    int red = 1;
    Berbernica() {
        for (int i = 0; i < 3; ++i) {
            sisanje[i] = new Condition();
        }
        for (int i = 0; i < 2; ++i) {
            gotov[i] = new Condition();
        }
    }
    boolean daLiJeZauzet(int izbor) {
        switch (izbor) {
            case ACA_ID:
            case BRACA_ID:
                return zauzet[izbor];
            case BILO_KO:
                return zauzet[ACA_ID] || zauzet[BRACA_ID];
        }
    }
    synchronized void osisajSe(int izbor) {
        int mojRed = red++;
        if (daLiJeZauzet(izbor)) {
            sisanje[izbor].wait(mojRed);
        }
        // Седање на столицу се не моделује неком посебном методом
        
    }
    synchronized void sacekajMusteriju(int berberId) {
        //
    }
    synchronized void obavestiMusteriju(int berberId) {
        //
    }
}
