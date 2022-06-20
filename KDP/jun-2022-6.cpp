#include "common.h"

const int P = 100;
const int C = 100;
const int B = 100;

struct Product {};
Product produce();
void consume(Product p);

int producer() {
    while (true) {
        Product p = produce();
        in("buffer empty");
        int index;
        in("producer index", &index);
        out("product", index, p);
        out("consumer count", C);
        out("producer index", (index + 1) % B);
        int size;
        in("size", &size);
        if (size == 0) {
            out("buffer full");
        }
        out("size", ++size);
        if (size < B) {
            out("buffer empty");
        }
    }
}

void consumer() {
    int index = 0;
    while (true) {
        in("buffer full");
        Product p;
        int count;
        in("consumer count", index, &count);
        if (count == 1) {
            in("product", index, &p);
            int size;
            in("size", &size);
            if (size == B) {
                out("buffer empty");
            }
            out("size", --size);
            if (size > 0) {
                out("buffer full");
            }
        } else {
            rd("product", index, &p);
            out("consumer count", count-1);
            out("buffer full");
        }
        index = (index + 1) % B;
        consume(p);
    }
}
