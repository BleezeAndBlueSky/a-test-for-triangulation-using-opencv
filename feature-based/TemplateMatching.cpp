#include <opencv2/opencv.hpp>
#include <iostream>

int method = CV_TM_SQDIFF;//Parameter specifying the comparison method

int main( int argc , char** argv )
{
    if(argc < 3)
        return -1;
    cv::Mat image, templ, result;
    image = cv::imread( argv[1]);
    templ = cv::imread( argv[2]);
    if(image.empty())
        return -1;
    if(templ.empty())
        return -1;
    cv::namedWindow( "source", 1);
    cv::namedWindow( "result", 1 );
    result.create( image.cols - templ.cols + 1, image.rows - templ.rows + 1, CV_32FC1 );

    cv::matchTemplate( image, templ, result, method );
    cv::normalize( result, result, 0, 1, cv::NORM_MINMAX, -1, cv::Mat() );

    double minVal; double maxVal;
    cv::Point minLoc, maxLoc;
    cv::minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, cv::Mat() );


    cv::Mat display;
    display = image.clone();
    cv::Point pt2( minLoc.x + templ.cols , minLoc.y + templ.rows );

    cv::rectangle( display, minLoc, pt2, CV_RGB(0,255,0) );
    cv::rectangle( result,  minLoc, pt2, CV_RGB(0,255,0) );

    imshow( "source", display );
    imshow( "result", result );


    cv::waitKey(0);
    return 0;
}

