#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv){
	Mat image, mask;
	int width, height;
	int nobjects;
	int nBuracos;

	CvPoint p;
	image = imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);

	if(!image.data)
	{
		std::cout << "imagem nao carregou corretamente\n";
		return(-1);
	}

	width  = image.size().width;
	height = image.size().height;

	p.x = 0;
	p.y = 0;

	//-----Eliminar objetos nas bordas-----//
	for (int i = 0; i < width; i++)
	{
		image.at<uchar>(i, 0) 		= 255;
		image.at<uchar>(i, height-1)= 255;
	}
	for (int i = 0; i < height; i++)
	{
		image.at<uchar>(0, i) 		= 255;
		image.at<uchar>(width-1, i) = 255;
	}
	floodFill(image, p, 0);	
	//-------------------------------------//

	floodFill(image, p, 244); //Diferenciar o fundo

	//--------Contar Objetos e Buracos---------//
	nobjects = 0;
	nBuracos = 0;
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			p.x = j;
			p.y = i;
	  		if(image.at<uchar>(i,j) == 255)	
				floodFill(image, p, ++nobjects);

	  		if(image.at<uchar>(i,j) == 0)
	  			floodFill(image, p, 244 - (++nBuracos));
		}
	}
	//-----------------------------------------//

	std::cout << "Objetos: "<< nobjects << "  Buracos: " << nBuracos << std::endl;

	imshow("image", image);
	imwrite("labeling.png", image);
	waitKey();
	return 0;
}