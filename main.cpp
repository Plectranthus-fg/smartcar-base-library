#include <iostream>
#include </usr/include/opencv4/opencv2/opencv.hpp>

#include "base_img.h"

#define filename "../picture_fixed.txt"

#include <vector>

int main() {
    uint8_t image[img_height][img_width];
    std::ifstream image_txt(filename, std::ios::binary);
    if (!image_txt.is_open()) {
        std::cout << "failed to open " << filename << '\n';
    }

    for (int i = 0; i < img_height; i++) {
        for (int j = 0; j < img_width; j++) {
            std::string word;
            std::stringstream buf;
            int input_value;
            buf.clear();
            image_txt >> word;
            buf << std::dec << word;
            buf >> input_value;
            image[i][j] = input_value;
        }
    }
    auto histogram = img::Histo(*image);
    for (int i = 0; i < 256; i++) {
        std::cout << histogram[i] << "\t";
    }
    std::cout << std::endl;
    uint8_t threshold = img::OtsuThreshold(histogram);
//    uint8_t threshold = img::IterationThreshold(histogram);
    std::cout << unsigned(threshold) << std::endl;
    delete []histogram;
    img::Binarize(*image,threshold);

    //picture display
    cv::Mat mat(img_height, img_width, CV_8UC1, (uint8_t*)image );
    cv::imshow("pic",mat);
    cv::waitKey();

//    // output the picture as number
//    for (int i = 0; i < img_height; i++) {
//        for (int j = 0; j < img_width; j++) {
//            std::cout <<  unsigned(image[j][i]) << "\t" ;
//        }
//        std::cout << std::endl;
//    }
}
