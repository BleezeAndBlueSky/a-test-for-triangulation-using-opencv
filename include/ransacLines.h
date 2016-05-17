/*
 * 试了好多次,itmax 要达到 1000000 次以上才有比较好的结果..  还以为程序出了毛病debug了一晚上..
 *          这几天试着看能不能优化一下          
 *                                ------------------2016. 5.17  23:55
 */

#ifndef RANSACLINES_H
#define RANSACLINES_H

#include <opencv2/opencv.hpp>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>


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
        unsigned int it = itmax;
        while(--it){
            srand((unsigned) time(NULL));
            t1 = rand() % input.size();
            srand((unsigned) time(NULL));
            t2 = rand() % input.size();
            t2 = (t1 == t2 ? rand() % input.size() : t2 );
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
    else std::cout << "no input to ransac" << std::endl;
}

#endif
