#include <math.h>
const int BLOCK_SIZE = 16384;
void sobel(double *image, const int rows, const int columns, double *edges) {
    for (register int block = 0; block < columns / BLOCK_SIZE; ++block) {
        for (register int row = 1; row < rows - 1; ++row) {
            for (register int column = block * BLOCK_SIZE; column < columns - 1 && column < (block + 1) * BLOCK_SIZE; ++column) {
                const double gx = -1 * image[(row - 1) * columns + (column - 1)] +
                                   1 * image[(row - 1) * columns + (column + 1)] +
                                  -2 * image[(row - 0) * columns + (column - 1)] +
                                   2 * image[(row - 0) * columns + (column + 1)] +
                                  -1 * image[(row + 1) * columns + (column - 1)] +
                                   1 * image[(row + 1) * columns + (column + 1)];
                const double gy = -1 * image[(row - 1) * columns + (column - 1)] +
                                  -2 * image[(row - 1) * columns + (column - 0)] +
                                  -1 * image[(row - 1) * columns + (column + 1)] +
                                   1 * image[(row + 1) * columns + (column - 1)] +
                                   2 * image[(row + 1) * columns + (column - 0)] +
                                   1 * image[(row + 1) * columns + (column + 1)];
                edges[row * columns + column] = sqrt(gx * gx + gy * gy);
            }
        }
    }
}
