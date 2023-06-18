#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
    string image_path = "/home/sergei/Изображения/SSO_Plamya.jpg";  // can be variable
    cv::Mat test_image = cv::imread(image_path, cv::IMREAD_GRAYSCALE);  // black and white output
    cv::resize(test_image, test_image, Size(), 0.7, 0.7, INTER_LINEAR);
    // resize output image
    //cv::namedWindow("Display Image");
    cv::imshow (image_path, test_image);  // output

    cv::waitKey(0);  // end after button click by user

    cout << "ImageTest" << endl;  // test output to understand that program works
    return 0;
}