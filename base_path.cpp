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
    /*!!!unusable!!! need fix*/
    std::vector<img::Point> IntersectionCurveInit(int c) {
        int curve_width = ((img_height - c) / (double_t) img_height) * img_width;
        double_t aDouble = 4 * c / pow(curve_width, 2);
        std::vector<img::Point> curve;
        img::Point cache;
        for (int i = (img_width + 1 - curve_width) / 2; i < (img_width + curve_width - 1) / 2; ++i) {
            cache.x_ = i;
            cache.y_ = round(-1 * aDouble * pow(i - img_width / 2, 2) + c);
            curve.push_back(cache);
        }
        return curve;
    }

    /*
    function: CircleInit
    last edited: 2020/07/25 18:32
    last edit by: Plectranthus_fg
    description: generate the circle which will be intersected with the lane line
    (x - x0)^2 + (y - y0)^2 = r
     x0 = img_width / 2
     y0 = 0
     x = sqrt(r - y^2) + img-width / 2
     y = sqrt(r - (x - img_width/2)^2)
    */
    std::vector<img::Point> CircleInit(int r) {
        std::vector<img::Point> circle;
        img::Point cache;
        int y_next;
        int y_cache;
        for (int x = img_width / 2 - r; x < img_width / 2 + r; ++x) {
            // calc the point on circle
            cache.x_ = x;
            cache.y_ = img_height - 1 - sqrt(r * r - pow(x - img_width / 2, 2));
            circle.push_back(cache);

            // make the circle close
            y_next = img_height - 1 - sqrt(r * r - pow(x + 1 - img_width / 2, 2));
            y_cache = cache.y_;
            if (y_next - y_cache >= 1) {
                for (int i = y_cache; i < y_next; ++i) {
                    cache.y_ = i;
                    circle.push_back(cache);
                }
            }
            if (y_cache - y_next >= 1) {
                for (int i = y_next; i < y_cache; ++i) {
                    cache.y_ = i;
                    circle.push_back(cache);
                }
            }
        }
        return circle;
    }

    double AngleCalc(std::vector<std::bitset<img_width>> &img, std::vector<img::Point> &Circle, int road_width) {

    }
}