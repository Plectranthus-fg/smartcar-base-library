#include <iostream>
#include </usr/include/opencv4/opencv2/opencv.hpp>

#include "base_img.h"
#include "base_path.h"

#define filename "../photo28.txt"
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
//        output << "}" << std::endl;
//    }


    cv::Mat origin_pic(img_height, img_width, CV_8UC1, (uint8_t *) image);
    cv::imshow("origin_pic", origin_pic);
    cv::imwrite("final_img.png", origin_pic);

    auto histogram = img::Histo(*image);
    for (int i = 0; i < 256; i++) {
        std::cout << histogram[i] << "\t";
    }
    std::cout << std::endl;
    //uint8_t threshold = img::OtsuThreshold(histogram);
    uint8_t threshold = img::IterationThreshold(histogram);
    std::cout << unsigned(threshold) << std::endl;
    delete[]histogram;
    histogram = nullptr;
    img::Binarize(*image, threshold);
    img::GaussianConvolution(*image);
    cv::Mat alter_pic(img_height, img_width, CV_8UC1, (uint8_t *) image);
    cv::imshow("pic1", alter_pic);
    img::ImageFilter(*image);
    auto new_img = img::PerspectiveTransform(*image, 30);
    //img show
    auto circle = path::CircleInit(60);
    for (auto k = circle.begin(); k != circle.end() ; ++k) {
        new_img[k->y_][img_width - k->x_] = true;
    }
    cv::Mat tran(img_height, img_width, CV_8UC1);
    for (int k = 0; k < img_height; ++k) {
        for (int i = 0; i < img_width; ++i) {
            (new_img[k][img_width - i] == 1) ? tran.at<uint8_t>(k, i) = 0x00 : tran.at<uint8_t>(k, i) = 0xFF;
        }
    }
    cv::imshow("trans",tran);
    for (auto k = new_img.begin(); k != new_img.end() ; ++k) {
        std::cerr  << k->to_string() << std::endl;
    }
    //picture display
    cv::Mat final_pic(img_height, img_width, CV_8UC1, (uint8_t *) image);
    cv::imshow("pic2", final_pic);

    cv::waitKey();

//    // output the picture as number
//    for (int i = 0; i < img_height; i++) {
//        for (int j = 0; j < img_width; j++) {
//            std::cout <<  unsigned(image[j][i]) << "\t" ;
//        }
//        std::cout << std::endl;
//    }
}
