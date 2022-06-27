class Monitor {
    public static final PRIORITY_HIGH = 1;
    public static final PRIORITY_LOW = 2;
    private final Condition queueOne = new Condition();
    private final Condition queueTwo = new Condition();
    private int resources = 0;
    public synchronized void request(int amount, int priority) {
        if (resources >= amount) {
            resources -= amount;
        } else {
            if (amount == 2) {
                priority += 2;
            }
            queue.wait(priority);
        }
    }
    public synchronized void release(int amount) {

    }
}
