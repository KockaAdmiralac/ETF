int communicationUntilCount(const char fromIPs[], const char toIPs[], const int times[], const char IP[], int n, int time) {
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        bool ok = times[i] < time;
        for (int j = 0; j < 3 && ok; j++) {
            ok &= (fromIPs[(i << 2) + j] == IP[j]) | (toIPs[(i << 2) + j] == IP[j]);
        }
        if (ok) {
            cnt++;
        }
    }
    return cnt;
}
