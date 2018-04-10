#include <iostream>
#include <math.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
  Mat image;

  image = imread("Praca-do-Comercio-Lisboa.png", CV_LOAD_IMAGE_COLOR);
  if (!image.data)
    cout << "nao abriu a imagem" << endl;

  int image_width = image.size().width;
  int image_height = image.size().height;

  Mat superior_esquerdo(image, Rect(0, 0, image_width / 2, image_height / 2));
  Mat inferior_esquerdo(image, Rect(image_width / 2, 0, image_width / 2, image_height / 2));
  Mat superior_direito(image, Rect(0, image_height / 2, image_width / 2, image_height / 2));
  Mat inferior_direito(image, Rect(image_width / 2, image_height / 2, image_width / 2, image_height / 2));

  Mat resultado = Mat::zeros(image.size(), image.type());
  Mat ponteiro;

  ponteiro = resultado.colRange(image_width / 2, image_width).rowRange(0, image_height / 2);
  superior_direito.copyTo(ponteiro);

  ponteiro = resultado.colRange(0, image_width / 2).rowRange(image_height / 2, image_height);
  inferior_esquerdo.copyTo(ponteiro);

  ponteiro = resultado.colRange(image_width / 2, image_width).rowRange(image_height / 2, image_height);
  superior_esquerdo.copyTo(ponteiro);

  ponteiro = resultado.colRange(0, image_width / 2).rowRange(0, image_height / 2);
  inferior_direito.clone().copyTo(ponteiro);

  namedWindow("janela", WINDOW_AUTOSIZE);
  imshow("janela", resultado);
  waitKey();
  return 0;
}
