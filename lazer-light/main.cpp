#include <iostream>
#include <opencv2/opencv.hpp>
#include "stereo_linelaser.h"

double canny_threshold1 = 50;
double canny_threshold2 = 150;
double threshold_value = 200, threshold_maxval = 255, threshold_type = cv::THRESH_BINARY;
int laser_strip_width_max = 20;

int main()
{
    std::cout << "canny_threshold1=50 \n"
                 "canny_threshold2=150 \n"
                 "threshold_value =200,threshold_maxval=255,threshold_type=THRESH_BINARY \n"
              << std::endl;
    cv::VideoCapture camera1(0);
    cv::VideoCapture camera2(1);

    if(!camera1.isOpened())
    return -1;
    else if(!camera2.isOpened())
    return -1;


    cv::Mat edge1;
    cv::Mat edge2;
    cv::namedWindow("edge1",1);
    cv::namedWindow("edge2",2);
    
    cv::Mat map11, map12, map21, map22;
    cv::initUndistortRectifyMap(M1, D1, R1, P1, img_size, CV_16SC2, map11, map12);  //Computes the undistortion
                                                                    //and rectification transformation map.
    cv::initUndistortRectifyMap(M2, D2, R2, P2, img_size, CV_16SC2, map21, map22);


    for(;;)        //Whether to use while or for is largely a matter of personal preference.
    {
        cv::Mat frame1, frame2;
        camera1 >> frame1;
        camera2 >> frame2;
        cv::cvtColor(frame1, edge1, CV_BGR2GRAY);
        cv::cvtColor(frame2, edge2, CV_BGR2GRAY);
        cv::GaussianBlur(edge1, edge1, cv::Size(7,7), 1.5, 1.5);//gaussian smoothing
        cv::GaussianBlur(edge2, edge2, cv::Size(7,7), 1.5, 1.5);
        cv::threshold(edge1, edge1, threshold_value,threshold_maxval,threshold_type);
        cv::threshold(edge2, edge2, threshold_value,threshold_maxval,threshold_type);
        cv::Mat final1(edge1.rows, edge1.cols, edge1.type() , 0);
        cv::Mat final2(edge2.rows, edge2.cols, edge2.type() , 0);
        mean(edge1 , final1);
        mean(edge2 , final2);
        //M1 第一个相机矩阵
        //D1 第二个相机矩阵
                //M2 第一个畸变参数
                //D2
                //img_size  用于校正的图像大小.
        //R  第一和第二相机坐标系之间的旋转矩阵
        //T  第一和第二相机坐标系之间的平移矩阵
        //R1 输出第一个相机的3x3矫正变幻 (旋转矩阵) .
        //R2 输出第二个相机的3x3矫正变幻 (旋转矩阵) .
        //P1 在第一台相机的新的坐标系统(矫正过的)输出 3x4 的投影矩阵
        //P2 在第二台相机的新的坐标系统(矫正过的)输出 3x4 的投影矩阵
        // Q 输出深度视差映射矩阵，如下：矩阵Q是一个任意提供的矩阵(比如, stereoRectify()所能得出的矩阵).
        //CV_CALIB_ZERO_DISPARITY,函数的作用是使每个相机的主点在校正后的图像上有相同的像素坐标
        //-1        执行默认缩放
        //img_size  校正后新的图像分辨率
        //&roi1     校正后的图像可选的输出矩形，里面所有像素都是有效的。如果alpha= 0，ROIs覆盖整个图像。否则，他们可能会比较小。
        //&roi2     校正后的图像可选的输出矩形，里面所有像素都是有效的。如果alpha= 0，ROIs覆盖整个图像。否则，他们可能会比较小。



       cv::Mat img1r, img2r;
       cv::remap(img1, img1r, map11, map12, INTER_LINEAR);
       cv::remap(img2, img2r, map21, map22, INTER_LINEAR);

       roi由下面这个函数获得
           stereoRectify( M1, D1, M2, D2, img_size, R, T, R1, R2, P1, P2, Q,
                          CALIB_ZERO_DISPARITY, -1, img_size, &roi1, &roi2 );
       
       
           bm->setROI1(roi1);
           bm->setROI2(roi2);
           bm->setPreFilterCap(31);
           bm->setBlockSize(SADWindowSize > 0 ? SADWindowSize : 9);
           bm->setMinDisparity(0);
           bm->setNumDisparities(numberOfDisparities);
           bm->setTextureThreshold(10);
           bm->setUniquenessRatio(15);
           bm->setSpeckleWindowSize(100);
           bm->setSpeckleRange(32);
           bm->setDisp12MaxDiff(1);
           
           Mat disp;
    
            bm->compute(img1, img2, disp);
       cv::reprojectImageTo3D(InputArray disparity, OutputArray _3dImage, InputArray Q, bool handle
                                               MissingValues=false, int ddepth=-1 );



        if(cv::waitKey(30)>=0) break;


    }

}


void mean(cv::Mat src,cv::Mat dst)     //Find laserstripe's center
{

    for(int i=0;i<=src.rows;i++)    //遍历灰度图像
    {
        int min=0,max=src.cols ,mid=0;
        for(int j=0;j<=src.cols;j++)
        {
            if (src.at<uchar>(i,j) > threshold_value )
            {
                if (j > min)
                   {
                        max = j;
                   }
                if (j < max)
                   {
                        min = j;
                   }
             }


        }

        if(  (max-min) > laser_strip_width_max )
            mid = (int) ((min+max)/2);

        dst.at<uchar>(i,mid) = 255;              //set the midpoint to 255;
    }

}


void result(cv::Mat src1 , cv::Mat src2, cv::Mat dst, const char* filename)
{
    /*
     *
     *
     * 这里计算深度




                        */

//注意这么写会存在数据覆盖问题的

    FILE* fp = fopen(filename, "wt");
    fprintf(fp, "%02d/n", dst.rows);
    fprintf(fp, "%02d/n", dst.cols);
    for(int y = 0; y < dst.rows; y++)
    {
        for(int x = 0; x < dst.cols; x++)
        {
            short disp = dst.at<short>(y, x); // 这里视差矩阵是CV_16S 格式的，故用 short 类型读取
            fprintf(fp, "%d/n", disp); // 若视差矩阵是 CV_32F 格式，则用 float 类型读取
        }
    }
    fclose(fp);
}
