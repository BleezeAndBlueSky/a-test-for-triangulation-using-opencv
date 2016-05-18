
#include <iostream>
#include <opencv2/opencv.hpp>

int main()
{
    cv::Matx21d m1( 1,
                    2);
    cv::Matx22d m2( 1,1,
                    1,1);
    cv::Matx21d m3 = m2* m1;
    m3 (2,1);   // 第二行第一列取值 注:由于过去很久时间,这段代码没有再试验,在其他的程序中 m(i,j),i,j是从0开始的,特此注明
    std::cout << m3 <<std::endl;

}
