// opencv 3.1.0 ,  xfeatures2d example code  .
// Add the include path and link the xfeatures2d module first 

#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <opencv2/xfeatures2d.hpp>
int main(int argc, char** argv)
{
    if(argc < 2)
        return -1;
    cv::Mat image1 = cv::imread(argv[1]);
    cv::cvtColor(image1,image1,CV_BGR2GRAY);
    std::vector<cv::Point2f> corners;
    cv::goodFeaturesToTrack(image1,corners,500,1,10);
    cv::Mat corner(image1.size(), CV_32FC1,cv::Scalar(255));
    for (auto a : corners)
        corner.at<uchar>(a) = 0;

    std::vector<cv::KeyPoint> keypoints;
    cv::Ptr<cv::FeatureDetector> fast =
            cv::FastFeatureDetector::create (10, true,cv::FastFeatureDetector::TYPE_9_16 );
    fast -> detect(image1,keypoints);
    cv::drawKeypoints(image1,keypoints,image1,cv::Scalar(0,255,0),0);

    std::vector<cv::KeyPoint> skeypoints;
    cv::Ptr<cv::xfeatures2d::SIFT> sift =
            cv::xfeatures2d::SIFT::create(10);
    sift -> detect(image1,skeypoints);
    cv::Mat image2;
    cv::drawKeypoints(image1,skeypoints,image2,cv::Scalar(0,255,0),0);
    cv::imshow("sift",image2);



    cv::namedWindow("corner",1);
    cv::namedWindow("image",1);
    cv::imshow("image",image1);
    cv::imshow("corner",corner);
    cv::waitKey(0);




}












