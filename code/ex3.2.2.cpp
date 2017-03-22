#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char** argv) {

	if(argc != 2) {
		std::cout << "Agumento inválido\n";
		std::cout << "Execute: ./nome_programa nome_imagem.png\n";
		return -1;
	}

	cv::Mat image;
	cv::Mat newImage;
	cv::Size size;

	int newHeight, newWidth;

	image = cv::imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);

	image.copyTo(newImage);

	size = image.size();

	newHeight = size.height/2;
	newWidth = size.width/2;

	cv::Mat block1 = image( cv::Rect(0, 0, newHeight, newWidth) );
	cv::Mat block2 = image( cv::Rect(newHeight, 0, newHeight, newWidth) );
	cv::Mat block3 = image( cv::Rect(0, newWidth, newHeight, newWidth) );
	cv::Mat block4 = image( cv::Rect(newHeight, newWidth, newHeight, newWidth) );

	block4.copyTo( newImage( cv::Rect(0, 0, newHeight, newWidth) ) ); // 1
	block3.copyTo( newImage( cv::Rect(newHeight, 0, newHeight, newWidth) ) ); // 2
	block2.copyTo( newImage( cv::Rect(0, newWidth, newHeight, newWidth) ) ); // 3
	block1.copyTo( newImage( cv::Rect(newHeight, newWidth, newHeight, newWidth) ) ); // 4

	cv::imshow("image", newImage);
	cv::waitKey();

	return 0;
}
