#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
int main(int argc, char** argv)
{
    if(argc < 2)
        return -1;
    cv::Mat image1 = cv::imread(argv[1]);
    cv::cvtColor(image1,image1,CV_BGR2GRAY);
    std::vector<cv::Point2f> corners;
    cv::goodFeaturesToTrack(image1,corners,500,0.01,10);
    cv::Mat corner(image1.size(), CV_32FC1,cv::Scalar(255));
    for (auto a : corners)
        corner.at<uchar>(a) = 0;
    cv::namedWindow("corner",1);
    cv::namedWindow("image",1);
    cv::imshow("image",image1);
    cv::imshow("corner",corner);
    cv::waitKey(0);




}
