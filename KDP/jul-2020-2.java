class TheH2OProblem {
    private Condition hQueue = new Condition();
    private Condition oQueue = new Condition();
    private int hCount = 0;
    private int oCount = 0;
    private int hTicket = 1;
    private int oTicket = 1;
    public synchronized void hReady() {
        ++hCount;
        if (hCount >= 2 && oCount >= 1) {
            makeWater();
            hCount -= 2;
            oCount -= 1;
            hQueue.signal();
            oQueue.signal();
        } else {
            hQueue.wait(hTicket++);
        }
    }
    public synchronized void oReady() {
        ++oCount;
        if (hCount >= 2 && oCount >= 1) {
            makeWater();
            hCount -= 2;
            oCount -= 1;
            hQueue.signal();
            hQueue.signal();
        } else {
            oQueue.wait(oTicket++);
        }
    }
    private void makeWater() {
        // ...
    }
}
