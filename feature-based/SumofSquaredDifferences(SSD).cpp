/*
 * opencv computer vision programming cook book 2nd edition
 * chapter 9 example code
 * bug fixed by TauBai
 * tested on ubuntu x64,  opencv 3.1.0
 */

#include <iostream>
#include <opencv2/opencv.hpp>
int main(int argc, char ** argv)
{
    if(argc < 3)
        return -1;
    cv::Mat image1 = cv::imread(argv[1],0);
    cv::Mat image2 = cv::imread(argv[2],0);
    if(image1.empty())
        return -1;
    if(image2.empty())
        return -1;
    std::vector<cv::KeyPoint> keypoints1;
    std::vector<cv::KeyPoint> keypoints2;
    cv::FAST(image1,keypoints1,80);
    cv::FAST(image2,keypoints2,80);
    const int nsize(12);
    std::vector<cv::DMatch> matches;
    for (int i=0; i < keypoints1.size(); i++)
    {
        cv::Rect neighborhood(0, 0, nsize, nsize);
        cv::Mat patch1;
        neighborhood.x = keypoints1[i].pt.x-nsize/2;
        neighborhood.y = keypoints1[i].pt.y-nsize/2;

        if (neighborhood.x<0 ||
            neighborhood.y<0 ||
            neighborhood.x+nsize >= image1.cols  ||
            neighborhood.y+nsize >= image1.rows)
                continue;
        patch1 = image1(neighborhood);
        cv::DMatch bestMatch;
        for (int j=0; j < keypoints2.size(); j++)
        {
            cv::Rect neighborhood(0, 0, nsize, nsize);
            cv::Mat patch2;
            cv::Mat result;

            neighborhood.x = keypoints2[j].pt.x-nsize/2;
            neighborhood.y = keypoints2[j].pt.y-nsize/2;

            if (neighborhood.x<0 || neighborhood.y<0 ||
                neighborhood.x + nsize >= image2.cols ||
                neighborhood.y + nsize >= image2.rows)
                    continue;
            patch2 = image2(neighborhood);
            cv::matchTemplate(patch1,patch2,result,CV_TM_SQDIFF_NORMED);
            if (result.at<float>(0,0) < bestMatch.distance)
                {
                    bestMatch.distance = result.at<float>(0,0);
                    bestMatch.queryIdx = i;
                    bestMatch.trainIdx = j;
                }
            }
        matches.push_back(bestMatch);
    }
    std::nth_element(matches.begin(),matches.begin()+25,matches.end());
    cv::Mat matchImage;
    cv::drawMatches(image1,keypoints1, image2,keypoints2, matches,matchImage,
                    cv::Scalar(255),cv::Scalar::all(-1),cv::Mat(),0);
    cv::namedWindow("matchresult",cv::WINDOW_NORMAL);
    cv::imshow("matchresult",matchImage);

    cv::waitKey(0);
}
