#include <iostream>
#include <opencv2/opencv.hpp>

struct Ponto {
	int x;
	int y;
};

int main(int argc, char** argv) {
	
	if(argc != 2) {
		std::cout << "Agumento inválido\n";
		std::cout << "Execute: ./nome_programa nome_imagem.png\n";
		return -1;
	}

	Ponto ponto1, ponto2;
	cv::Mat image;
	cv::Size size;
	
	image = cv::imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	
	size = image.size();
	
	{
		std::cout << "Para negativar a região, entre com P1 e P2\n";
		std::cout << "Sua imagem tem as seguintes dimenções:\n";
		std::cout << "height = " << size.height << \
					 " width = " << size.width << std::endl;
	
		std::cout << "Entre com o x de P1: ";
		std::cin >> ponto1.x;
		std::cout << "Entre com o y de P1: ";
		std::cin >> ponto1.y;
	
		std::cout << "Entre com o x de P2: ";
		std::cin >> ponto2.x;
		std::cout << "Entre com o y de P2: ";
		std::cin >> ponto2.y;		
	}
	
	for(int x=ponto1.x; x<=ponto2.x; x++) {
		for(int y=ponto1.y; y<=ponto2.y; y++) {
			image.at<uchar>(x,y)= 255 - image.at<uchar>(x,y);
		}
	}
	
	cv::imshow("image", image);
	cv::waitKey();
  
  return 0;
}
