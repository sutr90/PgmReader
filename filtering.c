#include "filtering.h"
#include <math.h>

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

PGMImage *sobelFilter(PGMImage *img, char mode){
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

            if(mode == 'x'){
                result->data[x][y] = (unsigned char) ((gx+1020)/8);
            }

            if(mode == 'y') {
                result->data[x][y] = (unsigned char) ((gy + 1020) / 8);
            }

            if(mode == 'f'){
                    result->data[x][y] = (unsigned char) (sqrt(gx * gx + gy * gy));
            }
        }
    }

    return result;
}
