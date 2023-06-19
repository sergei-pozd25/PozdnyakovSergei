#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/core/core.hpp>
#include <iostream>

using namespace std;
using namespace cv;


class Camera_Exceptions: public std::domain_error {
public:
    Camera_Exceptions(const char* const error) : std::domain_error(error) {}
};

Camera_Exceptions NO_CAMERA ("Сamera with this index is not connected");


int main(int argc, char** argv) {
    Mat video, video_resized;
    string cam_name;
    VideoCapture capture;
    unsigned int index;
    cin >> index;
    capture.open(index);

    switch (index) {
        case 0: cam_name = "Laptop webcam";
            break;
        case 1 ... 9: cam_name = "Not built-in camera";
            break; }

    while (1) {
        capture >> video;
        if (video.empty()) break;
        resize(video, video_resized, Size(), 0.5, 0.5, INTER_NEAREST);
        // resize output video
        imshow(cam_name, video_resized);
        // output video on screen
        if (waitKey(40) >= 0) break;  //click any button to turn video off
    }
    cout << cam_name << endl;
    return 0;
}