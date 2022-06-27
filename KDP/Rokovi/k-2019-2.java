class PodzemnaGaraza {
    private static final int N = 100;
    private int ulazi = 0;
    private int izlazi = 0;
    private int parkirano = 0;
    private boolean rampaZauzeta = false;
    private Condition ulaziRed = new Condition();
    private Condition izlaziRed = new Condition();
    public synchronized boolean trazim_ulaz() {
        if (parkirano + ulazi == N) {
            return false;
        }
        ++ulazi;
        if (!ulaziRed.queue() && !izlaziRed.queue() && !rampaZauzeta) {
            // Нема никога, улазимо
            rampaZauzeta = true;
            return true;
        }
        ulaziRed.wait();
        // rampaZauzeta је постављена од стране нити која сигнлизира
        return true;
    }
    public synchronized void usao() {
        ++parkirano;
        --ulazi;
        signal();
    }
    public synchronized void trazim_izlaz() {
        ++izlazi;
        --parkirano;
        if (!izlaziRed.queue() && !rampaZauzeta) {
            rampaZauzeta = true;
            return;
        }
        izlaziRed.wait();
        // rampaZauzeta је постављена од стране нити која сигнлизира
    }
    public synchronized void izasao() {
        --izlazi;
        signal();
    }
    private void signal() {
        rampaZauzeta = false;
        if (izlaziRed.queue()) {
            rampaZauzeta = true;
            izlaziRed.signal();
        } else if (ulaziRed.queue() && parkirano + izlazi < N) {
            rampaZauzeta = true;
            ulaziRed.signal();
        }
    }
}
