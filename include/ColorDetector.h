/*
 * opencv computer vision programming cook book 2nd edition
 * example code
 *  ColorDetector.cpp
 */
 
#ifndef COLORDETECTOR_H
#define COLORDETECTOR_H
#include <opencv2/opencv.hpp>
#include "ColorDetector.h"
class ColorDetector
{
    public:

        ColorDetector() = default;       //default constructor
        ColorDetector(int maxDist, cv::Vec3b target) : maxDist(100), target(0,0,0) {}

        int maxDist;    // minimum acceptable distance

        cv::Vec3b target;  // target color
        cv::Mat result;         // image containing resulting binary map


        int getDistanceToTargetColor(const cv::Vec3b& color) const {
            return getColorDistance(color, target);
        }
        int getColorDistance(const cv::Vec3b& color1,const cv::Vec3b& color2) const  {
            return abs(color1[0]-color2[0])+abs(color1[1]-color2[1])+abs(color1[2]-color2[2]);
        }
        // Gets the color distance threshold
        int getColorDistanceThreshold() const {

            return maxDist;
        }

        void setTargetColor(uchar blue,uchar green,uchar red) {

            target = cv::Vec3b(blue, green, red);
        }

        // Sets the color to be detected
        void setTargetColor(cv::Vec3b color) {
            target=color;
        }

        // Gets the color to be detected
        cv::Vec3b getTargetColor() const {

            return target;
        }


        cv::Mat process(const cv::Mat &image);
        void setColorDistanceThreshold(int distance);
};




#endif // COLORDETECTOR_H
