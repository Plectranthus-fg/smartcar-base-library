//
// Created by plectranthus_fg on 2020/07/13.
//

#ifndef IMG_BASE_PATH_H
#define IMG_BASE_PATH_H

#include "base_img.h"
#include <vector>

namespace path {
    std::vector<img::Point> IntersectionCurveInit(int c);
    std::vector<img::Point> CircleInit(int r);
}

#endif //IMG_BASE_PATH_H
