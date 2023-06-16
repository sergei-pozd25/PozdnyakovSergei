//Пример для вывод изображения с вебкамеры на монитор

#include <opencv4/opencv2/opencv.hpp>
#include "opencv4/opencv2/videoio.hpp"
#include <opencv4/opencv2/core/utility.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include "opencv4/opencv2/highgui.hpp"
#include <opencv4/opencv2/core/core.hpp>
#include <iostream>
#include <stdio.h>
#include "opencv4/opencv2/opencv_modules.hpp"


using namespace std;
using namespace cv;


int main(int argc, char* argv[]) {
    VideoCapture cap(0);
    if (cap.isOpened == false) {
        cout << "Cannot open" << endl;
        cin.get();
        return -1;
    }

    double dWigth = cap.get(CAP_PROP_FRAME_WIDTH);
    double dHeight = cap.get(CAP_PROP_FRAME_HEIGHT);

    cout << "Resolution" << dWigth << " x " << dHeight << endl;

    string window_name = "Camera";
    namedWindow(window_name);

    while (1) {
        Mat frame;
        bool bSuccess = cap.read(frame);
        if (!bSuccess) {
            cout << "Disconnected" << endl;
            cin.get();
            break;
        }

        imshow(window_name, frame);

        if (waitKey(10) = 27) {
            cout << "Esc was pressed by user" << endl;
            break;
        }
    }
    return 0;
}