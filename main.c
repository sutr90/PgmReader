#include "pgm.h"
#include "filtering.h"

int main() {
    PGMImage *img, *img2;

    img = readPGMfile("D:\\tmp\\lenna.pgm");
//    savePGMImage("D:\\tmp\\lenna2.pgm", img);

//    img2 = gaussFilter(img);
//    savePGMImage("D:\\tmp\\gauss.pgm", img2);
//    freePGMImage(img2);
//
//    img2 = sobelFilter(img);
//    savePGMImage("D:\\tmp\\sobel.pgm", img2);
//    freePGMImage(img2);

    img2 = adaptiveFilter(img, 3, 8);
    savePGMImage("D:\\tmp\\adaptive.pgm", img2);

    freePGMImage(img);
    freePGMImage(img2);

    return 0;
}
