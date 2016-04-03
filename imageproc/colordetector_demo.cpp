/*
 * opencv computer vision programming cookbook 2nd edition
 * example code 
 * demo for ColorDetector
 */
 

#include "ColorDetector.h"

int main(int argc, char** argv)
{
    if(argc < 2)
        return -1;
    ColorDetector cdetect;
    ColorDetector ccdetect(80,(23,23,23)); //for test
    cv::Mat image = cv::imread(argv[1]);
    if(image.empty())
        return -1;
    cdetect.setTargetColor(230,190,130);
    cv::namedWindow("result",cv::WINDOW_AUTOSIZE);
    cv::waitKey(0);
    return 0;

}



