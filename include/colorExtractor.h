#include <opencv2/opencv.hpp>
#include <vector>


void colorExtractor(const cv::Mat& image,cv::Mat& dst,cv::InputArray lowerb,cv::InputArray upperb);
enum colors {BLUE=1,YELLOW,WHITE,BLACK};
//fun colorExractor return the mask;
cv::Mat& colorExtractor(const cv::Mat& image,cv::Mat& dst,int color);



void colorExtractor(const cv::Mat& image,cv::Mat& dst,cv::InputArray lowerb,cv::InputArray upperb){
    if(image.channels() == 3){
        cv::Mat img;
        cv::cvtColor(image,img,CV_BGR2HSV);

        cv::Mat mask;
        cv::inRange(img,lowerb,upperb,mask);
        if(debugflag)
            cv::imshow("mask",mask);
        std::vector<cv::Mat> channels(3,cv::Mat());
        std::vector<cv::Mat> dischannels(3,cv::Mat());
        cv::split(image,channels);
        channels[0].copyTo(dischannels[0],mask);
        channels[1].copyTo(dischannels[1],mask);
        channels[2].copyTo(dischannels[2],mask);
        cv::merge(dischannels,dst);
        if(debugflag)
            cv::imshow("extract the color",dst);
    }else std::cout << "Channels error of the input image in colorExtractor" << std::endl;

}
cv::Mat& colorExtractor(const cv::Mat& image,cv::Mat& dst,int color){
    cv::Mat mask;
    if(image.channels() == 3){
        cv::Mat img;
        cv::cvtColor(image,img,CV_BGR2HSV);

        cv::Scalar lowerb,upperb;
        if(color == BLUE){
            lowerb = cv::Scalar(100,25,25);
            upperb = cv::Scalar(130,255,255);
            std::cout << lowerb << std::endl;
        }
        if(color == YELLOW){
            lowerb = cv::Scalar(20,25,25);
            upperb = cv::Scalar(40,255,255);
        }
        if(color == WHITE){
            lowerb = cv::Scalar(0,0,220);
            upperb = cv::Scalar(255,255,255);
        }
        if(color == BLACK){
            lowerb = cv::Scalar(0,0,0);
        }


        cv::inRange(img,lowerb,upperb,mask);
        if(debugflag)
            cv::imshow("mask",mask);
        std::vector<cv::Mat> channels(3,cv::Mat());
        std::vector<cv::Mat> dischannels(3,cv::Mat());
        cv::split(image,channels);
        channels[0].copyTo(dischannels[0],mask);
        channels[1].copyTo(dischannels[1],mask);
        channels[2].copyTo(dischannels[2],mask);
        cv::merge(dischannels,dst);
        if(debugflag)
            cv::imshow("extract the color",dst);
    }else std::cout << "Channels error of the input image in colorExtractor" << std::endl;
    return mask;
}
