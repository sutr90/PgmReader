//
// Created by VF on 9. 12. 2016.
//

#include "filtering.h"
#include <math.h>
#include <stdio.h>

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

PGMImage *sobelFilter(PGMImage *img) {
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

            //printf("%d\n", (gx+1020)/8);

            result->data[x][y] = (unsigned char) ((gx+1020)/8);//sqrt(gx * gx + gy * gy);
        }
    }

    return result;
}

double getNeighborhoodMean(PGMImage *img, int x, int y, int size) {
    int acc = 0;
    for (int i = -(size / 2); i <= (size / 2); i++) {
        for (int j = -(size / 2); j <= (size / 2); j++) {
            acc += img->data[y+j][x+i];
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
            if (img->data[y][x] > (mean - C)) {
                result->data[y - border][x - border] = 255;
            } else {
                result->data[y - border][x - border] = 0;
            }
        }
    }

    return result;
}

