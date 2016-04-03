#include <opencv2/opencv.hpp>
#include "ColorDetector.h"

cv::Mat ColorDetector::process(const cv::Mat &image) {
    // re-allocate binary map if necessary
    // same size as input image, but 1-channel
    result.create(image.size(),CV_8U);
    // processing loop above goes here
    cv::Mat_<cv::Vec3b>::const_iterator it    = image.begin<cv::Vec3b>();
    cv::Mat_<cv::Vec3b>::const_iterator itend = image.end<cv::Vec3b>();
    cv::Mat_<cv::Vec3b>::const_iterator itout = result.begin<cv::Vec3b>();
    for( ;it!=itend; ++it,++itout)
    {
        if(getDistanceToTargetColor(*it) <= maxDist)
            *itout = 255;
        else
            *itout = 0;

    }

return result;
}


// Sets the color distance threshold.
// Threshold must be positive,
// otherwise distance threshold is set to 0.
void ColorDetector::setColorDistanceThreshold(int distance) {

    if (distance<0)
        distance=0;
    maxDist= distance;
}






