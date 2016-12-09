//
// Created by VF on 9. 12. 2016.
//

#ifndef PGMREADER_FILTERING_H
#define PGMREADER_FILTERING_H

#include "pgm.h"

float gaussKernel[3][3] = {
        {0.077847, 0.123317, 0.077847},
        {0.123317, 0.195346, 0.123317},
        {0.077847, 0.123317, 0.077847}
};

PGMImage *gaussFilter(PGMImage *img, unsigned int size);

#endif //PGMREADER_FILTERING_H
