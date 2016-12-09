#include "pgm.h"

int main() {
    PGMImage *img;

    img = readPGMfile("D:\\tmp\\lenna.pgm");

    savePGMImage("D:\\tmp\\lenna2.pgm", img);

    freePGMImage(img);

    return 0;
}