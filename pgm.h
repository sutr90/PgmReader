//
// Code adapted from https://sun.iwu.edu/~shelley/sie/zoo/journal/
//

#ifndef PGMREADER_PGM_H
#define PGMREADER_PGM_H

typedef struct PGMstructure {
    unsigned int width;
    unsigned int height;
    unsigned char *data;
    unsigned int maxVal;
} PGMImage;

PGMImage *readPGMfile(char *filename);

void savePGMImage(char *fname, PGMImage *img);

void freePGMImage(PGMImage *img);

PGMImage *createPGMImage(unsigned int width, unsigned int height);

void setValue(PGMImage *img, unsigned int x, unsigned int y, unsigned char value);

unsigned char getValue(PGMImage *img, unsigned int x, unsigned int y);

#endif //PGMREADER_PGM_H
