#include "histogram.h"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"


void test1()
{
    std::cout << "test" << std::endl;
}

void histogram(int hbins,std::vector<double> hist)
{
  
    int heigth=0;
    for (int i=0; i<hbins;i++)
      heigth=heigth+hist[i];
  
    
    int scale = 10;
    int heigth_hist=500;
    int length_hist=800;
    cv::Mat histImg = cv::Mat::zeros(heigth_hist, length_hist, CV_8UC3);

    int width_bins=50;
    for( int h = 0; h < hbins; h++ )
        {
            rectangle( histImg, cv::Point(h*width_bins, heigth_hist),
                        cv::Point( (h+1)*width_bins - 1, heigth_hist*(1-hist[h]/heigth)),
                        cv::Scalar(255,0,0) );
        }
        
    cv::imshow( "Histogram", histImg );
    cv::waitKey();   
}