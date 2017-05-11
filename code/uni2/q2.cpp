#include <iostream>
#include <opencv2/opencv.hpp>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <numeric>
#include <ctime>
#include <cstdlib>

using namespace std;
using namespace cv;

#define RAIO_SLIDER_MAX   20
#define TOP_SLIDER_MAX    200

int top    = 10;
int raio   = 20;
int step   = 1;
int jitter = 30;

Mat image, border;
int width, height;

void on_trackbar(int, void*)
{
  Mat         points;
  vector<int> yrange;
  vector<int> xrange;
  int         x, y;
  Vec3b       pix;

  xrange.resize(height/step);
  yrange.resize(width/step);
  
  iota(xrange.begin(), xrange.end(), 0); 
  iota(yrange.begin(), yrange.end(), 0);
 
  for(uint i=0; i<xrange.size(); i++) xrange[i] = xrange[i]*step+step/2;
  for(uint i=0; i<yrange.size(); i++) yrange[i] = yrange[i]*step+step/2;

  points = Mat(height, width, CV_8UC3, Scalar(255));

  random_shuffle(xrange.begin(), xrange.end());  
  for(auto i : xrange)
  {
    random_shuffle(yrange.begin(), yrange.end());
    for(auto j : yrange)
    {
      x = i+rand()%(2*jitter)-jitter+1;
      y = j+rand()%(2*jitter)-jitter+1;
      
      pix[0] = (int) image.at<Vec3b>(x,y)[2];
      pix[1] = (int) image.at<Vec3b>(x,y)[1];
      pix[2] = (int) image.at<Vec3b>(x,y)[0];

      circle(points, cv::Point(y,x), 20, CV_RGB(pix[0],pix[1],pix[2]), -1, CV_AA);
    }
  }

  for (int top = 20; top < 200; top+=5)
  {
    raio =  (200 - top)/10;

    Canny(image, border, top, 3*top);

    random_shuffle(xrange.begin(), xrange.end());  
    for(auto i : xrange)
    {
      random_shuffle(yrange.begin(), yrange.end());
      for(auto j : yrange)
      {
        if (border.at<uchar>(i,j) == 0) continue;

        x = i+rand()%(2*jitter)-jitter+1;
        y = j+rand()%(2*jitter)-jitter+1;
        
        pix[0] = (int) image.at<Vec3b>(x,y)[2];
        pix[1] = (int) image.at<Vec3b>(x,y)[1];
        pix[2] = (int) image.at<Vec3b>(x,y)[0];

        circle(points, cv::Point(y,x), raio, CV_RGB(pix[0],pix[1],pix[2]), -1, CV_AA);
      }
    }
  }
  
  imshow("CannyPontilhismo", points);
  //imshow("Canny", border);
}


int main(int argc, char** argv)
{
  image = imread(argv[1],CV_LOAD_IMAGE_COLOR);
  
  srand(time(0));
  
  width = image.size().width;
  height= image.size().height;

  namedWindow("CannyPontilhismo", 1.5);

  createTrackbar( "Step: ",             "CannyPontilhismo", &step,   STEP_SLIDER_MAX,   on_trackbar );
  createTrackbar( "Jitter: ",           "CannyPontilhismo", &jitter, JITTER_SLIDER_MAX, on_trackbar );

  on_trackbar(top, 0 );
  waitKey();
  //return 0;
}
