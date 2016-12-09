//
// Created by VF on 9. 12. 2016.
//

#ifndef PGMREADER_FILTERING_H
#define PGMREADER_FILTERING_H

#include "pgm.h"

PGMImage *gaussFilter(PGMImage *img, unsigned int size);

PGMImage *sobelFilter(PGMImage *img, unsigned int size);

#endif //PGMREADER_FILTERING_H
