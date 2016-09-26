#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <cmath>
#include <iostream>
#include <string>
#include <cstdlib>

using namespace cv;
using namespace std;

float angleBetween(Point &v1, Point &v2)
{
    float dot = v1.x * v2.x + v1.y * v2.y;
    float a = dot / (norm(v1) * norm(v2));

    if (a >= 1.0)
        return 0.0;
    else if (a <= -1.0)
        return M_PI;
    else
        return acos(a); 
}

float complementAngleBetween(Point &v1,Point &v2){
	return 2*M_PI-angleBetween(v1,v2);
}

int main(int argc, char ** argv){
	const int size=101;
	const int halfSize=(size-1)/2;
	const int u=atoi(argv[1]);
	Mat image(size,size,CV_32FC3,Scalar(0,0,0));
 	Mat image2(size,size,CV_32FC1,Scalar(0));
 	cout << cos(M_PI)<<endl;
 	for (unsigned int i=0;i<size;i++){
		for (unsigned int j=0;j<size;j++){
			Point pt1(i-halfSize,(j-halfSize)*-1), pt2(0,-1);
			float hue = complementAngleBetween(pt1,pt2);
			float normPt1=norm(pt1);
			float saturation=normPt1/50.0;
			image2.at<float>(i,j)=255.0*saturation;
			float intensity = u/255.0;
			float r=.0,g=.0,b=.0;
			if(intensity>1.0)
				intensity=1.0;
			if (saturation >1.0){
				saturation=1.0;
				image2.at<float>(i,j)=.0;
			}	
			if(saturation==0){
				r=u;
				g=u;
				b=u;
			}else{ 
				if (hue<(2.0*M_PI)/3.0){
					b=(1.0-saturation)/3.0;
					r=(1.0+(saturation*cos(hue)/cos(M_PI/3.0-hue)))/3.0;
					g=1.0-r-b;
				
				}else if(hue<4.0*M_PI/3.0){
					hue=hue-(2.0*M_PI)/3.0;
					r=(1.0-saturation)/3.0;
					g=(1.0+saturation*cos(hue)/cos(M_PI/3-hue))/3;
					b=1.0-r-g;
				}else{
					hue=hue-(4.0*M_PI)/3.0;
					g=(1.0-saturation)/3.0;
					b=(1.0+(saturation*cos(hue)/cos(M_PI/3.0-hue)))/3.0;
					r=1.0-b-g;
				}
				r = intensity*r*3.0*255.0;
				g = intensity*g*3.0*255.0;
				b = intensity*b*3.0*255.0;
				if (r > 255.0)
					r=255.0;
				if (g > 255.0)
					g=255.0;
				if (b > 255.0)
					b=255.0;				
			}
			Vec3b v(b,g,r);
			image.at<Vec3b>(i,j)=v;
		}
	}
	imshow("HSI",image);
	imshow("Saturation",image2);
	waitKey();
}
