class Semaphore {
    private int value;
    private Queue<Integer> requests = new Queue<>();
    private Condition queue = new Condition();
    public Semaphore(int value) {
        this.value = value;
    }
    public synchronized void wait(int num) {
        if (value >= num) {
            value -= num;
        } else {
            requests.insert(num);
            queue.wait();
        }
    }
    public synchronized void signal(int num) {
        value += num;
        while (requests.size() > 0 && value >= requests.top()) {
            value -= requests.pop();
            queue.signal();
        }
    }
    public synchronized void wait() {
        wait(1);
    }
    public synchronized void signal() {
        signal(1);
    }
}
