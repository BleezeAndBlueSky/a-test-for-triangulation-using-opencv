#include <iostream>
#include <opencv2/opencv.hpp>


int main()
{

    cv::VideoCapture camera1(0);
    cv::VideoCapture camera2(1);

    if(!camera1.isOpened())
    return -1;
    if(!camera2.isOpened())
    return -1;


    cv::Mat img1;
    cv::Mat img2;
    cv::namedWindow("img1",1);
    cv::namedWindow("img2",1);

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
        cv::cvtColor(frame1, img1, CV_BGR2GRAY);
        cv::cvtColor(frame2, img2, CV_BGR2GRAY);
        cv::GaussianBlur(img1, img1, cv::Size(7,7), 1.5, 1.5);//gaussian smoothing
        cv::GaussianBlur(img2, img2, cv::Size(7,7), 1.5, 1.5);


       cv::remap(img1, img1, map11, map12, INTER_LINEAR); //双线性插补
       cv::remap(img2, img2, map21, map22, INTER_LINEAR);


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

           bm->compute(img1, img2, disp);

        cv::Mat image3D;

        cv::reprojectImageTo3D(disp, image3D, Q, false, -1 );



        if(cv::waitKey(30)>=0) return 0;


    

}
