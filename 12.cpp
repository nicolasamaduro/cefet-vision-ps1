#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<iostream>

using namespace cv;
int main (int argv, char** args){
	Mat img = imread(argv[1]);
	Mat hist(256,3,CV_8UC1,Scalar(0));
	for(unsigned int i =0;i<img.rows;i++){
		for(unsigned int j=0;j<img.cols;j++){
			Vec3b pixel = img.at<Vec3b>(i,j);
			hist.at<unsigned int>(pixel[0],0)++;
			hist.at<unsigned int>(pixel[1],1)++;
			hist.at<unsigned int>(pixel[2],2)++;
		}
	}
	std::cout<<hist<<std::endl;
	return 0;
}
