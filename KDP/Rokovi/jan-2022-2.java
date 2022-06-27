class Berbernica {
    // Идентификатори које муштерије могу да проследе у osisajSe()
    public static final int ACA_ID = 0;
    public static final int BRACA_ID = 1;
    public static final int BILO_KO = 2;
    // Редови чекања муштерија на столицама за шишање
    private Condition[] redZaSisanje = new Condition[3];
    // Редови чекања берберина када спавају
    private Condition[] berberinGotov = new Condition[2];
    // Редови чекања муштерија док се шишају
    private Condition[] cekamKrajSisanja = new Condition[2];
    // Редови чекања берберина док чекају муштерију да плати и изађе
    private Condition[] cekamIsplatu = new Condition[2];
    // Да ли је берберин тренутно заузет
    private boolean[] zauzet = new boolean[2];
    // Коју муштерију берберин тренутно шиша (идентификује се по броју у реду)
    private int trenutnoSisam = new int[2];
    // Број преосталих столица за седење
    private int stolice = 10;
    // Редни број муштерије
    private int red = 1;
    public Berbernica() {
        for (int i = 0; i < 3; ++i) {
            redZaSisanje[i] = new Condition();
        }
        for (int i = 0; i < 2; ++i) {
            berberinGotov[i] = new Condition();
            cekamKrajSisanja[i] = new Condition();
            cekamIsplatu[i] = new Condition();
            zauzet[i] = true;
        }
    }
    // Враћа идентификатор берберина уколико је слободан,
    // или -1 уколико нема слободних берберина за задати избор
    private int daLiJeZauzet(int izbor) {
        switch (izbor) {
            case ACA_ID:
            case BRACA_ID:
                return zauzet[izbor] ? -1 : izbor;
            case BILO_KO:
                if (!zauzet[ACA_ID]) {
                    return ACA_ID;
                }
                if (!zauzet[BRACA_ID]) {
                    return BRACA_ID;
                }
                return -1;
        }
    }
    public synchronized boolean osisajSe(int izbor) {
        int mojRed = red++;
        int berberin = daLiJeZauzet(izbor);
        if (berberin == -1) {
            if (stolice == 0) {
                return false;
            }
            --stolice;
            redZaSisanje[izbor].wait(mojRed);
            if (izbor == BILO_KO) {
                if (trenutnoSisam[ACA_ID] == mojRed) {
                    berberin = ACA_ID;
                } else {
                    berberin = BRACA_ID;
                }
            } else {
                berberin = izbor;
            }
            ++stolice;
        } else {
            zauzet[berberin] = true;
            trenutnoSisam[berberin] = mojRed;
            berberinGotov[berberin].signal();
        }
        // Седање на столицу се не моделује неком посебном методом
        cekamKrajSisanja[berberin].wait();
        // Плаћање и излазак
        cekamIsplatu[berberin].signal();
        return true;
    }
    public synchronized void sacekajMusteriju(int berberId) {
        int musterija;
        if (redZaSisanje[berberId].queue() && redZaSisanje[BILO_KO].queue()) {
            int musterija1 = redZaSisanje[berberId].minrank();
            int musterija2 = redZaSisanje[BILO_KO].minrank();
            if (musterija1 < musterija2) {
                musterija = musterija1;
                trenutnoSisam[berberId] = musterija;
                redZaSisanje[berberId].signal();
            } else {
                musterija = musterija2;
                trenutnoSisam[berberId] = musterija;
                redZaSisanje[BILO_KO].signal();
            }
        } else if (redZaSisanje[berberId].queue()) {
            musterija = redZaSisanje[berberId].minrank();
            trenutnoSisam[berberId] = musterija;
            redZaSisanje[berberId].signal();
        } else if (redZaSisanje[BILO_KO].queue()) {
            musterija = redZaSisanje[BILO_KO].minrank();
            trenutnoSisam[berberId] = musterija;
            redZaSisanje[BILO_KO].signal();
        } else {
            zauzet[berberId] = false;
            berberinGotov[berberId].wait();
        }
    }
    public synchronized void obavestiMusteriju(int berberId) {
        trenutnoSisam[berberId] = 0;
        cekamKrajSisanja[berberId].signal();
        cekamIsplatu[berberId].wait();
    }
}
