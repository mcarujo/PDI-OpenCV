# DCA0445 - PROCESSAMENTO DIGITAL DE IMAGENS
## Tarefas propostas para avaliação da primeira unidade da disciplica DCA0445.
### Alunos(as): Marco Antonio Moreira Carujo e Wysterlânya Kyury Pereira Barros


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

Segue abaixo a implementação completa do programa *regions.cpp*:

````c++
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
````
A imagem original utilizada para testar a nossa implementação é apresentada abaixo:

[![exe2](https://raw.githubusercontent.com/mcarujo/mcarujo.github.io/master/exercicios/2/biel.png)](https://github.com/mcarujo/mcarujo.github.io/blob/master/exercicios/2/biel.png)

Após serem repassado os 2 pontos na entrada, obtemos a seguinte saída:

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

Segue abaixo a implementação completa do programa *trocaregioes.cpp*:

````c++
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
````
A imagem original utilizada para testar a nossa implementação é apresentada abaixo:

[![exe2](https://raw.githubusercontent.com/mcarujo/mcarujo.github.io/master/exercicios/2/Praca-do-Comercio-Lisboa.png)](https://github.com/mcarujo/mcarujo.github.io/blob/master/exercicios/2/Praca-do-Comercio-Lisboa.png)

Nessa outra imagem temos o resultado obtido como saída do nosso programa:

[![exe2](https://raw.githubusercontent.com/mcarujo/mcarujo.github.io/master/exercicios/2/saida_troca_de_regiões.png)](https://github.com/mcarujo/mcarujo.github.io/blob/master/exercicios/2/saida_troca_de_regiões.png)

## Exercícios 3
#### Aprimoramos o algoritmo de contagem apresentado, o qual que agora consegue identificar regiões com ou sem buracos internos que existam na cena. Tambem assumimos que objetos com mais de um buraco podem existir. Incluimos suporte no nosso algoritmo para não contar bolhas que tocam as bordas da imagem. Não não presumirmos, a priori, que elas tenham buracos ou não.

O programa implementado para resolução do problema é apresentado abaixo:

````c++
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char *  * argv) {
    Mat image, mask;
    int width, height;
    int nobjects,inobjects;

    CvPoint p;
    image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);

    if ( ! image.data) {
        cout << "imagem nao carregou corretamente\n";
        return (-1);
    }
    width = image.size().width;
    height = image.size().height;

    p.x = 0;
    p.y = 0;
    //Varredura nas Bordas
    //Horizontal
    for (int i = 0; i < height; i = i + height - 1) {
        for (int j = 0; j < width; j++) {
            if (image.at<uchar>(i,j) == 255) {
                // achou um objeto
                p.x = j;
                p.y = i;
                floodFill(image, p, 0);
            }
        }
    }
    //Vertical
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j = j + width - 1) {
            if (image.at<uchar>(i,j) == 255) {
                // achou um objeto
                p.x = j;
                p.y = i;
                floodFill(image, p, 0);
            }
        }
    }
    imwrite("labeling_bordas.png", image);
    p.x=0;
    p.y=0;
    nobjects=0;
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            if(image.at<uchar>(i,j) == 255){
                // achou um objeto
                nobjects++;
                p.x=j;
                p.y=i;
                floodFill(image,p,nobjects);
            }
        }
    }

    imwrite("labeling_total.png", image);
    inobjects = 0;
    // busca objetos com buracos presentes
    p.x = 0;
    p.y = 0;
    floodFill(image, p, 255);

    for (int i = 1; i < height-1; i++) {
        for (int j = 1; j < width-1; j++) {
            if (image.at<uchar>(i-1, j) > 0 
                && image.at<uchar>(i-1,j) < 255 
                && image.at<uchar>(i,j) == 0)
            {
                // achou um objeto
                inobjects++;
                p.x = j;
                p.y = i-1;
                floodFill(image, p, 255);
                p.x = j;
                p.y = i;
                floodFill(image, p, 255);
            }
        }
    }

    imshow("image", image);
    imwrite("labeling_com_bolhas.png", image);
    waitKey();
    cout << "\nForam encontradas " << nobjects << " bolhas no total sendo " << inobjects << " com bolhas internas \n";
    return 0;
}
````
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

Segue abaixo a implementação completa do programa *equalize.cpp*:

````c++
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv){
  Mat image;
  int width, height;
  VideoCapture cap;
  vector<Mat> planes;
  Mat histR, histG, histB;
  int nbins = 64;
  float range[] = {0, 256};
  const float *histrange = { range };
  bool uniform = true;
  bool acummulate = false;

  cap.open(0);

  if(!cap.isOpened()){
    cout << "cameras indisponiveis";
    return -1;
  }

  width  = cap.get(CV_CAP_PROP_FRAME_WIDTH);
  height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);

  cout << "largura = " << width << endl;
  cout << "altura  = " << height << endl;

  int histw = nbins, histh = nbins/2;
  Mat histImgR(histh, histw, CV_8UC3, Scalar(0,0,0));
  Mat histImgG(histh, histw, CV_8UC3, Scalar(0,0,0));
  Mat histImgB(histh, histw, CV_8UC3, Scalar(0,0,0));

  while(1){
    cap >> image;
    split (image, planes);

    equalizeHist(planes[0], planes[0]);
    equalizeHist(planes[1], planes[1]);
    equalizeHist(planes[2], planes[2]);    
     
    merge(planes, image); 

    calcHist(&planes[0], 1, 0, Mat(), histR, 1,
             &nbins, &histrange,
             uniform, acummulate);
    calcHist(&planes[1], 1, 0, Mat(), histG, 1,
             &nbins, &histrange,
             uniform, acummulate);
    calcHist(&planes[2], 1, 0, Mat(), histB, 1,
             &nbins, &histrange,
             uniform, acummulate);

    

    normalize(histR, histR, 0, histImgR.rows, NORM_MINMAX, -1, Mat());
    normalize(histG, histG, 0, histImgG.rows, NORM_MINMAX, -1, Mat());
    normalize(histB, histB, 0, histImgB.rows, NORM_MINMAX, -1, Mat());
    
    histImgR.setTo(Scalar(0));
    histImgG.setTo(Scalar(0));
    histImgB.setTo(Scalar(0));

    for(int i=0; i<nbins; i++){
      line(histImgR,
           Point(i, histh),
           Point(i, histh-cvRound(histR.at<float>(i))),
           Scalar(0, 0, 255), 1, 8, 0);
      line(histImgG,
           Point(i, histh),
           Point(i, histh-cvRound(histG.at<float>(i))),
           Scalar(0, 255, 0), 1, 8, 0);
      line(histImgB,
           Point(i, histh),
           Point(i, histh-cvRound(histB.at<float>(i))),
           Scalar(255, 0, 0), 1, 8, 0);
    }

    histImgR.copyTo(image(Rect(0, 0       ,nbins, histh)));
    histImgG.copyTo(image(Rect(0, histh   ,nbins, histh)));
    histImgB.copyTo(image(Rect(0, 2*histh ,nbins, histh)));
    imshow("image", image);
    if(waitKey(30) >= 0) break;
  }
  return 0;
}
````

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

Segue abaixo a implementação completa do programa *motiondetector.cpp*:

````c++
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv){
  Mat image;
  int width, height;
  VideoCapture cap;
  vector<Mat> planes;
  Mat histR, histG, histB, histS, histS1;
  int nbins = 64, count_frames = 99999999;
  float range[] = {0, 256};
  double flag;
  const float *histrange = { range };
  bool uniform = true;
  bool acummulate = false;

  cap.open(0);
  
  if(!cap.isOpened()){
    cout << "cameras indisponiveis";
    return -1;
  }
  
  width  = cap.get(CV_CAP_PROP_FRAME_WIDTH);
  height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);

  cout << "largura = " << width << endl;
  cout << "altura  = " << height << endl;

  int histw = nbins, histh = nbins/2;
  Mat histImgR(histh, histw, CV_8UC3, Scalar(0,0,0));
  Mat histImgG(histh, histw, CV_8UC3, Scalar(0,0,0));
  Mat histImgB(histh, histw, CV_8UC3, Scalar(0,0,0));
  Mat histImgS(histh, histw, CV_8UC3, Scalar(0,0,0));

  while(1){
    cap >> image;
    split (image, planes);
    if(count_frames > 30)
    {
        count_frames = 0;
        calcHist(&planes[0], 1, 0, Mat(), histS, 1, &nbins, &histrange, uniform, acummulate);
    }

    calcHist(&planes[0], 1, 0, Mat(), histR, 1,
             &nbins, &histrange,
             uniform, acummulate);
    calcHist(&planes[1], 1, 0, Mat(), histG, 1,
             &nbins, &histrange,
             uniform, acummulate);
    calcHist(&planes[2], 1, 0, Mat(), histB, 1,
             &nbins, &histrange,
             uniform, acummulate);

    normalize(histR, histR, 0, histImgR.rows, NORM_MINMAX, -1, Mat());
    normalize(histG, histG, 0, histImgG.rows, NORM_MINMAX, -1, Mat());
    normalize(histB, histB, 0, histImgB.rows, NORM_MINMAX, -1, Mat());
     
    calcHist(&planes[0], 1, 0, Mat(), histS1, 1, &nbins, &histrange, uniform, acummulate);
    flag = compareHist(histS1, histS, CV_COMP_CORREL);

    
    if( flag < 0.80 )
    {
    cout << "Alarme com flag > "<< flag << endl;
    }

    histImgR.setTo(Scalar(0));
    histImgG.setTo(Scalar(0));
    histImgB.setTo(Scalar(0));
    
    for(int i=0; i<nbins; i++){
      line(histImgR,
           Point(i, histh),
           Point(i, histh-cvRound(histR.at<float>(i))),
           Scalar(0, 0, 255), 1, 8, 0);
      line(histImgG,
           Point(i, histh),
           Point(i, histh-cvRound(histG.at<float>(i))),
           Scalar(0, 255, 0), 1, 8, 0);
      line(histImgB,
           Point(i, histh),
           Point(i, histh-cvRound(histB.at<float>(i))),
           Scalar(255, 0, 0), 1, 8, 0);
    }
    
    histImgR.copyTo(image(Rect(0, 0       ,nbins, histh)));
    histImgG.copyTo(image(Rect(0, histh   ,nbins, histh)));
    histImgB.copyTo(image(Rect(0, 2*histh ,nbins, histh)));
    count_frames++;
    imshow("image", image);
    if(waitKey(30) >= 0) break;
  }
  return 0;
}
````

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

[![exe3](https://raw.githubusercontent.com/mcarujo/mcarujo.github.io/master/exercicios/5/original.png)](https://github.com/mcarujo/mcarujo.github.io/blob/master/exercicios/5/original.png)

A imagem capturada apenas com o filtro do laplaciano:

[![exe4](https://raw.githubusercontent.com/mcarujo/mcarujo.github.io/master/exercicios/5/la1.png)](https://github.com/mcarujo/mcarujo.github.io/blob/master/exercicios/5/la1.png)

E a imagem capturada com o filtro do laplaciano do gaussiano:

[![exe5](https://raw.githubusercontent.com/mcarujo/mcarujo.github.io/master/exercicios/5/lg1.png)](https://github.com/mcarujo/mcarujo.github.io/blob/master/exercicios/5/lg1.png)

Como podemos observar, com o filtro do laplaciano do gaussiano podemos obter uma imagem com as bordas mais ressaltadas, porém com um pouco mais de ruído quando comparado com resultado obtido apenas com a aplicação do filtro laplaciano.

## Exercícios 6.1
#### Utilizando o programa exemplos/addweighted.cpp como referência, implementamos um programa tiltshift.cpp. Com três ajustes que são providos na tela da interface:

* um ajuste para regular a altura da região central que entrará em foco;

* um ajuste para regular a força de decaimento da região borrada;

* um ajuste para regular a posição vertical do centro da região que entrará em foco. Finalizado o programa, a imagem produzida deverá ser salva em arquivo.

No main definimos a máscara de borramento *media* e o realizamos o borramento da imagem 15 vezes para se tornar mais vísivel o borramento. No main também declaramos as barras da nossa janela para o controle dos ajustes desejados. Obtivemos então a nova tela para visualação da imagem e exebição das barras de ajuste:

[![exe6](https://raw.githubusercontent.com/mcarujo/mcarujo.github.io/master/exercicios/6/Parte%201/tela.png)](https://github.com/mcarujo/mcarujo.github.io/blob/master/exercicios/6/Parte%201/tela.png)

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

[![exe7](https://raw.githubusercontent.com/mcarujo/mcarujo.github.io/master/exercicios/6/Parte%201/entrada.jpg)](https://github.com/mcarujo/mcarujo.github.io/blob/master/exercicios/6/Parte%201/entrada.jpg)

Nessa outra imagem temos o resultado obtido ao definir a igreja e a casa vermelha como região de foco :

[![exe8](https://raw.githubusercontent.com/mcarujo/mcarujo.github.io/master/exercicios/6/Parte%201/saida_igreja.png)](https://github.com/mcarujo/mcarujo.github.io/blob/master/exercicios/6/Parte%201/saida_igreja.png)

E nessa imagem temos o resultado obtido ao definir a casa mais próxima ao lago como região de foco :

[![exe9](https://raw.githubusercontent.com/mcarujo/mcarujo.github.io/master/exercicios/6/Parte%201/saida_casa_do_lago.png)](https://github.com/mcarujo/mcarujo.github.io/blob/master/exercicios/6/Parte%201/saida_casa_do_lago.png)

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

[![Canon EOS 100D Full HD Sample Video](https://raw.githubusercontent.com/mcarujo/mcarujo.github.io/master/exercicios/6/Parte%202/Entrada.png)](https://youtu.be/uaCtl8rblro "Everything Is AWESOME")

Usando esse vídeo como entrada, obtivemos o seguinte vídeo de saída:

[![Saida do Programa](https://raw.githubusercontent.com/mcarujo/mcarujo.github.io/master/exercicios/6/Parte%202/Saida.png)](https://drive.google.com/file/d/1B0TDSFUQI_xH6XCPl2o8oF90m5A6h8sj/view?usp=sharing "new")





## Exercícios 7


####    Utilizando o programa exemplos/dft.cpp como referência, implemente o filtro homomórfico para melhorar imagens com iluminação irregular. Crie uma cena mal iluminada e ajuste os parâmetros do filtro homomórfico para corrigir a iluminação da melhor forma possível. Assuma que a imagem fornecida é em tons de cinza.

O programa se dá aatravés da alteração do filtro utilizado na imagem, sendo agora utilizado um filtro homomórfico que possui como parâmetros ajustáveis os componentes: Gl - iluminância; Gh - reflectância; d - frequência de corte; e c - constante que controla a transição entre Gl e Gh. O switch case da questão foi modificado para permitir o ajuste desses parâmetros. O algoritmo implementado é apresentado abaixo:

```c++
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#define RADIUS 20

using namespace cv;
using namespace std;

// troca os quadrantes da imagem da DFT
void deslocaDFT(Mat& image ){
  Mat tmp, A, B, C, D;

  // se a imagem tiver tamanho impar, recorta a regiao para
  // evitar cópias de tamanho desigual
  image = image(Rect(0, 0, image.cols & -2, image.rows & -2));
  int cx = image.cols/2;
  int cy = image.rows/2;

  // reorganiza os quadrantes da transformada
  // A B   ->  D C
  // C D       B A
  A = image(Rect(0, 0, cx, cy));
  B = image(Rect(cx, 0, cx, cy));
  C = image(Rect(0, cy, cx, cy));
  D = image(Rect(cx, cy, cx, cy));

  // A <-> D
  A.copyTo(tmp);  D.copyTo(A);  tmp.copyTo(D);

  // C <-> B
  C.copyTo(tmp);  B.copyTo(C);  tmp.copyTo(B);
}

int main(int , char**){
  VideoCapture cap;
  Mat imaginaryInput, complexImage, multsp;
  Mat padded, filter, mag;
  Mat image, imagegray, tmp;
  Mat_<float> realInput, zeros;
  vector<Mat> planos;
  
  float Gh = 1.0, Gl = 1.0, d = 1.0, c = 1.0;
  double radius;

  // guarda tecla capturada
  char key;

  // valores ideais dos tamanhos da imagem
  // para calculo da DFT
  int dft_M, dft_N;

  // abre a câmera default
  cap.open(1);
  if(!cap.isOpened())
    return -1;

  // captura uma imagem para recuperar as
  // informacoes de gravação
  cap >> image;

  // identifica os tamanhos otimos para
  // calculo do FFT
  dft_M = getOptimalDFTSize(image.rows);
  dft_N = getOptimalDFTSize(image.cols);

  // realiza o padding da imagem
  copyMakeBorder(image, padded, 0,
                 dft_M - image.rows, 0,
                 dft_N - image.cols,
                 BORDER_CONSTANT, Scalar::all(0));

  // parte imaginaria da matriz complexa (preenchida com zeros)
  zeros = Mat_<float>::zeros(padded.size());

  // prepara a matriz complexa para ser preenchida
  complexImage = Mat(padded.size(), CV_32FC2, Scalar(0));

  // a função de transferência (filtro frequencial) deve ter o
  // mesmo tamanho e tipo da matriz complexa
  filter = complexImage.clone();

  // cria uma matriz temporária para criar as componentes real
  // e imaginaria do filtro ideal
  tmp = Mat(dft_M, dft_N, CV_32F);

  // prepara o filtro homomorfico
  for(int i=0; i<dft_M; i++)
  {
    for(int j=0; j<dft_N; j++)
    {
      radius = (double) (i - dft_M / 2) * (i - dft_M / 2) + (j - dft_N / 2) * (j - dft_N / 2);
      tmp.at<float> (i, j) = (Gh - Gl) * (1 - exp(-c * (radius / pow(d, 2)))) + Gl;
    }
  }

  // cria a matriz com as componentes do filtro e junta
  // ambas em uma matriz multicanal complexa
  Mat comps[]= {tmp, tmp};
  merge(comps, 2, filter);

  for(;;){
    cap >> image;
    cvtColor(image, imagegray, CV_BGR2GRAY);
    imshow("original", imagegray);

    // realiza o padding da imagem
    copyMakeBorder(imagegray, padded, 0,
                   dft_M - image.rows, 0,
                   dft_N - image.cols,
                   BORDER_CONSTANT, Scalar::all(0));

    // limpa o array de matrizes que vao compor a
    // imagem complexa
    planos.clear();
    // cria a compoente real
    realInput = Mat_<float>(padded);
    // insere as duas componentes no array de matrizes
    planos.push_back(realInput);
    planos.push_back(zeros);

    // combina o array de matrizes em uma unica
    // componente complexa
    merge(planos, complexImage);

    // calcula o dft
    dft(complexImage, complexImage);

    // realiza a troca de quadrantes
    deslocaDFT(complexImage);

    // aplica o filtro frequencial
    mulSpectrums(complexImage,filter,complexImage,0);

    // limpa o array de planos
    planos.clear();

    // troca novamente os quadrantes
    deslocaDFT(complexImage);

    cout << "Gl = " << Gl << " Gh = " << Gh << " D0 = " << d << " c = " << c << endl;
    // calcula a DFT inversa
    idft(complexImage, complexImage);

    // limpa o array de planos
    planos.clear();

    // separa as partes real e imaginaria da
    // imagem filtrada
    split(complexImage, planos);

    // normaliza a parte real para exibicao
    normalize(planos[0], planos[0], 0, 1, CV_MINMAX);
    imshow("filtrada", planos[0]);

    key = (char) waitKey(10);
    if( key == 27 ) break; // esc pressed!
    switch(key){
      // aumenta o componente de iluminância (Gl)
    case 'a':
      Gl = Gl + 1;
      break;
      // diminui o componente de iluminância (Gl)
    case 's':
      Gl = Gl - 1;
      break;
      // aumenta o componente de refletância (Gh)
    case 'd':
      Gh = Gh + 1;
      break;
      // diminui o componente de refletância (Gh)
    case 'f':
      Gh = Gh - 1;
      // aumenta o componente de frequencia de corte (d)
    case 'g':
      d = d + 1;
      break;
      // diminui o componente de frequencia de corte (d)
    case 'h':
      d = d - 1;
      break;
      // aumenta a constante (c)
    case 'j':
      c = c + 1;
      break;
      // diminui a constante (c)
    case 'k':
      c = c - 1;
      break;
    }
  }
  return 0;
}
```

A imagem original de entrada é apresentada a seguir:

[![exe10](https://raw.githubusercontent.com/mcarujo/mcarujo.github.io/master/exercicios/7/original_screenshot_23.05.2018.png)](https://github.com/mcarujo/mcarujo.github.io/blob/master/exercicios/7/original_screenshot_23.05.2018.png)

A essa imagem foi aplicado um filtro homomórifco com os parâmetros: Gl = 62; Gh = 89; d = -22.3 e c = -11. A image obtida após isso é ilustrada abaixo:

[![exe10](https://raw.githubusercontent.com/mcarujo/mcarujo.github.io/master/exercicios/7/filtrada_screenshot_23.05.2018.png)](https://github.com/mcarujo/mcarujo.github.io/blob/master/exercicios/7/filtrada_screenshot_23.05.2018.png)

Podemos observar assim que através do uso do filtro homomórfico foi possível corrigirmos a iluminação da imagem com iluminação irregular. 


## Exercícios 8

####    Utilizando os programas exemplos/canny.cpp e exemplos/pontilhismo.cpp como referência, implementamos um programa nova.cpp. Cuja a idéia é utilizar as bordas produzidas pelo algoritmo de Canny para suavizar as bordas da minha imagem pontilhista gerada. O Programa nova.cpp efetua pontos maiores para toda a região da imagem, após isso utilizamos o resultado do Canny para indentificar as bordas e efetuar pontos de raios menores, deixando assim a imagem com borda mais suave.

A imagem para exemplificar:

[![exe8](https://raw.githubusercontent.com/mcarujo/mcarujo.github.io/master/exercicios/8/biel.png)](https://github.com/mcarujo/mcarujo.github.io/blob/master/exercicios/8/biel.png)


Resultado do algoritmo de Canny(canny.cpp):

[![exe8](https://raw.githubusercontent.com/mcarujo/mcarujo.github.io/master/exercicios/8/canny.png)](https://github.com/mcarujo/mcarujo.github.io/blob/master/exercicios/8/canny.png)


Resultado do pontilhismo.cpp:

[![exe8](https://raw.githubusercontent.com/mcarujo/mcarujo.github.io/master/exercicios/8/pontos.png)](https://github.com/mcarujo/mcarujo.github.io/blob/master/exercicios/8/pontos.png)


Resultado da combinação de Canny com o pontilhismo.cpp (nova.cpp):

[![exe8](https://raw.githubusercontent.com/mcarujo/mcarujo.github.io/master/exercicios/8/pontos_nova.png)](https://github.com/mcarujo/mcarujo.github.io/blob/master/exercicios/8/pontos_nova.png)

```c++
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
```

## Exercícios 9









