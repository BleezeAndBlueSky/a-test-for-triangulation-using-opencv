/* 
 * opencv computer vision application programming cookbook 2nd edition
 * demo for the example class file harrisdetector
 */

#include <iostream>
#include <opencv2/opencv.hpp>
#include "harrisdetector.h"

int main(int argc, char **argv)
{
    if (argc < 2)
        return -1;
    cv::Mat image = cv::imread(argv[1]);
    cv::cvtColor(image,image,CV_RGB2GRAY);
    
    HarrisDetector harris;
    // Compute Harris values
    harris.detect(image);
    // Detect Harris corners
    std::vector<cv::Point> pts;
    harris.getCorners(pts,0.02);
    // Draw Harris corners
    harris.drawOnImage(image,pts);
    cv::namedWindow("harriscorner",1);
    cv::imshow("harriscorner", image);


    cv::waitKey(0);
    return 0;


}
