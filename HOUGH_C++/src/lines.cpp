#include "lines.h"
#include <iostream>
#include <boost/concept_check.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"


cv::Mat groupLines(cv::Mat src,std::vector<cv::Vec4i> lines,  std::vector<double> orientations,double tol_angle,double tol_distance)
{
 
    for( size_t i = 0; i < lines.size(); i++ )
      std::cout << "orientations: " << orientations[i] << "  index: " << i << std::endl;
  
  int n=lines.size();
  std::vector<cv::Point> centers;
  for (int i=0; i <n;i++)
    centers.push_back(centre(cv::Point(lines[i][0],lines[i][1]),cv::Point(lines[i][2],lines[i][3])));
  
  std::vector<std::vector<int> > group_line;
  //group_line.resize(n);
  
  int index_group;
  // here we want to create a group of lines using lines near eachother, but at the end of the process some lines of the group can not be near
  for (int i=0; i <n;i++)
  {
    int index = lineInList(i,group_line);
    //std::cout << " line: " << i << " index group: " << index << std::endl;
    if ( index == NO_GROUP) //creates a new group of lines
    {
      group_line.push_back( std::vector<int>());
      group_line[group_line.size()-1].push_back(i);
      index_group=group_line.size()-1;
    }
    else
    {
      index_group = index; 
    }
    for (int h=0; h<n ; h++)
    {
      if ((absDiff(orientations[h] , orientations[i])<=tol_angle) && (eucDist(centers[h],centers[i])<=tol_distance))
      {
	    group_line[index_group].push_back(h);
	     
      }
    }
  //now each line has been linked to the nearest line that has its same orientation
	    // PROBLEM: a long line segment and a short line segment lying in the same line have a big eucDist

  }
  //std::cout << " number of groups: " << group_line.size() << std::endl;
  
  group_line=refinementGroup(group_line);

  //debugiing purpose
  //  for (int i=0; i <group_line.size();i++)
  //    for (int h=0; h<group_line[i].size() ; h++)
	//std::cout << " Group : " << i << " Element: " << group_line[i][h] << " orientation: " << orientations[group_line[i][h]]  << "center: " << centers[i] << std::endl;

  
      
      
   //drawing the center that approximates the group of the lines
  /*******************/
   std::vector<cv::Point> center_group;
   center_group.resize(group_line.size());
   for (int i=0; i <group_line.size();i++)//group
   {
     double tempx = 0 ;
     double tempy = 0 ;
     for (int h=0; h<group_line[i].size() ; h++) //line
     {
	tempx=tempx+centers[group_line[i][h]].x;
	tempy=tempy+centers[group_line[i][h]].y;
     }
      center_group[i]=cv::Point(tempx/group_line[i].size(),tempy/group_line[i].size());
      cv::circle(src,center_group[i],5,cv::Scalar(0,255,0),5,8,0);
   }
   /*******************************************/
      
      return src;
}

int eucDist(cv::Point x1, cv::Point x2)
{
  return sqrt(pow(x1.x+x2.x,2)+pow(x1.y +x2.y,2));
  
}
cv::Point centre(cv::Point x1, cv::Point x2)
{
      return cv::Point((x1.x+x2.x)/2,(x1.y+x2.y)/2);
}
int lineInList(int i,   std::vector<std::vector<int> > group_line)
{
  int n_groups=group_line.size();
  for(int h=0;h<n_groups;h++)	// Looks in the all gropu of lines if there is a group with the searched line (index=i)
      for(int k=0;k<group_line[h].size();k++)
	if(group_line[h][k]==i)
	  return h;
  // if it found anything returns -1
  return NO_GROUP; 
}
double absDiff(double a,double b)
{
  if (a >= b) 
    return (a-b);
  
  return (b-a);
  
}
std::vector<std::vector<int> > refinementGroup(  std::vector<std::vector<int> > group_line)
{
    bool find;
    std::vector<std::vector<int> > gout;
    for(int i=0; i<group_line.size();i++)
    {
      int h=0;
      std::vector<int> temp;
      while(h<group_line[i].size())
      {
	find=false;
	for(int k=0;k<temp.size();k++)
	  if(temp.size() > 0)
	    if( temp[k] == group_line[i][h])
	    {  find= true; break;
	    }
	if(!find)
	  temp.push_back(group_line[i][h]);
	    
	h++;
      }
      gout.push_back(temp);
    }
    return gout;
}

