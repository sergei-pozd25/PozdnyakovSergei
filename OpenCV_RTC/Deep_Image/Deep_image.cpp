#include <iostream>
#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/calib3d.hpp>


int num_disparity = 8;
int block_size = 5;

cv::Ptr<cv::StereoSGBM> stereo = cv::StereoSGBM::create();
cv::Mat disp, disparity;
cv::Mat imgl, imgr;
std::string disparity_window = "Disparity";


static void trackbar1(int, void*) {
    stereo ->setNumDisparities(num_disparity * 16);
    num_disparity = num_disparity * 16;
    stereo ->compute(imgl, imgr, disp);
    disp.convertTo(disparity, CV_8U);
    cv::applyColorMap(disparity, disparity, cv::COLORMAP_JET);
    cv::imshow(disparity_window.c_str(), disparity);
}


static void trackbar2(int, void*) {
    stereo ->setBlockSize(block_size);
    stereo ->compute(imgl, imgr, disp);
    disp.convertTo(disparity, CV_8U);
    cv::applyColorMap(disparity, disparity, cv::COLORMAP_JET);
    cv::imshow(disparity_window.c_str(), disparity);
}


int main() {
    /*std::string Left_name = "/home/sergei/Изображения/outside photo_1/Left_1.jpg";
    std::string Right_name = "/home/sergei/Изображения/outside photo_1/Right_1.jpg";*/

    std::string Left_name = "/home/sergei/Изображения/imgl.png";
    std::string Right_name = "/home/sergei/Изображения/imgr.png";

    imgl = cv::imread(Left_name);
    //cv::resize(imgl, imgl, cv::Size(), 0.5, 0.5, cv::INTER_LINEAR);
    //cv::cvtColor(imgl, imgl, cv::COLOR_BGR2GRAY);
    imgr = cv::imread(Right_name);
    //cv::resize(imgr, imgr, cv::Size(), 0.5, 0.5, cv::INTER_LINEAR);
    //cv::cvtColor(imgr, imgr, cv::COLOR_BGR2GRAY);
    cv::namedWindow(disparity_window, cv::WINDOW_NORMAL);
    cv::createTrackbar("numDisparities", disparity_window.c_str(), &num_disparity, 18, trackbar1);
    cv::createTrackbar("blockSize", disparity_window.c_str(), &block_size, 50, trackbar2);
    cv::waitKey();

    return 0;
}