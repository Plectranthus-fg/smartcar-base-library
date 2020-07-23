//
// Created by plectranthus_fg on 2020/07/13.
//

#ifndef IMG_BASE_IMG_H
#define IMG_BASE_IMG_H

#ifndef img_width
#define img_width 188
#endif
#ifndef img_height
#define img_height 120
#endif

#include <cstdint>
#include <bitset>
#include <vector>
#include <cstring>

extern int pixel_total;
namespace img {
    int *Histo(uint8_t *img);
    uint8_t OtsuThreshold(int *histogram);
    int Binarize(uint8_t *img, uint8_t threshold);
    uint8_t IterationThreshold(int *histogram);
    int GaussianConvolution(uint8_t *img);
    int ImageFilter(uint8_t *img);

    class Point{
        public:
            int x_,y_;
    };
    std::vector<std::bitset<img_width>> PerspectiveTransform(uint8_t *img, int bottom_width);
}
#endif //IMG_BASE_IMG_H
