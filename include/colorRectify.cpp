// to configue out the lowerb and upperb in colorExtractor
#include "plate.h"
#include <opencv2/opencv.hpp>
using namespace std;

int minHue(0), maxHue(180),minSat(0),maxSat(255),minVal(0),maxVal(255);
char msg[10];
cv::Scalar lowerb(minHue,minSat,minVal),
           upperb(maxHue,maxSat,maxVal);
cv::Mat img = cv::imread("/home/tau/Pictures/chepai.jpg");

int main()
{
    cv::imshow("img",img);
    cv::Mat dst;
    colorExtractor(img,dst,lowerb,upperb);
    cv::imshow("dst",dst);


    void minHue_callback(int pos,void*);
    void maxHue_callback(int pos,void*);
    void minSat_callback(int pos,void*);
    void maxSat_callback(int pos,void*);
    void minVal_callback(int pos,void*);
    void maxVal_callback(int pos,void*);

    cv::createTrackbar("minHue","dst",&minHue, 255,minHue_callback);
    cv::createTrackbar("maxHue","dst",&maxHue, 180,maxHue_callback);
    cv::createTrackbar("minSat","dst",&minSat, 255,minSat_callback);
    cv::createTrackbar("maxSat","dst",&maxSat, 255,maxSat_callback);
    cv::createTrackbar("minVal","dst",&minVal, 255,minVal_callback);
    cv::createTrackbar("maxVal","dst",&maxVal, 255,maxVal_callback);

    while (cv::waitKey(0) != 27);
    return 0;
}
void minHue_callback(int pos,void*){
    minHue = pos;
    cv::Scalar lowerb(minHue,minSat,minVal),
               upperb(maxHue,maxSat,maxVal);
    cv::Mat dst;
    colorExtractor(img,dst,lowerb,upperb);
    cv::imshow("dst",dst);
    //sprintf(msg,"minHue = %d",minHue);
    //cv::displayOverlay("dst",msg);
}
void maxHue_callback(int pos,void*){
    maxHue = pos;
    cv::Scalar lowerb(minHue,minSat,minVal),
               upperb(maxHue,maxSat,maxVal);
    cv::Mat dst;
    one.colorExtractor(img,dst,lowerb,upperb);
    cv::imshow("dst",dst);
    //sprintf(msg,"maxHue = %d",maxHue);
    //cv::displayOverlay("dst",msg);
}
void minSat_callback(int pos,void*){
    minSat = pos;
    cv::Scalar lowerb(minHue,minSat,minVal),
               upperb(maxHue,maxSat,maxVal);
    cv::Mat dst;
    colorExtractor(img,dst,lowerb,upperb);
    cv::imshow("dst",dst);
    //sprintf(msg,"minHue = %d",minSat);
    //cv::displayOverlay("dst",msg);
}
void maxSat_callback(int pos,void*){
    maxSat = pos;
    cv::Scalar lowerb(minHue,minSat,minVal),
               upperb(maxHue,maxSat,maxVal);
    cv::Mat dst;
    colorExtractor(img,dst,lowerb,upperb);
    cv::imshow("dst",dst);
    //sprintf(msg,"minHue = %d",maxSat);
    //cv::displayOverlay("dst",msg);
}
void minVal_callback(int pos,void*){
    minVal = pos;
    cv::Scalar lowerb(minHue,minSat,minVal),
               upperb(maxHue,maxSat,maxVal);
    cv::Mat dst;
    colorExtractor(img,dst,lowerb,upperb);
    cv::imshow("dst",dst);
    //sprintf(msg,"minHue = %d",minVal);
    //cv::displayOverlay("dst",msg);
}
void maxVal_callback(int pos,void*){
    maxVal = pos;
    cv::Scalar lowerb(minHue,minSat,minVal),
               upperb(maxHue,maxSat,maxVal);
    cv::Mat dst;
    colorExtractor(img,dst,lowerb,upperb);
    cv::imshow("dst",dst);
    //sprintf(msg,"minHue = %d",maxVal);
    //cv::displayOverlay("dst",msg);
}
