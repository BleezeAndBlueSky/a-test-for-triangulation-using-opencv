/* 
 * opencv computer vision application programming cookbook 2nd edition
 * example class file
 */

#ifndef HARRISDETECTOR_H
#define HARRISDETECTOR_H

#include "harrisdetector.h"
#include <opencv2/opencv.hpp>
class HarrisDetector
{
private:
    // 32-bit float image of corner strength
    cv::Mat cornerStrength;
    // 32-bit float image of thresholded corners
    cv::Mat cornerTh;
    // image of local maxima (internal)
    cv::Mat localMax;
    // size of neighborhood for derivatives smoothing
    int neighbourhood;
    // aperture for gradient computation
    int aperture;
    // Harris parameter
    double k;
    // maximum strength for threshold computation
    double maxStrength;
    // calculated threshold (internal)
    double threshold;
    // size of neighborhood for non-max suppression
    int nonMaxSize;
    // kernel for non-max suppression
    cv::Mat kernel;
public:
    HarrisDetector() : neighbourhood(3), aperture(3), k(0.01), maxStrength(0.0),
                       threshold(0.01),nonMaxSize(3)
                       {
                                                    // create kernel used in non-maxima suppression
                        setLocalMaxWindowSize(nonMaxSize);
                       }
    void setLocalMaxWindowSize(int size)
    {
        nonMaxSize = size;
        kernel.create(nonMaxSize, nonMaxSize, CV_8U);
    }
    // Compute Harris corners
    void detect(const cv::Mat& image)
    {
        // Harris computation
        cv::cornerHarris(image,cornerStrength,neighbourhood,aperture, k);
                                           // neighborhood size
                                                    // aperture size
                                                            // Harris parameter
        // internal threshold computation
        cv::minMaxLoc(cornerStrength,0,&maxStrength);//Finds the global minimum and maximum in an array.
        // local maxima detection

        cv::Mat dilated; // temporary image
        cv::dilate(cornerStrength,dilated,cv::Mat()); // 膨胀If element=Mat(), a 3times 3 rectangular structuring element is used
        cv::compare(cornerStrength,dilated,localMax,cv::CMP_EQ);
    }

    // Get the corner map from the computed Harris values
    cv::Mat getCornerMap(double qualityLevel)
    {
        cv::Mat cornerMap;
        // thresholding the corner strength
        threshold= qualityLevel*maxStrength;
        cv::threshold(cornerStrength,cornerTh,threshold,255,cv::THRESH_BINARY);// convert to 8-bit image
        cornerTh.convertTo(cornerMap,CV_8U);
        // non-maxima suppression
        cv::bitwise_and(cornerMap,localMax,cornerMap);//Performs a per-element bitwise conjunction of
                                                      //two matrices or of matrix and scalar.
        return cornerMap;
    }

    // Get the feature points from the computed Harris values
    void getCorners(std::vector<cv::Point> &points,double qualityLevel)
    {
        // Get the corner map
        cv::Mat cornerMap= getCornerMap(qualityLevel);
        // Get the corners
        getCorners(points, cornerMap);//这里调用了下面的函数
    }
    // Get the feature points from the computed corner map
    void getCorners(std::vector<cv::Point> &points,const cv::Mat& cornerMap)
    {
        // Iterate over the pixels to obtain all features
        for( int y = 0; y < cornerMap.rows; y++ )
        {
            const uchar* rowPtr = cornerMap.ptr<uchar>(y);
            for( int x = 0; x < cornerMap.cols; x++ )
            {
             // if it is a feature point
                if (rowPtr[x])
                {
                    points.push_back(cv::Point(x,y));
                }
            }
        }
    }

    // Draw circles at feature point locations on an image
    void drawOnImage(cv::Mat &image,
    const std::vector<cv::Point> &points,
    cv::Scalar color= cv::Scalar(255,255,255),
    int radius=3, int thickness=1)
    {
        std::vector<cv::Point>::const_iterator it = points.begin();
                      // for all corners
        while (it!=points.end())
        {
            // draw a circle at each corner location
            cv::circle(image,*it,radius,color,thickness);
            ++it;
        }
    }



};






#endif // HARRISDETECTOR_H
