#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int histSize = 256;

float range[] = { 0, 256 } ;
const float* histRange = { range };


int thresh = 0;
const double thresh_maxval = 255;
const int thresh_type = CV_THRESH_BINARY;
int hist_w = 512;
int hist_h = 400;
int bin_w = cvRound( (double) hist_w/histSize );

Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );
Mat src;
Mat hist;
Mat dst;
void changeThreshAndShowResult(int,void*){
    histImage = 0;
    for( int i = 1; i < histSize; i++ )
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(hist.at<float>(i-1)) ) ,
                         Point( bin_w*(i), hist_h - cvRound(hist.at<float>(i)) ),
                         Scalar( 255, 0, 0), 2, 8, 0  );

    line(histImage,Point(thresh,0),Point(thresh,hist_h),Scalar(255,255,255));
    cv::threshold(src,dst,thresh,thresh_maxval,thresh_type);
    imshow("threshold",dst);
    imshow("calcHist Demo", histImage );
}



int main(int argc, char** argv)
{

    String imageName( "/home/tau/Pictures/Screenshot from 2016-10-23 07:57:38.png" );

    if (argc > 1)
        imageName = argv[1];


    src = imread(imageName,IMREAD_GRAYSCALE);

    if(src.empty())  return -1;

    calcHist( &src, 1, 0, Mat(), hist, 1, &histSize, &histRange, true, false );
    imshow("hist",hist);

    normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );

    for( int i = 1; i < histSize; i++ )
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(hist.at<float>(i-1)) ) ,
                       Point( bin_w*(i), hist_h - cvRound(hist.at<float>(i)) ),
                       Scalar( 255, 0, 0), 2, 8, 0  );

    for( int i = 1; i < histSize; i++ )
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(hist.at<float>(i-1)) ) ,
                         Point( bin_w*(i), hist_h - cvRound(hist.at<float>(i)) ),
                         Scalar( 255, 0, 0), 2, 8, 0  );
    line(histImage,Point(thresh,0),Point(thresh,hist_h),Scalar(255,255,255));
    threshold(src,dst,thresh,thresh_maxval,thresh_type);

    namedWindow("calcHist Demo", WINDOW_AUTOSIZE );
    cv::createTrackbar("thresh:","calcHist Demo",&thresh,256,changeThreshAndShowResult,NULL);
    imshow("calcHist Demo", histImage );
    imshow("threshold",dst);
    imshow("src",src);
    waitKey(0);

    return 0;

}
