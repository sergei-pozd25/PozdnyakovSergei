#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/calib3d/calib3d.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/core/core.hpp>
#include <stdio.h>
#include <iostream>
#include <vector>

int CHESSBOARD[2] {6,9};

int main() {
    std::vector<std::vector<cv::Point3f> > objpoints;
    std::vector<std::vector<cv::Point2f> > imgpoints;
    std::vector<cv::Point3f> objp;
    for (int i{0} ; i<CHESSBOARD[1]; i++) {
        for (int j{0}; j<CHESSBOARD[0]; j++) {
            objp.push_back(cv::Point3f(j, i, 0));
        }
    }
    std::vector<cv::String> images;
    std::string path = "/home/sergei/Изображения/ChessBoard.png";
    cv::glob(path, images);
    cv::Mat frame, resized_frame, gray;
    std::vector<cv::Point2f> corner_pts;
    bool success;

    for (int i{0}; i<images.size(); i++) {
        frame = cv::imread(images[i]);
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

        success = cv::findChessboardCorners(gray, cv::Size(CHESSBOARD[0], CHESSBOARD[1]), corner_pts,
                                            cv::CALIB_CB_ADAPTIVE_THRESH | cv::CALIB_CB_NORMALIZE_IMAGE);


        if (success) {
            cv::TermCriteria criteria (cv::TermCriteria::EPS | cv::TermCriteria::MAX_ITER, 30, 0.001);
            cv::cornerSubPix(gray, corner_pts, cv::Size(11, 11), cv::Size(1, 1), criteria);
            cv::drawChessboardCorners(frame, cv::Size(CHESSBOARD[0], CHESSBOARD[1]), corner_pts, success);
            objpoints.push_back(objp);
            imgpoints.push_back(corner_pts);
        }
        else {
            std::cout << "No corners" << std::endl;
        }
        cv::resize(frame, resized_frame, cv::Size(), 1.5, 1.5, cv::INTER_LINEAR);
        cv::imshow(path, resized_frame);
        cv::waitKey(0);

    }

    cv::destroyAllWindows();
    cv::Mat cameraMatrix, distCoef, R, T;
    cv::calibrateCamera(objpoints, imgpoints, cv::Size(gray.rows, gray.cols), cameraMatrix, distCoef, R, T);

    std::cout << "cameraMatrix: " << cameraMatrix << std::endl;
    std::cout << "distCoef: " << distCoef << std::endl;
    std::cout << "Rotation vector: " << R << std::endl;
    std::cout << "Translation vector: " << T << std::endl;

    return 0;
}


/*
cv::Mat resized_image;
cv::Mat image = cv::imread(path, cv::IMREAD_GRAYSCALE);
cv::resize(image, resized_image, cv::Size(), 0.3, 0.3, cv::INTER_LINEAR);
cv::imshow(path, resized_image);
cv::waitKey(0);*/