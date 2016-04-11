#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
int main()
{
    Mat image = imread("/home/tau/opencv/opencv-3.1.0/samples/data/blox.jpg",0);
//    uchar* it = image.ptr<uchar>;
    cv::MatIterator_<uchar> it = image.begin<uchar>();
    cv::MatIterator_<uchar> itend = image.end<uchar>();
    for(; it != itend; it++)
    {
      std::cout << *it ;

    }


}
