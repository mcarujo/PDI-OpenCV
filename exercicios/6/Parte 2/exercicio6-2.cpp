#include <iostream>
#include <string>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argvc, char** argv){
	const string source = argv[1];
	int taxa = 4;
	
	// Abertura do vídeo e obtenção de alguns dos seus parâmetros
	VideoCapture inputVideo(source);
	if (!inputVideo.isOpened())
    	{
        	cout  << "O vídeo não pode ser aberto: " << source << endl;
        	return -1;
    	}
    	
    	Size S = Size((int) inputVideo.get(CAP_PROP_FRAME_WIDTH),    
                      (int) inputVideo.get(CAP_PROP_FRAME_HEIGHT));
    	int ex = static_cast<int>(inputVideo.get(CAP_PROP_FOURCC));     // Obter Codec Type- Int form
        
     	// Criação do arquivo de vídeo para escrita
    	VideoWriter outputVideo;
    	outputVideo.open("saida.avi", ex, inputVideo.get(CAP_PROP_FPS)/taxa, S, true);	    
	if (!outputVideo.isOpened())
	{
		cout  << "Não é possivel abrir o arquivo para escrita: " << source << endl;
		return -1;
	}
	
	// Parâmetros para efeito Tiltshift
	Mat mask(3,3,CV_32F), mask1;
	Mat image32f, imageFiltered, result;
	Mat image1, image2;

	double alfa;

	double altura = 0.4 * S.height; // A altura da região central será 40% da altura do vídeo 
	double centro = 0.5 * S.height; // A posição vertical do centro da região que entrará em foco estará bem no meio do vídeo
	double decaimento = 30; // O decaimento da região borrada será 30
	double l1 = centro - altura/2;
	double l2 = centro + altura/2;
	
	float media[] = {1,1,1,
 	 	         1,1,1,
		         1,1,1};
	
  	mask = Mat(3, 3, CV_32F, media); 
	scaleAdd(mask, 1/9.0, Mat::zeros(3,3,CV_32F), mask1);
        swap(mask, mask1);
        
        // Calculo do centro da imagem desejado
	altura = (double) (40 * S.height) / maximo;
	
	// Calculo de l1 e l2 (linhas cujo valor de αlfa assume valor em torno de 0.5)
	l1 = centro - altura/2; 
	l2 = centro + altura/2;
	
	Mat src, res;
	vector<Mat> spl;
	
	for(;;) //Show the image captured in the window and repeat
   	{
        	inputVideo >> src;              // read
        	if (src.empty()) break;         // check if at end
        	split(src, spl);                // process - extract only the correct channel
        	for (int i =0; i < 3; ++i)
           		if (i != 2)
                		spl[i] = Mat::zeros(S, spl[0].type());
       		merge(spl, res);
       		
       		outputVideo.write(res); 
       		outputVideo << res;
    	}
	cout << "Finished writing" << endl;
	return 0;
}	
