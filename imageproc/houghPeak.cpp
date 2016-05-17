#include <opencv2/opencv.hpp>
#include <vector>
#include <cmath>

struct LinePolar
{
        float rho;
        float angle;
};

void HoughLinesPeak( LinePolar& linepolar,
                     std::vector<cv::Point> linepoint,cv::Size size,
                    float rho, float theta,
                    double min_theta, double max_theta )
{
    float irho = 1 / rho;

    int width = size.width;
    int height = size.height;


    if (max_theta < min_theta ) {
        CV_Error( CV_StsBadArg, "max_theta must be greater than min_theta" );
    }
    int numangle = cvRound((max_theta - min_theta) / theta);
    int numrho = cvRound(((width + height) * 2 + 1) / rho);

    cv::AutoBuffer<int> _accum((numangle+2) * (numrho+2));
    cv::AutoBuffer<float> _tabSin(numangle);
    cv::AutoBuffer<float> _tabCos(numangle);
    int *accum = _accum;
    float *tabSin = _tabSin, *tabCos = _tabCos;


    memset( accum, 0, sizeof(accum[0]) * (numangle+2) * (numrho+2) );


    float ang = static_cast<float>(min_theta);
    for(int n = 0; n < numangle; ang += theta, n++ )
    {
        tabSin[n] = (float)(sin((double)ang) * irho);
        tabCos[n] = (float)(cos((double)ang) * irho);
    }


    // stage 1. fill accumulator
    for(auto i = linepoint.begin(); i !=  linepoint.end(); ++i){
        for(int n = 0; n < numangle; n++ ){
            int r = cvRound( (*i).x * tabCos[n] + (*i).y * tabSin[n] );              //  ρ = x cos θ + y sin θ
            r += (numrho - 1) / 2;
            accum[(n+1) * (numrho+2) + r+1]++;
        }
    }

    // stage 2. finding peak
    int peak = 0 , rpeak = 0, npeak = 0;

    for(int r = 0; r < numrho; r++ )
        for(int n = 0; n < numangle; n++ ){
            int base = (n+1) * (numrho+2) + r+1;

            if( accum[base] > peak ){
                peak = accum[base];
                rpeak = r;
                npeak = n;
            }
        }
    linepolar.rho =   (rpeak - (numrho - 1)*0.5f) * rho;
    linepolar.angle = static_cast<float>(min_theta) + npeak * theta;
}
