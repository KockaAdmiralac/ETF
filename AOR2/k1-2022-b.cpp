struct LogMisc {
    int code;
    char type;
    char severity;
    char* fromHostname;
    char* toHostname;
};

struct Log {
    // B0: 4 * 8 = 32bit
    char fromIP[4];
    // B0: 4 * 8 = 32bit
    char toIP[4];
    // B1: 32bit
    int time;
    // B1: 32bit
    LogMisc* misc;
};

int communicationUntilCount(const Log logs[], int n, const char IP[], int time) {
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        bool ok = logs[i].time < time;
        for (int j = 0; j < 3 && ok; j++) {
            ok &= (logs[i].fromIP[j] == IP[j]) | (logs[i].toIP[j] == IP[j]);
        }
        if (ok) {
            cnt++;
        }
    }
    return cnt;
}
