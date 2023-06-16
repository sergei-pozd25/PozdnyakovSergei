#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/core/core.hpp>
#include <iostream>
#include <stdio.h>
using namespace std;
//using namespace cv;

using namespace std;
using namespace cv;

int main(int argc, char** argv) {

    cv::Mat frame;
    cv::VideoCapture capture;
    capture.open("");
    for (;;) {
        capture>>frame;
        if (frame.empty()) break;
        cv::imshow("Window", frame);
        if (cv::waitKey(30)>=0) break;
    }

    cout << "Test Video" << endl;
    return 0;
}