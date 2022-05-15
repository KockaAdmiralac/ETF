class SingleBathroomProblem {
    public static final int capacity = 10;
    private int count = 0;
    private int childCount = 0;
    // Група која је тренутно у тоалету
    // -1 - нема никога, 0 - мушкарци, 1 - жене, 2 - домар
    private int group = -1;
    private final Condition queue = new Condition();
    private final Condition childrenQueue = new Condition();
    private final Condition waitingForChildren = new Condition();
    private int ticket = 1;
    private void signalPersonOrChild() {
        boolean personWaiting = queue.queue() && queue.minrank() % 3 == group;
        boolean childWaiting = childrenQueue.queue();
        if (personWaiting && childWaiting) {
            if (queue.minrank() > childrenQueue.minrank() * 3) {
                // Одрасла особа је стигла пре детета
                queue.signal();
            } else {
                // Дете је стигло пре одрасле особе
                childrenQueue.signal();
            }
        } else if (personWaiting) {
            queue.signal();
        } else if (childWaiting) {
            childrenQueue.signal();
        }
    }
    public synchronized void enterMan() {
        int myTicket = ticket++;
        if (count == capacity || group == 1 || group == 2 || queue.queue()) {
            // Пун тоалет, у њему су жене/домар или има других особа испред тоалета
            queue.wait(myTicket * 3);
        }
        ++count;
        if (group == -1) {
            // Означавамо да је тренутно активна група мушкараца
            group = 0;
        } else if (waitingForChildren.queue()) {
            // Ако има мушкарца који чека децу јавља му се да не мора више да чека
            waitingForChildren.signal();
        }
        if (count != capacity) {
            signalPersonOrChild();
        }
    }
    public synchronized void enterWoman() {
        int myTicket = ticket++;
        if (count == capacity || group == 0 || group == 2 || queue.queue()) {
            // Пун тоалет или су у њему мушкарци/домар
            queue.wait(myTicket * 3 + 1);
        }
        ++count;
        if (group == -1) {
            // Означавамо да је тренутно активна група жена
            group = 1;
        }
        if (count != capacity) {
            signalPersonOrChild();
        }
    }
    public synchronized void enterJanitor() {
        int myTicket = ticket++;
        if (group != -1) {
            // У тоалету или испред тоалета има било кога
            queue.wait(myTicket * 3 + 2);
        }
        ++count;
        // Означавамо да је домар тренутно у тоалету
        group = 2;
    }
    public synchronized void enterChild() {
        int myTicket = ticket++;
        if (count == capacity || group == 2 || group == -1 || queue.queue() || childrenQueue.queue() || waitingForChildren.queue()) {
            // Пун тоалет, у њему нема никога, у њему је домар, има других особа
            // испред тоалета или има особа која је унутра и чека да деца изађу
            childrenQueue.wait(myTicket);
        }
        ++count;
        ++childCount;
        if (count != capacity) {
            signalPersonOrChild();
        }
    }
    public synchronized void exitMan() {
        if (count == childCount + 1) {
            // Мушкарац не може да изађе док су деца сама у тоалету
            waitingForChildren.wait();
        }
        --count;
        if (count == 0) {
            // Нема више никог у тоалету, пусти следећу одраслу особу ако је има
            group = -1;
            if (queue.queue()) {
                queue.signal();
            }
        } else {
            signalPersonOrChild();
        }
    }
    public synchronized void exitWoman() {
        if (count == childCount + 1) {
            // Жена не може да изађе док су деца сама у тоалету
            waitingForChildren.wait();
        }
        --count;
        if (count == 0) {
            // Нема више никог у тоалету, пусти следећу одраслу особу ако је има
            group = -1;
            if (queue.queue()) {
                queue.signal();
            }
        } else if (queue.queue() && queue.minrank() % 3 == group) {
            signalPersonOrChild();
        }
    }
    public synchronized void exitJanitor() {
        --count;
        // Сигурно нема више никог у тоалету
        group = -1;
        if (queue.queue()) {
            queue.signal();
        }
    }
    public synchronized void exitChild() {
        --count;
        --childCount;
        if (waitingForChildren.queue() && childCount == 0) {
            // Јави особи која чека на излазак детета да су сва деца изашла
            waitingForChildren.signal();
        }
        if (count == 0) {
            // Нема више никог у тоалету, пусти следећу одраслу особу ако је има
            group = -1;
            if (queue.queue()) {
                queue.signal();
            }
        } else if (queue.queue() && queue.minrank() % 3 == group) {
            signalPersonOrChild();
        }
    }
}
