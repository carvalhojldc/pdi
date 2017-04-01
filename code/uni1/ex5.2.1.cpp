#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv){
    Mat image, image_pb;
    VideoCapture cap;
    vector<Mat> planes;
    int width, height;

    cap.open(0);

    if(!cap.isOpened())
    {
        cout << "cameras indisponiveis";
        return -1;
    }

    width  = cap.get(CV_CAP_PROP_FRAME_WIDTH);
    height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);

    cout << "largura = " << width << endl;
    cout << "altura  = " << height << endl;

    while(true)
    {
        cap >> image;
        split (image, planes);
        
        cvtColor(image, image, CV_BGR2GRAY);

        equalizeHist(image, image_pb);

        imshow("image", image);
        imshow("equalizada", image_pb);
        if(waitKey(30) >= 0) break;       
    }
    return 0;
}