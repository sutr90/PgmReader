//
// Created by VF on 9. 12. 2016.
//

#include "filtering.h"
#include <math.h>

float gaussKernel[3][3] = {
        {0.077847, 0.123317, 0.077847},
        {0.123317, 0.195346, 0.123317},
        {0.077847, 0.123317, 0.077847}
};

int sobelXKernel[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
};

int sobelYKernel[3][3] = {
        {-1, -2, -1},
        {0,  0,  0},
        {1,  2,  1}
};

PGMImage *gaussFilter(PGMImage *img, unsigned int size) {
    PGMImage *result = createPGMImage(img->height - 2, img->width - 2);

    for (int y = 0; y < img->height - 2; y++) {
        for (int x = 0; x < img->width - 2; x++) {
            double g = gaussKernel[0][0] * img->data[x][y] +
                       gaussKernel[0][1] * img->data[x][y + 1] +
                       gaussKernel[0][2] * img->data[x][y + 2] +
                       gaussKernel[1][0] * img->data[x + 1][y] +
                       gaussKernel[1][1] * img->data[x + 1][y + 1] +
                       gaussKernel[1][2] * img->data[x + 1][y + 2] +
                       gaussKernel[2][0] * img->data[x + 2][y] +
                       gaussKernel[2][1] * img->data[x + 2][y + 1] +
                       gaussKernel[2][2] * img->data[x + 2][y + 2];
            result->data[x][y] = (unsigned char) g;
        }
    }

    return result;
}

PGMImage *sobelFilter(PGMImage *img, unsigned int size) {
    PGMImage *result = createPGMImage(img->height - 2, img->width - 2);

    for (int y = 0; y < img->height - 2; y++) {
        for (int x = 0; x < img->width - 2; x++) {
            int gx = sobelXKernel[0][0] * img->data[x][y] +
                     sobelXKernel[0][1] * img->data[x][y + 1] +
                     sobelXKernel[0][2] * img->data[x][y + 2] +
                     sobelXKernel[1][0] * img->data[x + 1][y] +
                     sobelXKernel[1][1] * img->data[x + 1][y + 1] +
                     sobelXKernel[1][2] * img->data[x + 1][y + 2] +
                     sobelXKernel[2][0] * img->data[x + 2][y] +
                     sobelXKernel[2][1] * img->data[x + 2][y + 1] +
                     sobelXKernel[2][2] * img->data[x + 2][y + 2];

            int gy = sobelYKernel[0][0] * img->data[x][y] +
                     sobelYKernel[0][1] * img->data[x][y + 1] +
                     sobelYKernel[0][2] * img->data[x][y + 2] +
                     sobelYKernel[1][0] * img->data[x + 1][y] +
                     sobelYKernel[1][1] * img->data[x + 1][y + 1] +
                     sobelYKernel[1][2] * img->data[x + 1][y + 2] +
                     sobelYKernel[2][0] * img->data[x + 2][y] +
                     sobelYKernel[2][1] * img->data[x + 2][y + 1] +
                     sobelYKernel[2][2] * img->data[x + 2][y + 2];

            result->data[x][y] = (unsigned char) sqrt(gx * gx + gy * gy);
        }
    }

    return result;
}
