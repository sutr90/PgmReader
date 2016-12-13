#include "filtering.h"
#include <stdio.h>
#include <math.h>


/*
 * Sobeluv filtr pro smer X.
 */
int sobelXKernel[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
};


/*
 * Sobeluv filtr pro smer Y.
 */
int sobelYKernel[3][3] = {
        {-1, -2, -1},
        {0,  0,  0},
        {1,  2,  1}
};

PGMImage *sobelFilter(PGMImage *img, char mode){
    return NULL;
}
