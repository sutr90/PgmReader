//
// Code adapted from https://sun.iwu.edu/~shelley/sie/zoo/journal/
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "pgm.h"


int fpeek(FILE *stream) {
    int c;

    c = fgetc(stream);
    ungetc(c, stream);

    return c;
}

void skipComment(FILE *stream) {
    while ((char) fpeek(stream) == '#')              /* skip comment lines */
    {
        while ((char) getc(stream) != '\n');          /* skip to end of comment line */
    }
}

void skipWhitespace(FILE *stream) {
    while (isspace(fpeek(stream))) getc(stream);
}

void skipWhitespaceComment(FILE *stream) {
    skipWhitespace(stream);
    skipComment(stream);
}

PGMImage *readPGMfile(char *filename) {
    FILE *in_file;
    char ch;
    int type;
    unsigned int y;
    unsigned int x;
    int ch_int;

    in_file = fopen(filename, "r");
    if (in_file == NULL) {
        fprintf(stderr, "ERROR: Unable to open file %s\n\n", filename);
        return NULL;
    }

    ch = (char) getc(in_file);
    if (ch != 'P') {
        fprintf(stderr, "ERROR(1): Not valid pgm/ppm file type\n");
        return NULL;
    }
    ch = (char) getc(in_file);

    type = ch - '0';
    if ((type != 2) && (type != 5)) {
        fprintf(stderr, "ERROR(2): Not valid pgm/ppm file type\n");
        return NULL;
    }

    skipWhitespaceComment(in_file);

    PGMImage *img = malloc(sizeof(PGMImage));
    fscanf(in_file, "%d", &(img->width));
    fscanf(in_file, "%d", &(img->height));
    fscanf(in_file, "%d", &(img->maxVal));
    getc(in_file); // line end

    if (type == 5) {
        fclose(in_file);
        in_file = fopen(filename, "rb");

        /* magic number */
        fgetc(in_file);
        fgetc(in_file);
        skipWhitespaceComment(in_file);
        /* width */
        while (!isspace(fpeek(in_file))) { getc(in_file); }
        skipWhitespaceComment(in_file);
        /* height */
        while (!isspace(fpeek(in_file))) { getc(in_file); }
        skipWhitespaceComment(in_file);
        /* maxval */
        while (!isspace(fpeek(in_file))) { getc(in_file); }
        skipWhitespaceComment(in_file);
    }

    img->data = (unsigned char *) malloc(img->width * img->height);
    for (y = 0; y < img->height; y++) {
        for (x = 0; x < img->width; x++) {
            if (type == 5) {
                ch_int = fgetc(in_file);
            } else {
                fscanf(in_file, "%d", &ch_int);
            }

            setValue(img, x, y, (unsigned char) ch_int);
        }
    }

    fclose(in_file);
    return img;
}

void savePGMImage(char *fname, PGMImage *img) {
    unsigned int x;
    unsigned int y;
    int gray = 0;
    FILE *iop;

    iop = fopen(fname, "w");
    fprintf(iop, "P2\n");
    fprintf(iop, "%d %d\n", img->width, img->height);
    fprintf(iop, "%d\n", img->maxVal);

    for (y = 0; y < img->height; y++) {
        for (x = 0; x < img->width; x++) {
            gray = getValue(img, x, y);
            if (gray < 0) {
                printf("IMG_WRITE: Found value %d at row %d col %d\n", gray, y, x);
                printf("           Setting gray to zero\n");
                gray = 0;
            }
            fprintf(iop, "%3d ", gray);
        }
        fprintf(iop, "\n");
    }
    fprintf(iop, "\n");
    fclose(iop);
}

void freePGMImage(PGMImage *img) {
    free(img->data);
    free(img);
}

PGMImage *createPGMImage(unsigned int width, unsigned int height) {
    PGMImage *img = malloc(sizeof(PGMImage));
    img->width = width;
    img->height = height;
    img->maxVal = 255;
    img->data = malloc(img->height * img->height);
    return img;
}

void setValue(PGMImage *img, unsigned int x, unsigned int y, unsigned char value) {
    img->data[y * img->width + x] = value;
}

unsigned char getValue(PGMImage *img, unsigned int x, unsigned int y) {
    return img->data[y * img->width + x];
}