#include <iostream>
#include <opencv2/opencv.hpp>


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
                       CALIB_ZERO_DISPARITY, -1, newimg_size, &roi1, &roi2 );


    cv::Mat map11, map12, map21, map22;
    cv::initUndistortRectifyMap(M1, D1, R1, P1, newimg_size, CV_16SC2, map11, map12);  //Computes the undistortion
                                                                    //and rectification transformation map.
    cv::initUndistortRectifyMap(M2, D2, R2, P2, newimg_size, CV_16SC2, map21, map22);



    
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



       cv::remap(final1, final1, map11, map12, INTER_LINEAR); //双线性插补
       cv::remap(final2, final2, map21, map22, INTER_LINEAR);


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

           cv::Mat disp;

           bm->compute(final1, final2, disp);

        cv::Mat image3D;

        cv::reprojectImageTo3D(disp, image3D, Q, false, -1 );



        if(cv::waitKey(30)>=0) return 0;


    

}
