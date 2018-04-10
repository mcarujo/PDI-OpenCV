//Autor: Marco Carujo
//Data: 02/03/2018

#include <math.h>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int, char **)
{
  int p1x, p1y;
  int p2x, p2y;

  Mat image;

  image = imread("biel.png", CV_LOAD_IMAGE_GRAYSCALE);
  if (!image.data)
    cout << "nao abriu a imagem.png" << endl;

  cout << "Porfavor me informa o ponto 1 x e y :";
  cout << "\n";
  cin >> p1x >> p1y;
  cout << "Porfavor me informa o ponto 2 x e y :";
  cout << "\n";
  cin >> p2x >> p2y;
  int px_start, px_finish;
  int py_start, py_finish;
  if (p1x < p2x)
  {
    px_start = p1x;
    px_finish = p2x;
  }
  else
  {
    px_start = p2x;
    px_finish = p1x;
  }
  if (p1y < p2y)
  {
    py_start = p1y;
    py_finish = p2y;
  }
  else
  {
    py_start = p2y;
    py_finish = p1y;
  }

  namedWindow("janela", WINDOW_AUTOSIZE);

  for (int i = px_start; i < px_finish; i++)
  {
    for (int j = py_start; j < py_finish; j++)
    {
      image.at<uchar>(i, j) = abs(image.at<uchar>(i, j) - 255);
    }
  }
  imshow("janela", image);
  waitKey();

  return 0;
}