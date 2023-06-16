//Пример для вывода изображения по адресу файла

#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <iostream>
#include <stdio.h>
using namespace std;
//using namespace cv;

int main(int argc, char** argv) {
    cv::Mat test_image = cv::imread("/home/sergei/opencv_build/opencv/Image1/OpenCV.jpg", cv::IMREAD_GRAYSCALE);
    //cv::namedWindow("Display Image");
    cv::imshow ("Image", test_image);

    cv::waitKey(0);

    cout << "ImageTest" << endl;
    return 0;
}