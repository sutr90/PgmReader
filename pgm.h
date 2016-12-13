//
// Code adapted from https://sun.iwu.edu/~shelley/sie/zoo/journal/
//

#ifndef PGMREADER_PGM_H
#define PGMREADER_PGM_H

/**
 * Struktura popisujici obrazek
 */
typedef struct PGMstructure {
    /** sirka obrazku */
    unsigned int width;
    /** vyska obrazku */
    unsigned int height;
    /**
     * Jednotlive pixely, ulozene ve 2D poli, po radcich.
     * Jedna se o pole poli, kdy kazde pole ma width prvku, celkem je zde height poli.
     * K jednotlivym pixelum je mozno pristupovat stylem img->data[y][x].
     * Pozor na prohozene poradi souradnic!!
     */
    unsigned char **data;
    unsigned int maxVal; /* vzdy 255 */
} PGMImage;

/**
 * Nacte obrazek ze souboru.
 */
PGMImage *readPGMfile(char *filename);

/**
 * Ulozi obrazek do souboru.
 */
void savePGMImage(char *fname, PGMImage *img);

/**
 * Uvolni pamet.
 */
void freePGMImage(PGMImage *img);

#endif //PGMREADER_PGM_H
