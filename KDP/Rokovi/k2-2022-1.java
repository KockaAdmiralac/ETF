class ReadersWriters {
    private int readers = 0;
    private int writers = 0;
    private int ticket = 1;
    private Condition okToRead = new Condition();
    private Condition okToWrite = new Condition();
    public synchronized void lockShared() {
        if (writers == 0 && okToWrite.empty()) {
            ++readers;
        } else {
            okToRead.wait(ticket++);
        }
    }
    public synchronized void lockExclusive() {
        if (readers == 0 && writers == 0) {
            ++writers;
        } else {
            okToWrite.wait(ticket++);
        }
    }
    public synchronized void unlock() {
        if (readers > 0) {
            if (--readers == 0 && okToWrite.queue()) {
                writers = 1;
                okToWrite.signal();
            }
        } else {
            boolean readersNext = okToRead.queue() && (okToWrite.empty() || okToRead.minrank() < okToWrite.minrank());
            boolean writersNext = okToWrite.queue() && (okToRead.empty() || okToWrite.minrank() < okToRead.minrank());
            if (readersNext) {
                while (okToRead.queue() && okToRead.minrank() < okToWrite.minrank()) {
                    ++readers;
                    okToRead.signal();
                }
            } else if (writersNext) {
                okToWrite.signal();
            } else {
                writers = 0;
            }
        }
    }
    public synchronized void upgradeLock() {
        if (readers == 1) {
            // Ако је само један читалац, конвертуј га у писца
            readers = 0;
            writers = 1;
        } else {
            // У супротном, мораће да сачека остале читаоце и писце како би постао писац
            unlock();
            lockExclusive();
        }
    }
}
