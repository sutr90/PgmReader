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

PGMImage *gaussFilter(PGMImage *img) {
    PGMImage *result = createPGMImage(img->width - 2, img->height - 2);

    for (unsigned int y = 0; y < result->height; y++) {
        for (unsigned int x = 0; x < result->width; x++) {
            double g = gaussKernel[0][0] * getValue(img, x, y) +
                       gaussKernel[0][1] * getValue(img, x, y + 1) +
                       gaussKernel[0][2] * getValue(img, x, y + 2) +
                       gaussKernel[1][0] * getValue(img, x + 1, y) +
                       gaussKernel[1][1] * getValue(img, x + 1, y + 1) +
                       gaussKernel[1][2] * getValue(img, x + 1, y + 2) +
                       gaussKernel[2][0] * getValue(img, x + 2, y) +
                       gaussKernel[2][1] * getValue(img, x + 2, y + 1) +
                       gaussKernel[2][2] * getValue(img, x + 2, y + 2);

            setValue(result, x, y, (unsigned char) g);
        }
    }

    return result;
}

PGMImage *sobelFilter(PGMImage *img) {
    PGMImage *result = createPGMImage(img->width - 2, img->height - 2);

    for (unsigned int y = 0; y < img->height - 2; y++) {
        for (unsigned int x = 0; x < img->width - 2; x++) {
            double gx = sobelXKernel[0][0] * getValue(img, x, y) +
                        sobelXKernel[0][1] * getValue(img, x, y + 1) +
                        sobelXKernel[0][2] * getValue(img, x, y + 2) +
                        sobelXKernel[1][0] * getValue(img, x + 1, y) +
                        sobelXKernel[1][1] * getValue(img, x + 1, y + 1) +
                        sobelXKernel[1][2] * getValue(img, x + 1, y + 2) +
                        sobelXKernel[2][0] * getValue(img, x + 2, y) +
                        sobelXKernel[2][1] * getValue(img, x + 2, y + 1) +
                        sobelXKernel[2][2] * getValue(img, x + 2, y + 2);

            int gy = sobelYKernel[0][0] * getValue(img, x, y) +
                     sobelYKernel[0][1] * getValue(img, x, y + 1) +
                     sobelYKernel[0][2] * getValue(img, x, y + 2) +
                     sobelYKernel[1][0] * getValue(img, x + 1, y) +
                     sobelYKernel[1][1] * getValue(img, x + 1, y + 1) +
                     sobelYKernel[1][2] * getValue(img, x + 1, y + 2) +
                     sobelYKernel[2][0] * getValue(img, x + 2, y) +
                     sobelYKernel[2][1] * getValue(img, x + 2, y + 1) +
                     sobelYKernel[2][2] * getValue(img, x + 2, y + 2);

            setValue(result, x, y, (unsigned char) sqrt(gx * gx + gy * gy));
        }
    }

    return result;
}

double getNeighborhoodMean(PGMImage *img, int x, int y, int size) {
    int acc = 0;
    for (int i = -(size / 2); i <= (size / 2); i++) {
        for (int j = -(size / 2); j <= (size / 2); j++) {
            acc += getValue(img, (unsigned int) (x + i), (unsigned int) (y + j));
        }
    }
    return acc / (double) (size * size);
}

PGMImage *adaptiveFilter(PGMImage *img, unsigned int size, unsigned int C) {
    unsigned int border = size / 2;
    PGMImage *result = createPGMImage(img->width + 1 - size, img->height + 1 - size);


    for (unsigned int y = border; y < img->height - border - 2; y++) {
        for (unsigned int x = border; x < img->width - border - 2; x++) {
            double mean = getNeighborhoodMean(img, x, y, size);
            if (getValue(img, x, y) > (mean - C)) {
                setValue(result, x - border, y - border, 255);
            } else {
                setValue(result, x - border, y - border, 0);
            }
        }
    }

    return result;
}

