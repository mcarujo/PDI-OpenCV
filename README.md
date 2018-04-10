# DCA0445 - PROCESSAMENTO DIGITAL DE IMAGENS
## Tarefas propostas para avaliação da primeira unidade da disciplica DCA0445.
### Alunos(as): Marco Antonio Moreira Carujo e Wysterlania Kyury Pereira Barros


## Exercícios 2
#### Utilizando o programa exemplos/pixels.cpp como referência,implementamos um programa regios.cpp o qual solicita ao usuário as cordenadas de 2 pontos da maneira mostrada na figura. Os mesmos localizados dentro dos limites do tamanho da imagem. Após isso, a região definida pelo retângulo de vértices opostos definidos pelos pontos será exibida com o negativo da imagem na região correspondente. O efeito é ilustrado na Figura Abaixo. 

O bloco abaixo está pegando cada pixel dentro da área informada, para subtrair 255 e efetuar o módulo. 
```c++
for (int i = px_start; i < px_finish; i++)
  {
    for (int j = py_start; j < py_finish; j++)
    {
      image.at<uchar>(i, j) = abs(image.at<uchar>(i, j) - 255);
    }
}
```
Entrada deve está dentro do limite da imagem.

[![exe2](https://raw.githubusercontent.com/mcarujo/mcarujo.github.io/master/exercicios/2/entrada_regions.png)](https://github.com/mcarujo/mcarujo.github.io/blob/master/exercicios/2/entrada_regions.png)

Após serem repassado os 2 pontos na entrada, temos uma saída como:

[![exe2](https://raw.githubusercontent.com/mcarujo/mcarujo.github.io/master/exercicios/2/sainda_regions.png)](https://github.com/mcarujo/mcarujo.github.io/blob/master/exercicios/2/sainda_regions.png)

#### Também seguindo o programa exemplos/pixels.cpp como referência, implementamos um programa trocaregioes.cpp, o qual divide a imagem em 4 quadrantes e troca eles de posições.

O código abaixo é responsavel para salvar os quatro pedaços da imagem principal.
```c++
  Mat superior_esquerdo(image, Rect(0, 0, image_width / 2, image_height / 2));
  Mat inferior_esquerdo(image, Rect(image_width / 2, 0, image_width / 2, image_height / 2));
  Mat superior_direito(image, Rect(0, image_height / 2, image_width / 2, image_height / 2));
Mat inferior_direito(image, Rect(image_width / 2, image_height / 2, image_width / 2, image_height / 2));
```
Onde o bloco seguinte está copiando cada pedeço para uma nova imagem, e durante o processo, trocando as possições do quadrante.
```c++
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
```

[![exe2](https://raw.githubusercontent.com/mcarujo/mcarujo.github.io/master/exercicios/2/saida_troca_de_regiões.png)](https://github.com/mcarujo/mcarujo.github.io/blob/master/exercicios/2/saida_troca_de_regiões.png)

## Exercícios 3
#### Aprimoramos o algoritmo de contagem apresentado, o qual que agora consegue identificar regiões com ou sem buracos internos que existam na cena. Tambem assumimos que objetos com mais de um buraco podem existir. Incluimos suporte no nosso algoritmo para não contar bolhas que tocam as bordas da imagem. Não não presumirmos, a priori, que elas tenham buracos ou não.

Executando o comando para execução do programa labeling:

[![exe2](https://raw.githubusercontent.com/mcarujo/mcarujo.github.io/master/exercicios/3/entrada.png)](https://github.com/mcarujo/mcarujo.github.io/blob/master/exercicios/3/entrada.png)

Recebendo a imagem a seguir como entrada:

[![exe2](https://raw.githubusercontent.com/mcarujo/mcarujo.github.io/master/exercicios/3/bolhas.png)](https://github.com/mcarujo/mcarujo.github.io/blob/master/exercicios/3/bolhas.png)

Desconsiderando as bolhas que tocam as bordas temos a seguinte imagem:

[![exe2](https://raw.githubusercontent.com/mcarujo/mcarujo.github.io/master/exercicios/3/labeling_bordas.png)](https://github.com/mcarujo/mcarujo.github.io/blob/master/exercicios/3/labeling_bordas.png)

Fazendo a contagem total de bolhas, geramos essa imagem auxiliar: 

[![exe2](https://raw.githubusercontent.com/mcarujo/mcarujo.github.io/master/exercicios/3/labeling_total.png)](https://github.com/mcarujo/mcarujo.github.io/blob/master/exercicios/3/labeling_total.png)

E considerando apenas as que não possem bolhas internas:

[![exe2](https://raw.githubusercontent.com/mcarujo/mcarujo.github.io/master/exercicios/3/labeling_com_bolhas.png)](https://github.com/mcarujo/mcarujo.github.io/blob/master/exercicios/3/labeling_com_bolhas.png)

Temos a resposta de que foram identificadas 21 bolhas no total sendo 7 com bolhas internas

## Exercícios 4
#### Utilizando o programa exemplos/histogram.cpp como referência, implementamos um programa equalize.cpp. O qual para cada imagem capturada, realizar a equalização do histogram antes de exibir a imagem. 

Sem a equalização, e com um cenário com pouca iluminação notamos que o histograma fica com tons contrados proximo a zero como demonstra a seguinte imagem:

[![exe2](https://raw.githubusercontent.com/mcarujo/mcarujo.github.io/master/exercicios/4/sem_equalizar.png)](https://github.com/mcarujo/mcarujo.github.io/blob/master/exercicios/4/sem_equalizar.png)

Aopós a equalização notamos o hisograma fica com tons mais espalhados e com uma transiço brusca entre os tons.

[![exe2](https://raw.githubusercontent.com/mcarujo/mcarujo.github.io/master/exercicios/4/com_equalizar.png)](https://github.com/mcarujo/mcarujo.github.io/blob/master/exercicios/4/com_equalizar.png)

O processo da equalização é feito antes de ser calculado os histogramas e ser mostrado a imagem capturada pela câmera, assim que obtivemos a imagem fazemos a equalização da mesma.
```c++
 cap >> image;
    split (image, planes);

    equalizeHist(planes[0], planes[0]);
    equalizeHist(planes[1], planes[1]);
    equalizeHist(planes[2], planes[2]);    
     
    merge(planes, image); 
```

#### Utilizando o programa exemplos/histogram.cpp como referência, implementamos um programa motiondetector.cpp. O programa está calculando os histogramas das imagens, mas utiliza apenas um histograma para verificar se houve uma mudança no cenário filmado.

o programa faz uma amostragem de 30 frames para capturar o seu frame de referência para comprar se houve mudança brusca no cenrio da câmera ou não.

```c++
if(count_frames > 30)
    {
        count_frames = 0;
        calcHist(&planes[0], 1, 0, Mat(), histS, 1, &nbins, &histrange, uniform, acummulate);
    }
```
Esse histograma calculado é atualizado a cada 30 frames, e serve de comparação para o histograma em tempo real, e caso seja dectadada alguma diferença alta, será imprimido no terminal o alerta, o valor limitar para determinaço de que houve alteração do cenrio foi determinado por Heurística.
```c++
   if( flag < 0.80 )
    {
    cout << "Alarme com flag > "<< flag << endl;
    }
```

[![exe2](https://raw.githubusercontent.com/mcarujo/mcarujo.github.io/master/exercicios/4/motion.png)](https://github.com/mcarujo/mcarujo.github.io/blob/master/exercicios/4/motion.png)

## Exercícios 5
#### Utilizando o programa exemplos/filtroespacial.cpp como referência, implementamos um programa laplgauss.cpp. O nosso programa consegue acrescentar mais uma funcionalidade ao exemplo fornecido, permitindo que seja calculado o laplaciano do gaussiano das imagens capturadas. Comparamos o resultado desse filtro com a simples aplicação do filtro laplaciano.

Com base na literatura, temos que o filtro do laplaciano do gaussiano possui a seguinte máscara, definida em nosso código como segue:

```c++
  float laplacian_gauss[] = {0, 0,-1, 0, 0,
			     0,-1,-2,-1, 0,
			    -1,-2,16,-2,-1,
			     0,-1,-2,-1, 0,
			     0, 0,-1, 0, 0};
```

Ao nosso menu de opções de filtro uma nova opção foi adicionada, a opção 'n', a qual realiza a aplicação do filtro do laplaciano do gaussiano na imagem capturada. Escolhendo essa nova opção de filtro o switch case, que determina a ação realizada de acordo com a entrada do usuário no menu, nos direciona ao seguinte trecho de código: 

```c++
    case 'n':
	  menu();
      mask = Mat(5, 5, CV_32F, laplacian_gauss);
      printmask(mask);
      break;
```

Neste caso temos a seleção da máscara do laplaciano do gaussiano apresentada anteriormente, a qual é utilizada para filtrar as imagens capturadas conforme é realizado também na aplicação dos demais filtros.

Segueu abaixo a implementação completa do código:

```c++
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void printmask(Mat &m){
  for(int i=0; i<m.size().height; i++){
    for(int j=0; j<m.size().width; j++){
      cout << m.at<float>(i,j) << ",";
    }
    cout << endl;
  }
}

void menu(){
  cout << "\npressione a tecla para ativar o filtro: \n"
	"a - calcular modulo\n"
        "m - media\n"
        "g - gauss\n"
        "v - vertical\n"
	"h - horizontal\n"
        "l - laplaciano\n"
	"n - laplaciano do gaussiano\n" 
	"esc - sair\n";
}

int main(int argvc, char** argv){
  VideoCapture video;
  float media[] = {1,1,1,
				   1,1,1,
				   1,1,1};
  float gauss[] = {1,2,1,
				   2,4,2,
				   1,2,1};
  float horizontal[]={-1,0,1,
					  -2,0,2,
					  -1,0,1};
  float vertical[]={-1,-2,-1,
					0,0,0,
					1,2,1};
  float laplacian[]={0,-1,0,
					 -1,4,-1,
					 0,-1,0};
  float laplacian_gauss[]={0,0,-1,0,0,
					 0,-1,-2,-1,0,
					 -1,-2,16,-2,-1,
					 0,-1,-2,-1,0,
					 0,0,-1,0,0};

  Mat cap, frame, frame32f, frameFiltered;
  Mat mask(3,3,CV_32F), mask1;
  Mat result, result1;
  double width, height, min, max;
  int absolut;
  char key;
  
  video.open(0); 
  if(!video.isOpened()) 
    return -1;
  width=video.get(CV_CAP_PROP_FRAME_WIDTH);
  height=video.get(CV_CAP_PROP_FRAME_HEIGHT);
  std::cout << "largura=" << width << "\n";;
  std::cout << "altura =" << height<< "\n";;

  namedWindow("filtroespacial",1);

  mask = Mat(3, 3, CV_32F, media); 
  scaleAdd(mask, 1/9.0, Mat::zeros(3,3,CV_32F), mask1);
  swap(mask, mask1);
  absolut=1; // calcs abs of the image

  menu();
  for(;;){
    video >> cap; 
    cvtColor(cap, frame, CV_BGR2GRAY);
    flip(frame, frame, 1);
    imshow("original", frame);
    frame.convertTo(frame32f, CV_32F);
    filter2D(frame32f, frameFiltered, frame32f.depth(), mask, Point(1,1), 0);
    if(absolut){
      frameFiltered=abs(frameFiltered);
    }
    frameFiltered.convertTo(result, CV_8U); 
    
    imshow("filtroespacial", result);
    key = (char) waitKey(10);
    if( key == 27 ) break; // esc pressed!
    switch(key){
    case 'a':
	  menu();
      absolut=!absolut;
      break;
    case 'm':
	  menu();
      mask = Mat(3, 3, CV_32F, media);
      scaleAdd(mask, 1/9.0, Mat::zeros(3,3,CV_32F), mask1);
      mask = mask1;
      printmask(mask);
      break;
    case 'g':
	  menu();
      mask = Mat(3, 3, CV_32F, gauss);
      scaleAdd(mask, 1/16.0, Mat::zeros(3,3,CV_32F), mask1);
      mask = mask1;
      printmask(mask);
      break;
    case 'h':
	  menu();
      mask = Mat(3, 3, CV_32F, horizontal);
      printmask(mask);
      break;
    case 'v':
	  menu();
      mask = Mat(3, 3, CV_32F, vertical);
      printmask(mask);
      break;
    case 'l':
	  menu();
      mask = Mat(3, 3, CV_32F, laplacian);
      printmask(mask);
      break;
    case 'n':
	  menu();
      mask = Mat(5, 5, CV_32F, laplacian_gauss);
      printmask(mask);
      break;
    default:
      break;
    }
  }
  return 0;
}
```

Essa foi a imagem capturada para ser utilizada como teste da nossa implementação, sendo aqui apresentada a imagem original sem nenhum filtro: 

[![exe3](https://github.com/mcarujo/mcarujo.github.io/blob/master/exercicios/5/original.png)](https://github.com/mcarujo/mcarujo.github.io/blob/master/exercicios/5/original.png)

A imagem capturada apenas com o filtro do laplaciano:

[![exe4](https://github.com/mcarujo/mcarujo.github.io/blob/master/exercicios/5/la1.png)](https://github.com/mcarujo/mcarujo.github.io/blob/master/exercicios/5/la1.png)

E a imagem capturada com o filtro do laplaciano do gaussiano:

[![exe5](https://github.com/mcarujo/mcarujo.github.io/blob/master/exercicios/5/lg1.png)](https://github.com/mcarujo/mcarujo.github.io/blob/master/exercicios/5/lg1.png)

Como podemos observar, com o filtro do laplaciano do gaussiano podemos obter uma imagem com as bordas mais ressaltadas, porém com um pouco mais de ruído quando comparado com resultado obtido apenas com a aplicação do filtro laplaciano.

## Exercícios 6.1
#### Utilizando o programa exemplos/addweighted.cpp como referência, implementamos um programa tiltshift.cpp. Com três ajustes que são providos na tela da interface:

* um ajuste para regular a altura da região central que entrará em foco;

* um ajuste para regular a força de decaimento da região borrada;

* um ajuste para regular a posição vertical do centro da região que entrará em foco. Finalizado o programa, a imagem produzida deverá ser salva em arquivo.

No main definimos a máscara de borramento *media* e o realizamos o borramento da imagem 15 vezes para se tornar mais vísivel o borramento. No main também declaramos as barras da nossa janela para o controle dos ajustes desejados. Obtivemos então a nova tela para visualação da imagem e exebição das barras de ajuste:

[![exe6](https://github.com/mcarujo/mcarujo.github.io/blob/master/exercicios/6/Parte%201/tela.png)](https://github.com/mcarujo/mcarujo.github.io/blob/master/exercicios/6/Parte%201/tela.png)

Na função *on_trackbar_centro* temos o ajuste para regular a posição vertical do centro da região que entrará em foco. Em outra função, denominada *on_trackbar_decaimento* temos o ajuste para regular a força de decaimento da região borrada, sendo o decaimento no mínimo 1. E, por fim, temos a função *on_trackbar_regiao* responsável por regular a altura da região central que entrará em foco e atualizar a imagem em exibição e salvá-la.

O código implementado é apresentado a seguir: 

```c++
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
```

A imagem original utilizada para testar a nossa implementação é apresentada abaixo:

[![exe7](https://github.com/mcarujo/mcarujo.github.io/blob/master/exercicios/6/Parte%201/entrada.jpg)](https://github.com/mcarujo/mcarujo.github.io/blob/master/exercicios/6/Parte%201/entrada.jpg)

Nessa outra imagem temos o resultado obtido ao definir a igreja e a casa vermelha como região de foco :

[![exe8](https://github.com/mcarujo/mcarujo.github.io/blob/master/exercicios/6/Parte%201/saida_igreja.png)](https://github.com/mcarujo/mcarujo.github.io/blob/master/exercicios/6/Parte%201/saida_igreja.png)

E nessa imagem temos o resultado obtido ao definir a casa mais próxima ao lago como região de foco :

[![exe9](https://github.com/mcarujo/mcarujo.github.io/blob/master/exercicios/6/Parte%201/saida_casa_do_lago.png)](https://github.com/mcarujo/mcarujo.github.io/blob/master/exercicios/6/Parte%201/saida_casa_do_lago.png)

## Exercícios 6.2
#### Utilizando o programa exemplos/addweighted.cpp como referência, implementamos um programa tiltshiftvideo.cpp. O qual é capaz de processar um arquivo de vídeo, produzir o efeito de tilt-shift nos quadros presentes e escrever o resultado em outro arquivo de vídeo.

O programa se dá através da leitura de um arquivo de vídeo e criação de um arquivo de vídeo para escrita do novo vídeo. Para a escrita do nosso vídeo de saída descartamos alguns quadros do vídeo original para evidenciar o efeito de stop motion, reduzindo também o fps do vídeo de entrada pela metade no vídeo de saída.

O efeito de borramento do vídeo se deu utilizando a mesma ideia implementada no exercício 6.1, com a única diferença do borramento ser realizado por uma máscara 9x9. Para realização do borramento definimos a altura da região central do foco como 30% da altura do vídeo, a posição vertical do centro da região que entrará em foco ao meio do vídeo e o decaimento da região borrada igual a 10.

O código implementado é apresentado a seguir: 

```c++
#include <iostream>
#include <string>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argvc, char** argv){
	const string source = argv[1];
	int cont = 0, taxa = 2;
	
	// Abertura do vídeo e obtenção de alguns dos seus parâmetros
	VideoCapture inputVideo(source);
	if (!inputVideo.isOpened())
    	{
        	cout  << "O vídeo não pode ser aberto: " << source << endl;
        	return -1;
    	}
    	
    	Size S = Size((int) inputVideo.get(CAP_PROP_FRAME_WIDTH),    
                      (int) inputVideo.get(CAP_PROP_FRAME_HEIGHT));
        
     	// Criação do arquivo de vídeo para escrita
    	VideoWriter outputVideo;
    	outputVideo.open("saida.mkv", CV_FOURCC('D', 'I', 'V', '3'), inputVideo.get(CAP_PROP_FPS)/taxa, S, true);	    
	if (!outputVideo.isOpened())
	{
		cout  << "Não é possivel abrir o arquivo para escrita: " << source << endl;
		return -1;
	}
	
	// Parâmetros para efeito Tiltshift
	Mat mask(9,9,CV_32F), mask1;
	Mat image32f, imageFiltered, result;
	Mat image1, image2, res;

	double alfa;

	double altura = 0.3 * S.height; // A altura da região central será 30% da altura do vídeo 
	double centro = 0.5 * S.height; // A posição vertical do centro da região que entrará em foco estará bem no meio do vídeo
	double decaimento = 10; // O decaimento da região borrada será 10
	double l1 = centro - altura/2;
	double l2 = centro + altura/2;
	
	float media[] = {1,1,1,1,1,1,1,1,1,
 	 	         1,1,1,1,1,1,1,1,1,
 	 	         1,1,1,1,1,1,1,1,1,
 	 	         1,1,1,1,1,1,1,1,1,
 	 	         1,1,1,1,1,1,1,1,1,
 	 	         1,1,1,1,1,1,1,1,1,
 	 	         1,1,1,1,1,1,1,1,1,
 	 	         1,1,1,1,1,1,1,1,1,
		         1,1,1,1,1,1,1,1,1};
	
  	mask = Mat(9, 9, CV_32F, media); 
	scaleAdd(mask, 1/81.0, Mat::zeros(9,9,CV_32F), mask1);
        swap(mask, mask1);
		
	for(;;)
   	{
   	   	cont++;
   		
   		if(cont > 100)
   		{
			inputVideo >> image1;              
			if (image1.empty()) break; // checa se o vídeo acabou
			
			image2 = image1.clone();
			image2.convertTo(image32f, CV_32F);
			
			// A imagem é borrada várias vezes para poder ser notado melhor o efeito de borramento
			for (int i = 0; i < 100; i++) 
				filter2D(image32f, imageFiltered, image32f.depth(), mask, Point(2,2), 0);
			
			// A variável 'result' guarda a imagem borrada
			imageFiltered.convertTo(result, CV_8U); 
			
			for(int i = 0; i < result.size().height; i++)
			{
				alfa = 0.5 * (tanh((i - l1) / decaimento) - tanh((i - l2) / decaimento));
				addWeighted(image1.row(i), alfa, result.row(i), 1.0 - alfa, 0.0, image2.row(i));
			}
       		
       			outputVideo << image2;
       			cont = 0;
       		}
    	}

	return 0;
}
```

O vídeo original utilizado para testar a nossa implementação é apresentado abaixo:

[![Everything Is AWESOME](https://github.com/mcarujo/mcarujo.github.io/blob/master/exercicios/6/Parte%202/Entrada.png)](https://youtu.be/uaCtl8rblro "Everything Is AWESOME")

Usando esse vídeo como entrada, obtivemos o seguinte vídeo de saída:

[![new](https://github.com/mcarujo/mcarujo.github.io/blob/master/exercicios/6/Parte%202/Saida.png)](https://drive.google.com/file/d/1B0TDSFUQI_xH6XCPl2o8oF90m5A6h8sj/view?usp=sharing "new")
