/*
 * 试了好多次,itmax 要达到 1000000 次以上才有比较好的结果..  还以为程序出了毛病debug了一晚上..
 *          这几天试着看能不能优化一下          
 *                                ------------------2016. 5.17  23:55
 *  按照http://blog.csdn.net/traumland/article/details/51284129  提供的计算迭代次数k的方法
 *  需要大概 143数量集的 迭代次数
 *  1百万次都算少的了
 *  但是按照这个说法,  ransac就不能用了?  他们是如何优化的? 
 *                                 -----------------2016. 5.18   00:40
 *  搞错了 ,  应该是40次左右就能达到99%,  还是程序本身的问题,  难道是rand()的伪随机?
 *                                  ----------------2016. 5.19   16:00
 *使用了c++11 中的随机函数, 对于非指定边数的不规则形状(内凹, 很多杂乱的边缘)的点效果较差, 因为这个函数本身就只是用来识别直线特征的
 *   40次可以达到效果, 1000次基本符合我的预期
 *                                  ----------------2016. 5.20    12.33
 *--------------------------------------------------------------------------------------
 * 注意:
 *最后一步没有用确定出inlier的点进行重新拟合,有的算法书会用到这一点. 如果需要,加个fitline函数就行了,或者自己去写,也很简单
 */

#ifndef RANSACLINES_H
#define RANSACLINES_H

#include <opencv2/opencv.hpp>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <random>


//distance -- max distance to the random line for voting
//ngon     -- n-gon to be detected
//itmax    -- max iteration times
void ransacLines(std::vector<cv::Point>& input,std::vector<cv::Vec4d>& lines,
                    double distance ,  unsigned int ngon,unsigned int itmax ){

    if(!input.empty())
    for(int i = 0; i < ngon; ++i){
        unsigned int Mmax = 0;
        cv::Point imax;
        cv::Point jmax;
        cv::Vec4d line;
        size_t t1 , t2;
        
        std::random_device rd;     // only used once to initialise (seed) engine
        std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
        std::uniform_int_distribution<int> uni(0,input.size()-1); // guaranteed unbiased // 概率相同

        unsigned int it = itmax;
        while(--it){
            t1 = uni(rng);
            t2 = uni(rng);
            t2 = (t1 == t2 ? uni(rng): t2);
            unsigned int M = 0;
            cv::Point i = input[t1];
            cv::Point j = input[t2];
            for(auto a : input){
                double dis = fabs((j.x - i.x)*(a.y - i.y) - (j.y - i.y)*(a.x - i.x)) /
                        sqrt((j.x - i.x)*(j.x - i.x) + (j.y - i.y)*(j.y - i.y));

                if( dis < distance)
                    ++M;
            }
            if(M > Mmax ){
                Mmax = M;
                imax = i;
                jmax = j;
            }
        }
        line[0] = imax.x;
        line[1] = imax.y;
        line[2] = jmax.x;
        line[3] = jmax.y;
        lines.push_back(line);
        auto iter = input.begin();
        while(iter != input.end()){
            double dis = fabs((jmax.x - imax.x)*((*iter).y - imax.y) -
                                    (jmax.y - imax.y)*((*iter).x - imax.x))
                         / sqrt((jmax.x - imax.x)*(jmax.x - imax.x)
                                 + (jmax.y - imax.y)*(jmax.y - imax.y));
            if(dis < distance)
                iter = input.erase(iter);  //erase the dis within , then point to
                                           //   the next element
            else ++iter;
        }
    }
    else std::cout << "no input to ransacLines" << std::endl;
}

#endif
