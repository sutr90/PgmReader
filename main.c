#include "pgm.h"
#include "filtering.h"

int main() {
    PGMImage *img, *img2;

    img = readPGMfile("/home/jose/Downloads/lena512.pgm");
    savePGMImage("/home/jose/Downloads/lena.pgm", img);

    img2 = sobelFilter(img, 'y');
    savePGMImage("/home/jose/Downloads/sobel.pgm", img2);
    freePGMImage(img2);
    freePGMImage(img);

    return 0;
}
