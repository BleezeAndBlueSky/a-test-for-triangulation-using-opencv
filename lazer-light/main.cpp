#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>


double canny_threshold1 = 50;
double canny_threshold2 = 150;
double threshold_value = 200, threshold_maxval = 255, threshold_type = cv::THRESH_BINARY;
int laser_strip_width_max = 20;
int laser_strip_width_min = 3;


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
    if(!camera2.isOpened())
    return -1;


    cv::Mat edge1;
    cv::Mat edge2;
    cv::namedWindow("edge1",1);
    cv::namedWindow("edge2",1);

    cv::Mat M1,M2,D1,D2,R,T;// 由标定参数获得,需要赋值
    cv::Size img_size,newimg_size;        //Size of the image used for stereo calibration.需要赋值
                                         //New image resolution after rectification.

    cv::Rect roi1,roi2;       //校正后输出矩形
    cv::Mat R1,R2,P1,P2,Q;    //输出的旋转、投影、视差映射矩阵
    cv::stereoRectify( M1, D1, M2, D2, img_size, R, T, R1, R2, P1, P2, Q,
                       cv::CALIB_ZERO_DISPARITY, -1, newimg_size, &roi1, &roi2 );


    cv::Mat map11, map12, map21, map22;
    cv::initUndistortRectifyMap(M1, D1, R1, P1, newimg_size, CV_16SC2, map11, map12);  //Computes the undistortion
                                                                    //and rectification transformation map.
    cv::initUndistortRectifyMap(M2, D2, R2, P2, newimg_size, CV_16SC2, map21, map22);



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
        cv::imshow("edge1",edge1);
        cv::imshow("edge2",edge2);
        
        cv::remap(edge1, edge1, map11, map12, cv::INTER_LINEAR); //双线性插补
        cv::remap(edge2, edge2, map21, map22, cv::INTER_LINEAR);
        std::vector<cv::Point2f> left;
        std::vector<cv::Point2f> right;

        cv::Mat result(4,left.size(),CV_32FC1);
        cv::Mat result3d;
        mean(edge1 , left);
        mean(edge2 , right);
        cv::triangulatePoints(P1,P2,left,right,result);
        cv::convertPointsFromHomogeneous(cv::Mat(result.t()).reshape(4, 1),result3d);//transform the 4xN array to Nx4
                                                                                     //then convert it to Nx3
        save_result(result3d, "Point_Cloud.txt");

        if(cv::waitKey(30)>=0) break;


    }

}


void mean(cv::Mat src,std::vector<Point2f>& dst)     //Find laserstripe's center and convert it to array
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

        if(  (max-min) < laser_strip_width_max && (max-min)> laser_strip_width_min)
        {
            mid = (float) ((min+max)/2);
            dst.push_back(cv::Point2f(mid,(float)i));

        }
    }

}


void save_result(cv::Mat result, const char* filename)
{

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
