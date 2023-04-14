struct PC {
    char IP[4];
    char* hostname;
};

struct Log {
    int code;
    char type;
    PC* from;
    PC* to;
    char severity;
    int time;
};

int communicationUntilCount(const Log logs[], int n, const char IP[], int time) {
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        bool ok = logs[i].time < time;
        for (int j = 0; j < 3 && ok; j++) {
            // Претпоставка: from и to никада неће бити исти (јер то нема много смисла).
            ok &= (logs[i].from->IP[j] == IP[j]) | (logs[i].to->IP[j] == IP[j]);
        }
        if (ok) {
            cnt++;
        }
    }
    return cnt;
}
