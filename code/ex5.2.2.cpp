#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv){
    Mat image;
    int width, height;
    VideoCapture cap;
    vector<Mat> planes;
    Mat hist_new, hist_old;
    int nbins = 64;
    float range[] = {0, 256};
    const float *histrange = { range };
    bool uniform = true;
    bool acummulate = false;
    double limiar = 0.022;

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

    cap >> image;
    split (image, planes);
    calcHist(&planes[0], 1, 0, Mat(), hist_old, 1, &nbins, &histrange, uniform, acummulate);
    normalize(hist_old, hist_old, 0, 1, NORM_MINMAX, -1, Mat());

    while(true)
    {
        cap >> image;
        split (image, planes);
        calcHist(&planes[0], 1, 0, Mat(), hist_new, 1, &nbins, &histrange, uniform, acummulate);
        normalize(hist_new, hist_new, 0, 1, NORM_MINMAX, -1, Mat());

        double value = compareHist(hist_old, hist_new, CV_COMP_BHATTACHARYYA);

        cout << value;
        if (value > limiar)
            cout << " >> Alerta!! <<";
        cout << endl;

        hist_old = hist_new.clone();

        imshow("image", image);
        if(waitKey(30) >= 0) break;
    }
    return 0;
}