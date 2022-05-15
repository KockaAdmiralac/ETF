class PrintersMonitor {
    private class ProcessPriority implements Comparable<ProcessPriority> {
        public int priority;
        public int ticket;
        public int id;
        public int printer;
        public ProcessPriority(int priority, int ticket, int id) {
            this.priority = priority;
            this.ticket = ticket;
            this.id = id;
        }
        @Override
        public int compareTo(ProcessPriority p2) {
            if (priority == p2.priority) {
                // Ако је приоритет исти, уреди по времену стизања
                return ticket - p2.ticket;
            }
            // Прво се уређује по приоритету
            return priority - p2.priority;
        }
    }
    private static final int N = 100;
    private boolean[] busy = new boolean[2];
    private Condition[] free = new Condition[N];
    private PriorityQueue<ProcessPriority> pq = new PriorityQueue<>(N);
    private int ticket = 0;
    private int id = 0;
    public PrintersMonitor() {
        for (int i = 0; i < N; ++i) {
            free[i] = new Condition();
        }
    }
    public synchronized int request(int priority) {
        // Прво проверимо да ли има слободних штампача
        for (int i = 0; i < 2; ++i) {
            if (!busy[i]) {
                busy[i] = true;
                return i;
            }
        }
        // Ако нема, убацујемо се у ред за чекање
        int myTicket = ticket++;
        int myId = id;
        id = (id + 1) % N;
        ProcessPriority pp = new ProcessPriority(priority, myTicket, myId);
        pq.push(pp);
        free[myId].wait();
        // Одблокирао нас је неки процес који је раније држао неки штампач
        return pp.printer;
    }
    public synchronized void release(int printer) {
        if (pq.isEmpty()) {
            busy[printer] = false;
        } else {
            ProcessPriority pp = pq.pop();
            free[pp.id].signal();
            pp.printer = printer;
        }
    }
}
