/*
 * This program is for generating images for calibration in Matlab
 * Press any key except ESC to capture current two image in the stereo cam simultaneously
 * Press Esc to quit this program
 *
 */



#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
    cout << "Press any key except ESC to capture " << endl
         << "Press Esc to quit this program"       << endl;
    VideoCapture capture1(0),capture2(1);
    if (!capture1.isOpened()) return -1;
    if (!capture2.isOpened()) return -1;
    Mat img1,img2;
    namedWindow("cam1",1);
    namedWindow("cam2",1);

    vector<int> compression_params;
    compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
    compression_params.push_back(100);

    static int flag = 1;

    for(;;)
       {
           capture1 >> img1;
           capture2 >> img2;
           imshow("cam1",img1);
           imshow("cam2",img2);

           if (waitKey(30) >=0 && waitKey(30) !=27)
           {
               string flag_string;
               stringstream ss;
               if ( flag < 100)
               {
                  ss << flag;
                  ss >> flag_string;
               }
               else
               {
                   cout << "Out of Range, Stop" << endl;
                   break;

               }
               const string str1 =  "left"  + flag_string + ".jpeg";
               const string str2 =  "right" + flag_string + ".jpeg";
               imwrite(  str1 , img1, compression_params );
               imwrite(  str2 , img2, compression_params );
               ++flag;

           }
           if (waitKey(30) == 27) break;
       }


}
