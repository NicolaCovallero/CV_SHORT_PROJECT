#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"

#define NO_GROUP -1 


//divide a vector of lines in groups of lines according to their orientations and how they far are from eachother 
cv::Mat groupLines(cv::Mat src,std::vector<cv::Vec4i> lines,  std::vector<double> orientations,double tol_angle,double tol_distance);

//compute the euclidian distance between two points
int eucDist(cv::Point x1, cv::Point x2);


//compute the centre between two points ( the center is the middle point)
cv::Point centre(cv::Point x1, cv::Point x2);

/*
  It returns the index of the group where is present the searched line represented by the index i
*/
int lineInList(int i,   std::vector<std::vector<int> > group_line);

// absolute difference
double absDiff(double a,double b);


//take off elements that appear more than once, in order to leave only one element for each type of element presented in each group
std::vector<std::vector<int> > refinementGroup(  std::vector<std::vector<int> > group_line);


