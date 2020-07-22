//
// Created by plectranthus_fg on 2020/07/13.
//

#include "base_path.h"
#include <cmath>

namespace path {
    /*
    function: IntersectionCurveInit
    last edited: 2020/07/22 3:57
    last edit by: Plectranthus_fg
    description: generate the curve which will be intersected with the lane line
     y = -a * x^2 + c
     c means the roi area height
    */
    std::vector<img::Point> IntersectionCurveInit(int c) {
        double_t curve_width = (img_height - c) / img_height * img_width;
        double_t aDouble = 4 * c / pow(curve_width, 2);
        std::vector<img::Point> curve;
        img::Point cache;
        for (int i = (img_width - curve_width) / 2; i < (img_width + curve_width) / 2; ++i) {
            cache.x_ = i;
            cache.y_ = round(-1 * aDouble * pow(i - curve_width / 2, 2) + c);
            curve.push_back(cache);
        }
        return curve;
    }
}