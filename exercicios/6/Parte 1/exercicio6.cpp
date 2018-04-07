#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

Mat mask(3,3,CV_32F), mask1;
Mat image32f, imageFiltered, result;
Mat image1, image2;

double alfa;
double l1, l2;

int y_max;
int altura = 0, centro = 0, decaimento = 1;
int regiao_slider = 0, decaimento_slider = 0, centro_slider = 0;
int maximo = 100;

char TrackbarName[50];

// Ajuste para regular a altura da região central que entrará em foco
void on_trackbar_regiao(int, void*){
	// Calculo do centro da imagem desejado
	altura = (double) (regiao_slider * y_max) / maximo;
	
	// Calculo de l1 e l2 (linhas cujo valor de αlfa assume valor em torno de 0.5)
	l1 = centro - altura/2; 
	l2 = centro + altura/2;
       
	for(int i = 0; i < result.size().height; i++)
	{
        	alfa = 0.5 * (tanh((i - l1) / decaimento) - tanh((i - l2) / decaimento));
        	addWeighted(image1.row(i), alfa, result.row(i), 1.0 - alfa, 0.0, image2.row(i));
        }
 
	imshow("Tiltshift",image2);
        imwrite("Tiltshift.png",image2); 
}

// Ajuste para regular a força de decaimento da região borrada
void on_trackbar_decaimento(int, void*){
	// O decaimento mínimo será 1 devido o cálculo do alfa
	decaimento = (double) decaimento_slider + 1;
	on_trackbar_regiao(regiao_slider, 0);
}

// Ajuste para regular a posição vertical do centro da região que entrará em foco
void on_trackbar_centro(int, void*){
	centro = (double) (centro_slider * y_max) / maximo;
	on_trackbar_regiao(regiao_slider, 0);
}


int main(int argvc, char** argv){
	float media[] = {1,1,1,
 	 	         1,1,1,
		         1,1,1};
	
	image1 = imread(argv[1]);
	image2 = image1.clone();
	
	y_max = image1.size().height;
	
  	mask = Mat(3, 3, CV_32F, media); 
	scaleAdd(mask, 1/9.0, Mat::zeros(3,3,CV_32F), mask1);
        swap(mask, mask1);
	image2.convertTo(image32f, CV_32F);
	
	// A imagem é borrada várias vezes para poder ser notado melhor o efeito de borramento
	for (int i = 0; i < 15; i++) 
	      filter2D(image32f, imageFiltered, image32f.depth(), mask, Point(2,2), 0);
	
	// A variável 'result' guarda a imagem borrada
	imageFiltered.convertTo(result, CV_8U); 

	namedWindow("Tiltshift", 1);
  
  	sprintf( TrackbarName, "Região Central: ");
	createTrackbar( TrackbarName, "Tiltshift",
				      &regiao_slider,
				      maximo,
				      on_trackbar_regiao);
	on_trackbar_regiao(regiao_slider, 0 );
	  
	sprintf( TrackbarName, "Decaimento: ");
	createTrackbar( TrackbarName, "Tiltshift",
				      &decaimento_slider,
				      maximo,
				      on_trackbar_decaimento);
	on_trackbar_decaimento(decaimento_slider, 0 );

	sprintf( TrackbarName, "Centro da Região: ");
	createTrackbar( TrackbarName, "Tiltshift",
				      &centro_slider,
				      maximo,
				      on_trackbar_centro);
	on_trackbar_centro(centro_slider, 0 );

	waitKey();
	return 0;
}
