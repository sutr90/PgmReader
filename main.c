#include "pgm.h"

int main() {
    PGMImage *img;

    img = readPGMfile("lenna.pgm");

    savePGMImage("lenna2.pgm", img);

    freePGMImage(img);

    return 0;
}
