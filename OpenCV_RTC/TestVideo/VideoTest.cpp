#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/core/core.hpp>
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
    Mat video;
    VideoCapture capture;
    string filename = "/home/sergei/Видео/BOATS.MOV";
    capture.open(filename);

    while (1) {
        capture >> video;

        if (video.empty()) break;

        resize(video, video, Size(), 0.5, 0.5, INTER_NEAREST);
        // resize output video
        imshow(filename, video);
        // output video on screen
        if (waitKey(30) >= 0) break;
        //click escape button to turn video off
    }
    cout << filename << endl;
    return 0;
}
