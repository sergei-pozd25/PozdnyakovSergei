#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/videoio.hpp>
#include <opencv4/opencv2/core/utility.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/core/core.hpp>
#include <iostream>
#include <stdio.h>
using namespace std;
//using namespace cv;

using namespace std;
using namespace cv;

int main() {

    Mat image;
    namedWindow("Video");
    VideoCapture cap(0);
    if (cap.isOpened()) {
        cout << "cannot open" << endl;
    }
    for (;;) {
        cap >> image;
        imshow("Display window", image);
        waitKey(25);
    }
    return 0;
}