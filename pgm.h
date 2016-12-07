//
// Code adapted from https://sun.iwu.edu/~shelley/sie/zoo/journal/
//

#ifndef PGMREADER_PGM_H
#define PGMREADER_PGM_H

typedef struct PGMstructure {
    int width;
    int height;
    unsigned char **data;
    int maxVal;
} PGMImage;

PGMImage *readPGMfile(char *filename);

void savePGMImage(char *fname, PGMImage *img);

void freePGMImage(PGMImage *img);

#endif //PGMREADER_PGM_H
