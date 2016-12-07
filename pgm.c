//
// Code adapted from https://sun.iwu.edu/~shelley/sie/zoo/journal/
//

#include <stdio.h>
#include <stdlib.h>
#include "pgm.h"

PGMImage *readPGMfile(char *filename) {
    FILE *in_file;
    char ch;
    int row, col, type;
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
    if (type != 2) {
        fprintf(stderr, "ERROR(2): Not valid pgm/ppm file type\n");
        return NULL;
    }

    PGMImage *img = malloc(sizeof(PGMImage));

    while (getc(in_file) != '\n');             /* skip to end of line*/

    while (getc(in_file) == '#')              /* skip comment lines */
    {
        while (getc(in_file) != '\n');          /* skip to end of comment line */
    }

    fseek(in_file, -1, SEEK_CUR);             /* backup one character*/

    fscanf(in_file, "%d", &(img->width));
    fscanf(in_file, "%d", &(img->height));
    fscanf(in_file, "%d", &(img->maxVal));

    img->data = (unsigned char **) malloc((size_t) img->height);

    for (row = 0; row < img->height; row++) {
        img->data[row] = (unsigned char *) malloc((size_t) img->width);
        for (col = 0; col < img->width; col++) {
            fscanf(in_file, "%d", &ch_int);
            img->data[row][col] = (unsigned char) ch_int;
        }
        printf("\n");
    }

    fclose(in_file);
    return img;
}


void savePGMImage(char *fname, PGMImage *img) {
    int i, j;
    int gray;
    FILE *iop;

    iop = fopen(fname, "w");
    fprintf(iop, "P2\n");
    fprintf(iop, "%d %d\n", img->width, img->height);
    fprintf(iop, "255\n");

    for (i = 0; i < img->height; i++) {
        for (j = 0; j < img->width; j++) {
            gray = img->data[i][j];
            if (gray < 0) {
                printf("IMG_WRITE: Found value %d at row %d col %d\n", gray, i, j);
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
    int row;

    for (row = 0; row < img->height; row++) {
        free(img->data[row]);
    }
    free(img->data);
}
