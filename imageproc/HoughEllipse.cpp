/* 
 * 程序没有完成,  只是用霍夫变换刚刚求出了椭圆中心, 
 * 也就是http://blog.csdn.net/traumland/article/details/51089786 提到的简化方法
 * 至于后面的三个参数简化到两个参数,  我还没想好 B, C 的取值范围, 应该是浮点数, 还涉及到参数空间中每个格子代表多少的问题
 * 过程和这里面的求中心类似
 *                                          ---------------2016.4.11     20:00
 * 会接着更新(to be continued..   _(:з」 ∠)_  )
 */
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

//#define minwidth 30
cv::Size2f a;
const decltype(a.width) minwidth = 30;  //if you dont know the type of width
#define minheight  30
#define maxwidth   100
#define maxheight  100


unsigned int iteration_times = 20;  // Max times for loops.
std::vector<size_t> trashnum_box;                  //储存随机生成的数,  避免后面重复



double threshold1 = 50;
double threshold2 = 150;
int apertureSize = 3;//aperture size for the Sobel() operator.
int point_num_min = 100; //least point in a contour


cv::Mat dx, dy;

int main(int argc, char** argv)
{
    if(argc < 2)
        return -1;
    cv::Mat image1 = cv::imread(argv[1]);

    cv::namedWindow("canny_edge1",1);
    cv::cvtColor(image1, image1, CV_BGR2GRAY);
    cv::GaussianBlur(image1, image1, cv::Size(7,7), 1.5, 1.5);


    cv::Sobel(image1, dx, CV_16S, 1, 0, apertureSize, 1, 0, cv::BORDER_REPLICATE);  // compute dx, dy
    cv::Sobel(image1, dy, CV_16S, 0, 1, apertureSize, 1, 0, cv::BORDER_REPLICATE);
    cv::Canny(image1,image1,threshold1,threshold2,apertureSize, false);
    cv::imshow("canny_edge1",image1);
    std::vector<std::vector<cv::Point> > contours1;
    std::vector<cv::RotatedRect> contours01;

    cv::findContours( image1, contours1 ,CV_RETR_LIST,CV_CHAIN_APPROX_NONE,cvPoint(0,0));

    cv::Mat ellipse_contour ;

    cv::Mat allcontours(image1.size(),CV_8U,cv::Scalar(255));
    ellipse_contour.create(image1.size(),image1.type());          //two types of initiation

    contours01.reserve(contours1.size());


    void houghellipse( std::vector<cv::Point> contour,cv::Mat image);

    for( std::size_t k = 0; k < contours1.size(); k++ )
    {

        int count = contours1[k].size(); // This is point's number in the contour
        if( count > point_num_min )   //  the least points to form a contour
            houghellipse(contours1[k],image1);


    }


    cv::drawContours(allcontours, contours1,-1, CV_RGB(0,0,0), 1, cv::LINE_8,cv::noArray(),contours1.size(),cvPoint(0,0));


    cv::Size2f min;
    cv::Size2f max;
    min.width = minwidth;
    min.height = minheight;
    max.width  = maxwidth ;
    max.height = maxheight;

    for( auto a : contours01)
    {
        auto ellipse_size = a.size;
        if(
                ellipse_size.width < max.width && ellipse_size.height < max.height
          &&    ellipse_size.width > min.width && ellipse_size.height > min.height
                )
        {
            cv::ellipse(ellipse_contour,a,CV_RGB(255,255,255));
            std::cout << "size = "  << a.size   << " , "
                      << "center =" << a.center << std::endl;
        }

    }
    cv::namedWindow("drawcontour",1);
    cv::namedWindow("ellipsecontour",1);
    cv::imshow("drawcontour",allcontours);
    cv::imshow("ellipsecontour",ellipse_contour);
    cv::waitKey(0);
    return 0;
}

void houghellipse(std::vector<cv::Point> contour, cv::Mat image)
{
    cv::Mat accumulator(image.size(),CV_8UC1,cv::Scalar(0));
    cv::Point ellipsecenter;

    size_t k = contour.size();
    if (iteration_times > contour.size())
        iteration_times = contour.size();
    bool compare_trashnum(size_t t);
    std::vector<size_t>().swap(trashnum_box);   // 删除vector内的所有元素,  不删除后面越界会陷入循环
    for (unsigned int i = 0; i< iteration_times ; ++i)    //随机抽iteration_times个点
    {


        size_t t1 , t2 , t3;                  //随机生成三个点
        srand((unsigned) time(NULL));
        do {
            t1 = rand() % k;
        }
        while(compare_trashnum(t1));
        trashnum_box.push_back(t1);           //扔掉
        srand((unsigned) time(NULL));
        do {
            t2 = rand() % k;
        }
        while(compare_trashnum(t2));
        trashnum_box.push_back(t2);
        srand((unsigned) time(NULL));
        do {
            t3 = rand() % k;
        }
        while(compare_trashnum(t3));
        trashnum_box.push_back(t3);

        double k1,k2,k3;

        cv::Point2d p1,p2;
        cv::Point2d pp1 = (contour[t1]+contour[t2])/2,
                    pp2 = (contour[t1]+contour[t3])/2;


//        if (!dx.at<uchar>(contour[t1]))           // ignore the assumption that dx equals to zero
            k1 = (double)dy.at<uchar>(contour[t1]) / (double)dx.at<uchar>(contour[t1]);
//        if (!dx.at<uchar>(contour[t2]))
            k2 = (double)dy.at<uchar>(contour[t2]) / (double)dx.at<uchar>(contour[t2]);
//        if (!dx.at<uchar>(contour[t3]))
            k3 = (double)dy.at<uchar>(contour[t3]) / (double)dx.at<uchar>(contour[t3]);
        cv::Matx21d matp1, matp2,
                    matcp1(contour[t1].y - k1*contour[t1].x,
                           contour[t2].y - k2*contour[t2].x),
                    matcp2(contour[t1].y - k1*contour[t1].x,
                           contour[t3].y - k2*contour[t3].x);
        cv::Matx22d matkp1(-k1, 1,
                           -k2, 1 ),
                    matkp2(-k1, 1
                           -k3, 1);
        matp1 = matkp1.inv() * matcp1;
        matp2 = matkp2.inv() * matcp2;
        p1.x =matp1(1,1);
        p1.y =matp2(2,1);
        p2.x =matp1(1,1);
        p2.y =matp2(2,1);

        double kp1,kp2;
        kp1 = (double)(p1.y-pp1.y)/(p1.x-pp1.x);
        kp2 = (double)(p2.y-pp2.y)/(p2.x-pp2.x);

        cv::Matx21d mcenter;
        cv::Matx22d kpp(-kp1,1,
                        -kp2,1);
        cv::Matx21d kpc(p1.y-kp1*p1.x,
                        p2.y-kp2*p2.x);

        mcenter = kpp.inv() * kpc;
        cv::Point center;
        center.x = cvRound(mcenter(1,1));
        center.y = cvRound(mcenter(2,1));
        if(center.x < image.cols &&
                center.x >0      &&
                center.y < image.rows &&
                center.y >0)                     //防止中心坐标出界
            accumulator.at<uchar>(center) += 1;   

    }
    cv::MatIterator_<uchar> it = accumulator.begin<uchar>();
    cv::MatIterator_<uchar> itend = accumulator.end<uchar>();
    uchar peak = 0;
    for(;it != itend; ++it)
    {
        if( *it > peak)
            peak = *it;
    }
    it = accumulator.begin<uchar>();             //reset iterator it
//    int count = 0;          //count how many pixels reach the peak. but there is no need since the vector has it's size
    std::vector<cv::Point> Points;
    for(int i = 0;it != itend; ++it, ++i)   // 这里能不能简化?避免 使用这样的循环?
    {
        cv::Point pt;
        if( *it == peak)
        {
            pt.x = i % accumulator.cols;
            pt.y = i / accumulator.cols;
            Points.push_back(pt);
        }
    }
    cv::Point pts(0,0);
    for(auto a : Points)
        pts += a;
    ellipsecenter.x = pts.x/Points.size();    //get the center;
    ellipsecenter.y = pts.y/Points.size();
    //下一步是求剩下的3个参数
    std::cout << ellipsecenter << std::endl; //先测试一下
    

}


bool compare_trashnum(size_t t)
{
    for (size_t i = 0 ; i < trashnum_box.size(); ++i)
    {
        if ( t == trashnum_box[i])
            return true;
    }
    return false;
}
