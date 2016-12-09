#include "pgm.h"
#include "filtering.h"

int main() {
    PGMImage *img, *img2;

    img = readPGMfile("D:\\tmp\\lenna.pgm");

    img2 = sobelFilter(img, 0);

    savePGMImage("D:\\tmp\\rand.pgm", img2);

    freePGMImage(img);
    freePGMImage(img2);

    return 0;
}
