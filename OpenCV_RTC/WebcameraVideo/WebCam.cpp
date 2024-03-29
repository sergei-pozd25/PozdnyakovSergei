#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/core/core.hpp>
#include <iostream>

using namespace std;


class Camera_Exceptions: public std::domain_error {
public:
    Camera_Exceptions(const char* const error) : std::domain_error(error) {}
};

Camera_Exceptions NO_CAMERA ("Сamera with this index is not connected");


int main(int argc, char** argv) {
    cv::Mat video, video_resized;
    string cam_name;
    cv::VideoCapture capture;
    unsigned int index;
    cin >> index;
    capture.open(index);

    switch (index) {
        case 0: cam_name = "Laptop webcam";
            break;
        case 1 ... 9: cam_name = "Not built-in camera";
            break;
    }

    cout << cam_name << endl;


    while (1) {
        capture >> video;
        if (video.empty()) break;
        cv::resize(video, video_resized, cv::Size(), 0.5, 0.5, cv::INTER_NEAREST);
        // resize output video
        cv::imshow(cam_name, video_resized);
        // output video on screen
        if (cv::waitKey(40) >= 0) break;  //click any button to turn video off
    }
    return 0;
}