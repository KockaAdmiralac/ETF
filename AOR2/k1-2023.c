#include <math.h>
void sobel ( double *image, int rows, int columns, double *edges ) {
    int GX[] = { -1, 0, 1, -2, 0, 2, -1, 0, 1 };
    int GY[] = { -1, -2, -1, 0, 0, 0, 1, 2, 1 };

    for ( int row = 1; row < ( rows - 1 ); ++row ) {
        for ( int column = 1; column < ( columns - 1 ); ++column ) {
            double gx = 0;
            double gy = 0;

            for ( int i = 0; i < 3; ++i ) {
                for ( int j = 0; j < 3; ++j ) {
                    int image_row    = row + i - 1;
                    int image_column = column + j - 1;

                    double image_value = image[image_row * columns + image_column];

                    int kernel_index = i * 3 + j;

                    gx += image_value * GX[kernel_index];
                    gy += image_value * GY[kernel_index];
                }
            }

            edges[row * columns + column] = sqrt ( gx * gx + gy * gy );
        }
    }
}
