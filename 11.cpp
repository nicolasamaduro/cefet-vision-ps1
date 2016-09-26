#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>

using namespace cv;

int main (int argv, char** args){
	Mat img = imread("files/lena.png");
	namedWindow("Auto",	WINDOW_AUTOSIZE);
	imshow("Auto",img);
	waitKey(0);
	return 0;
}
