class DiningPhilosophers {
    public static final int N = 10;
    boolean forks[] = new boolean[N];
    Condition queue = new Condition();
    int ticket = 1;
    private int left(int id) {
        return id;
    }
    private int right(int id) {
        return id + 1;
    }
    public synchronized void acquireForks(int id) {
        if (queue.queue() || forks[left(id)] || forks[right(id)]) {
            queue.wait((ticket++) * N + id);
        }
        forks[left(id)] = true;
        forks[right(id)] = true;
        signal();
    }
    public synchronized void releaseForks(int id) {
        forks[left(id)] = false;
        forks[right(id)] = false;
        signal();
    }
    private void signal() {
        if (queue.empty()) {
            return;
        }
        int id = queue.minrank() % N;
        if (!forks[left(id)] && !forks[right(id)]) {
            queue.signal();
        }
    }
}
