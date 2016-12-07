#include "pgm.h"

int main() {
    PGMImage *img;

    img = readPGMfile("D:\\tmp\\feep.pgm");

    savePGMImage("D:\\tmp\\feep2.pgm", img);

    freePGMImage(img);

    return 0;
}