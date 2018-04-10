# DCA0445 - PROCESSAMENTO DIGITAL DE IMAGENS
## Tarefas propostas para avaliação da primeira unidade da disciplica DCA0445.
### Alunos(as): Marco Antonio Moreira Carujo e Wysterlania Kyury Pereira Barros


## Exercícios 2
#### Utilizando o programa exemplos/pixels.cpp como referência,implementamos um programa regios.cpp o qual solicita ao usuário as cordenadas de 2 pontos da maneira mostrada na figura. Os mesmos localizados dentro dos limites do tamanho da imagem. Após isso, a região definida pelo retângulo de vértices opostos definidos pelos pontos será exibida com o negativo da imagem na região correspondente. O efeito é ilustrado na Figura Abaixo. 

[![exe2](https://raw.githubusercontent.com/mcarujo/mcarujo.github.io/master/exercicios/2/entrada_regions.png)](https://github.com/mcarujo/mcarujo.github.io/blob/master/exercicios/2/entrada_regions.png)

Após serem repassado os 2 pontos na entrada, temos uma saída como:

[![exe2](https://raw.githubusercontent.com/mcarujo/mcarujo.github.io/master/exercicios/2/sainda_regions.png)](https://github.com/mcarujo/mcarujo.github.io/blob/master/exercicios/2/sainda_regions.png)

#### Também seguindo o programa exemplos/pixels.cpp como referência, implementamos um programa trocaregioes.cpp, o qual divide a imagem em 4 quadrantes e troca eles de posições.

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

Essa foi a imagem capturada para ser utilizada como teste da nossa implementação, sendo aqui apresentada a imagem original sem nenhum filtro: 

[![exe2](https://github.com/mcarujo/mcarujo.github.io/blob/master/exercicios/5/original.png)](https://github.com/mcarujo/mcarujo.github.io/blob/master/exercicios/5/original.png)

A imagem capturada apenas com o filtro do laplaciano:

[![exe2](https://github.com/mcarujo/mcarujo.github.io/blob/master/exercicios/5/la1.png)](https://github.com/mcarujo/mcarujo.github.io/blob/master/exercicios/5/la1.png)

E a imagem capturada com o filtro do laplaciano do gaussiano:

[![exe2](https://github.com/mcarujo/mcarujo.github.io/blob/master/exercicios/5/lg1.png)](https://github.com/mcarujo/mcarujo.github.io/blob/master/exercicios/5/lg1.png)

Como podemos observar, com o filtro do laplaciano do gaussiano podemos obter uma imagem com as bordas mais ressaltadas, porém com um pouco mais de ruído quando comparado com resultado obtido apenas com a aplicação do filtro laplaciano.

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

## Exercícios 6.1
#### Utilizando o programa exemplos/addweighted.cpp como referência, implementamos um programa tiltshift.cpp. Com três ajustes que são providos na tela da interface:

* um ajuste para regular a altura da região central que entrará em foco;

* um ajuste para regular a força de decaimento da região borrada;

* um ajuste para regular a posição vertical do centro da região que entrará em foco. Finalizado o programa, a imagem produzida deverá ser salva em arquivo.
 
 XXXX
 
## Exercícios 6.2
#### Utilizando o programa exemplos/addweighted.cpp como referência, implementamos um programa tiltshiftvideo.cpp. O qual é capaz de processar um arquivo de vídeo, produzir o efeito de tilt-shift nos quadros presentes e escrever o resultado em outro arquivo de vídeo.


 XXXX
