#define MIN_FLOAT -200000

double temp[86400][31];

int main(void) {
    for (register int i = 0; i < 31; i += 8) {
        register double max[8] = {MIN_FLOAT, MIN_FLOAT, MIN_FLOAT, MIN_FLOAT, MIN_FLOAT, MIN_FLOAT, MIN_FLOAT, MIN_FLOAT};
        for (register int j = 0; j < 86400; ++j) {
            for (register int k = i; k < i + 8 && k < 31; ++k) {
                if (max[k - i] < temp[j][i]) {
                    max[k - i] = temp[j][i];
                }
            }
        }
        for (register int j = 0; j < 8; ++j) {
            printf("maj %d.: %lf", i + j, max[j]);
        }
    }
    return 0;
}
