#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/core/core.hpp>
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {

    Mat frame;
    VideoCapture capture;
    capture.open(0);

    while (1) {
        capture >> frame;

        if (frame.empty()) break;

        imshow("W", frame);

        if (waitKey(30) >= 0) break;
        //click escape button to turn video off
    }
    cout << "Video test" << endl;
    return 0;
}
