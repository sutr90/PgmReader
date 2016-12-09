//
// Created by VF on 9. 12. 2016.
//

#ifndef PGMREADER_FILTERING_H
#define PGMREADER_FILTERING_H

#include "pgm.h"

PGMImage *gaussFilter(PGMImage *img);

PGMImage *sobelFilter(PGMImage *img);

PGMImage *adaptiveFilter(PGMImage *img, unsigned int size, unsigned int C);

#endif //PGMREADER_FILTERING_H
