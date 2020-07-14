//
// Created by plectranthus_fg on 2020/07/13.
//

#ifndef IMG_BASE_IMG_H
#define IMG_BASE_IMG_H

#ifndef img_height
#define img_height 40
#endif
#ifndef img_width
#define img_width 200
#endif

#include "cstdint"
#include <bitset>
#include <vector>

extern int pixel_total;
namespace img {
    int *Histo(uint8_t *img);

    uint8_t OtsuThreshold(int *histogram);

    int Binarize(uint8_t *img, uint8_t threshold);

    uint8_t IterationThreshold(int *histogram);

    typedef struct {
        int x, y;
    } point;
}
#endif //IMG_BASE_IMG_H
