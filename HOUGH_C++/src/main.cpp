#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <cmath>
#include "histogram.h"
#include "lines.h"


using namespace cv;
using namespace std;


vector<Vec4i> takeOffLines(  vector<Vec4i> lines,  std::vector<double> orientations)
{
    int i=0;
    std::vector<Vec4i> temp;
    while(i<lines.size())
    {
    if (!((orientations[i]== 0 )|| (abs(orientations[i]-M_PI/2)<= 0.005 ) || (abs(orientations[i]+M_PI/2)<= 0.005 )))
      temp.push_back(lines[i]);
    i++; 
    }
    return temp;
}

cv::Mat HoughLine(cv::Mat src)
{

    cv::Mat src_gray, edges,probabilistic_hough;
    /// Pass the image to gray
   cvtColor( src, src_gray, COLOR_RGB2GRAY );

   GaussianBlur( src_gray, edges, Size( 3, 3 ), 0, 0 );

   /// Apply Canny edge detector
   Canny( edges, edges, 50, 100, 3 );

  vector<Vec4i> p_lines;


    //cvtColor( edges, probabilistic_hough, COLOR_GRAY2BGR );

  /// 2. Use Probabilistic Hough Transform
  HoughLinesP( edges, p_lines, 1, CV_PI/180, 100, 100, 10 );
  /*	p_lines=[x1,y1,x2,y2];
   * 
   * 
   * */
  //  HoughLines( edges, p_lines, 1, CV_PI/180, 50, 50, 10 );

  
  std::vector<double> orientations;
  //std::vector<double> length_lines;
  orientations.resize(p_lines.size());
  //length_lines.resize(p_lines.size());
  //-----------getting orientations of each line -----------
  int n_lines=p_lines.size();
  //std::cout << n_lines << std::endl;
  for (int h=0; h<n_lines;h++)
  {
          Vec4i l=p_lines[h];
          orientations[h]= atan2(l[1]-l[3],l[0]-l[2]);
	  if (orientations[h] > M_PI/2 )
	      orientations[h]=orientations[h] -M_PI;
	  else if (orientations[h] < - M_PI/2 )
	      orientations[h]=orientations[h] +M_PI;
	 
	  //length_lines[h]=sqrt(pow(l[0]+l[2],2)+pow(l[1]+l[3],2));
  }
  
  vector<Vec4i> lines;
  lines=takeOffLines(p_lines,orientations);
  
  /****recalculating the orientations*****/  //TODO instead of recalculating the orientation take off the rientations of the taken off elements
  n_lines=lines.size();
  for (int h=0; h<n_lines;h++)
  {
          Vec4i l=lines[h];
          orientations[h]= atan2(l[1]-l[3],l[0]-l[2]);
	  if (orientations[h] > M_PI/2 )
	      orientations[h]=orientations[h] -M_PI;
	  else if (orientations[h] < - M_PI/2 )
	      orientations[h]=orientations[h] +M_PI;
  }
  /***************************************/
  
  /****************HISTOGRAM***************/
  /*
  int n_bins=18;
  double step_angle= M_PI/n_bins;
  std::vector<double> length_orientations;
  length_orientations.resize(n_bins);
    for (int h=0; h <n_bins;h++)
	length_orientations[h]=0;
  
  int bin=0;
  for (double i=-M_PI/2 ; i<=  M_PI/2-step_angle ; i=i+step_angle)
  {
     for (int h=0; h <lines.size();h++)
     {
	if ((orientations[h]>= i) & (orientations[h]<=(i+step_angle)))
	{
	  length_orientations[bin]=length_orientations[bin]+length_lines[h];	  
	}
     }
     bin++;
  }
  */
  //histogram(n_bins,length_orientations);
  /***************************************/
    
  
  /// Show the result
  for( size_t i = 0; i < lines.size(); i++ )
  {
       Vec4i l = lines[i];
       line( src, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255,0,0), 4, LINE_AA);
  }
     
  src=groupLines( src,lines, orientations, M_PI/20, 1300);


  cv::imshow("src",src);
  cv::waitKey();
     
  return src;

}

int main(int argc, char** argv)
{
  
    std::string filename = "../TLRC_12sec.avi";
    cv::VideoCapture inputVideo(filename);
    cv::Mat frame;

    const String NAME="prova.avi";

    if( !inputVideo.isOpened() )
      throw "Error when reading steam_avi";

    double fps =inputVideo.get(CAP_PROP_FPS );
    std::cout<< "frame rate per second:" << fps << std::endl;
    
    double width=inputVideo.get(CAP_PROP_FRAME_WIDTH);
    std::cout<< "frame width:" << width << std::endl;


    Size S = Size((int) inputVideo.get(CAP_PROP_FRAME_WIDTH),    // Acquire input size
                  (int) inputVideo.get(CAP_PROP_FRAME_HEIGHT));

    cv::VideoWriter outputVideo;                                        // Open the output
    outputVideo.open(NAME, VideoWriter::fourcc('M','J','P','G'), inputVideo.get(CAP_PROP_FPS), S, true);


    if (!outputVideo.isOpened())
    {
        cout  << "Could not open the output video for write: " << endl;
        return -1;
    }


    clock_t begin = clock();
    
//  frame=HoughLine(frame);

    
   for(;;) //Show the image captured in the window and repeat
   {
        inputVideo >> frame;              // read
        if (frame.empty()) break;         // check if at end

        frame=HoughLine(frame);


        outputVideo.write(frame); //save or
        outputVideo << frame;
    }
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Times passed in seconds: " << elapsed_secs << endl;

  return 0;
}




