//
// Created by VF on 9. 12. 2016.
//

#ifndef PGMREADER_FILTERING_H
#define PGMREADER_FILTERING_H

#include "pgm.h"

/*
 * +---+---...
 * |abc|
 * |def|         +---+
 * |ghi|         |123|
 * +---+         |456| ==> G = a*1 + b*2 + c*3 + d*4 + e*5 + f*6 + h*7 + g*9
 * |             |789|
 * .             +---+
 * .
 *
 *
 * @brief Vypocita konvoluci obrazku se Sobelovym operatorem.
 * @param    img            vstupni obrazek
 * @param   mode[x, y, f]   rezim vypoctu, ovlivni vystupni obrazek
 *              x - vystupem je aproximace derivace ve smeru X - ( G_x() + 1020 ) / 8
 *              y - vystupem je aproximace derivace ve smeru Y - ( G_y() + 1020 ) / 8
 *              f - vystupem je aproximace gradientu - sqrt( G_y()^2 + G_y()^2 )
 * @return vysledek konvoluce
 */
PGMImage *sobelFilter(PGMImage *img, char mode);

#endif //PGMREADER_FILTERING_H
