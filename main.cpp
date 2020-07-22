#include <iostream>
#include </usr/include/opencv4/opencv2/opencv.hpp>

#include "base_img.h"
#include "base_path.h"

#define filename "../Left.txt"
// #define output_file "../output_img_1.txt"

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
            buf << std::hex << word;
            buf >> input_value;
            image[i][j] = input_value;
        }
    }
//    std::ofstream output(output_file);
//
//    for (int i = 0; i < img_height; i++) {
//        output << "{";
//        for (int j = 0; j < img_width; j++) {
//            (j != img_width - 1)?
//            output << (unsigned) image[i][j] << ",":output << (unsigned) image[i][j];
//        }
//        output << "}" <<std::endl;
//    }


    cv::Mat origin_pic(img_height, img_width, CV_8UC1, (uint8_t*)image );
    cv::imshow("origin_pic",origin_pic);

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
    img::GaussianConvolution(*image);
    cv::Mat alter_pic(img_height, img_width, CV_8UC1, (uint8_t*)image );
    cv::imshow("pic1",alter_pic);
    img::ImageFilter(*image);
    auto curve = path::IntersectionCurveInit(50);
    for (auto k = curve.begin(); k != curve.end() ; ++k) {
        image[img_height - 1 - k->y_][k->x_] = 0x00;
    }
    curve = path::IntersectionCurveInit(75);
    for (auto k = curve.begin(); k != curve.end() ; ++k) {
        image[img_height - 1 - k->y_][k->x_] = 0x00;
    }
    curve = path::IntersectionCurveInit(100);
    for (auto k = curve.begin(); k != curve.end() ; ++k) {
        image[img_height - 1 - k->y_][k->x_] = 0x00;
    }
    curve = path::IntersectionCurveInit(25);
    for (auto k = curve.begin(); k != curve.end() ; ++k) {
        image[img_height - 1 - k->y_][k->x_] = 0x00;
    }
    //picture display
    cv::Mat final_pic(img_height, img_width, CV_8UC1, (uint8_t*)image );
    cv::imshow("pic2",final_pic);
    cv::imwrite("final_img.png",final_pic);
    cv::waitKey();

//    // output the picture as number
//    for (int i = 0; i < img_height; i++) {
//        for (int j = 0; j < img_width; j++) {
//            std::cout <<  unsigned(image[j][i]) << "\t" ;
//        }
//        std::cout << std::endl;
//    }
}
