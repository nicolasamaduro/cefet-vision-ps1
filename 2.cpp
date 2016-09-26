#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<iostream>
#include<string>
#include<cmath>

using namespace cv;
using namespace std;

float Mean(Mat mat){
	float sum=0;
	for(unsigned int i =0;i<mat.rows;i++){
		for(unsigned int j=0;j<mat.cols;j++){
			sum+=mat.at<float>(i,j); 
		}
	}
	return sum/(mat.rows*mat.cols);
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


int main (int argv, char** args){
	VideoCapture cap ("files/VIDEO.mp4");
	if(!cap.isOpened()){
		std::cout<<"Vídeo nao aberto"<<std::endl;
		return -1;
	}
	double framePeriod =1000*1.0/cap.get(CV_CAP_PROP_FPS);
	Mat frame;
	namedWindow("Video",WINDOW_NORMAL);
	cap>>frame;
	char key='a';
	int k=1;
	Mat intensity(frame.rows,frame.cols, CV_32F);
		
	while(!frame.empty()){
		for(unsigned int i =0;i<frame.rows;i++){
			for(unsigned int j=0;j<frame.cols;j++){	
				intensity.at<float>(i,j)=(frame.at<Vec3b>(i,j)[0]+frame.at<Vec3b>(i,j)[1]+frame.at<Vec3b>(i,j)[2])/3.0;
			}
		}
		cout<<"Mean("<<k<<") = "<<Mean(intensity)<<endl;
			
		cout<<"Variance("<<k<<") = "<<Variance(intensity)<<endl;
		
		cout<<"StDeviation("<<k<<") = "<<StDeviation(intensity)<<"\n"<<endl;
		k++;
		imshow("Video",frame);
		key=waitKey(framePeriod);
		if(k==3)
			break;
		cap>>frame;
	}
	cap.release();
}
