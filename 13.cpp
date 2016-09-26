#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<iostream>
#include<string>
#include<cmath>

using namespace cv;
using namespace std;

float Mean(Mat mat){
	float sum=0.0;
	for(unsigned int i =0;i<mat.rows;i++){
		for(unsigned int j=0;j<mat.cols;j++){
			sum+=mat.at<float>(i,j); 
		}
	}
	return (sum/(mat.rows*mat.cols));
}

float Variance(Mat mat){
	float sum=0;
	for(unsigned int i =0;i<mat.rows;i++){
		for(unsigned int j=0;j<mat.cols;j++){
			sum+=mat.at<float>(i,j)*mat.at<float>(i,j); 
		}
	}	
	return sum/(mat.rows*mat.cols)-pow(Mean(mat),2);
}

float StDeviation(Mat mat){
	return sqrt(Variance(mat));
}

void CallBackFunc(int event, int x, int y, int flags, void* param)
{
	Mat* img=(Mat*) param;
	namedWindow("Zoom",	WINDOW_AUTOSIZE);
	
	if ( event == EVENT_MOUSEMOVE )
    {
		cout << "Mouse move over the window - position (" << x << ", " << y << ")"<<endl;
		cout << "RGB - ["<< (int)(*img).at<Vec3b>(x,y)[0]<<","<<(int)(*img).at<Vec3b>(x,y)[1]<<","<<(int)(*img).at<Vec3b>(x,y)[2]<<"]" << endl;
		cout << "Intensity - " << ((int)(*img).at<Vec3b>(x,y)[0]+(int)(*img).at<Vec3b>(x,y)[1]+(int)(*img).at<Vec3b>(x,y)[2])/3.0<<endl;
		Mat zoomImg(11,11,CV_8UC3,Scalar(0,0,0));
		Mat intensityZoomImg(11,11, CV_32F);
			unsigned int k,l;
			if (x>5&&	y>5&&x<(*img).cols-5&&y<(*img).rows-5){
			for(unsigned int i =x-5, k=0;i<x+5;k++,i++){
				for(unsigned int j=y-5, l=0;j<y+5;l++,j++){	
					zoomImg.at<Vec3b>(l,k)=(*img).at<Vec3b>(j,i);
					intensityZoomImg.at<float>(l,k)=((int)(*img).at<Vec3b>(j,i)[0]+(int)(*img).at<Vec3b>(j,i)[1]+(int)(*img).at<Vec3b>(j,i)[2])/3.0;
				}
			}
			cout <<"Mean - "<<Mean(intensityZoomImg)<<", Standard  deviation - " << StDeviation(intensityZoomImg) << endl;
			cout <<endl;
			imshow("Zoom",zoomImg);
		}
	}	
}

int main (int argv, char** args){
	Mat img = imread("files/lena.png");
	namedWindow("Auto",	WINDOW_AUTOSIZE);
	setMouseCallback("Auto", CallBackFunc, &img);
	imshow("Auto",img);
	waitKey(0);
	return 0;
}
