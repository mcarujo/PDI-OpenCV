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
    cout << "\nForam encontradas " << nobjects << " bolhas externas e " << inobjects << " bolhas externas \n";
    return 0;
}