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

#define STEP 1
#define JITTER 3
#define RAIO 1

int top_slider = 10;
int top_slider_max = 200;

char TrackbarName[50];

Mat image, border, frame, points;

void on_trackbar_canny(int, void*){
  Canny(image, border, top_slider, 3*top_slider);
  // imshow("canny", border);
}

int main(int argc, char** argv){
  vector<int> yrange;
  vector<int> xrange;

  int width, height, gray;
  int x, y;
  
  image= imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);

  srand(time(0));
  
  if(!image.data){
	cout << "nao abriu" << argv[1] << endl;
    cout << argv[0] << " imagem.jpg";
    exit(0);
  }

  width=image.size().width;
  height=image.size().height;


  createTrackbar( TrackbarName, "canny",
                &top_slider,
                top_slider_max,
                on_trackbar_canny );

  on_trackbar_canny(top_slider, 0 );

  xrange.resize(height/STEP);
  yrange.resize(width/STEP);
  
  iota(xrange.begin(), xrange.end(), 0); 
  iota(yrange.begin(), yrange.end(), 0);

  for(uint i=0; i<xrange.size(); i++){
    xrange[i]= xrange[i]*STEP+STEP/2;
  }

  for(uint i=0; i<yrange.size(); i++){
    yrange[i]= yrange[i]*STEP+STEP/2;
  }

  points = Mat(height, width, CV_8U, Scalar(255));

  random_shuffle(xrange.begin(), xrange.end());
  
  for(auto i : xrange){
    for(auto j : yrange){
      x = i+rand()%(2*JITTER)-JITTER+1;
      y = j+rand()%(2*JITTER)-JITTER+1;
      gray = image.at<uchar>(x,y);
        circle(points,
             cv::Point(y,x),
              RAIO+2,
             CV_RGB(gray,gray,gray),
             -1,
             CV_AA);
      }
    }
    for(auto i : xrange){
      for(auto j : yrange){
        x = i+rand()%(2*JITTER)-JITTER+1;
        y = j+rand()%(2*JITTER)-JITTER+1;
        gray = image.at<uchar>(x,y);
        if(border.at<uchar>(x,y) == 255)
        {
          circle(points,
              cv::Point(y,x),
              RAIO,
              CV_RGB(gray,gray,gray),
              -1,
              CV_AA);
        }
      }
    }

  imwrite("pontos_nova.jpg", points);
  return 0;
}
