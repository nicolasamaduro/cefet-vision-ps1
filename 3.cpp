#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char ** argv)
{

    Mat I1 = imread("files/lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    Mat I2 = imread("files/arvore.png", CV_LOAD_IMAGE_GRAYSCALE);
    if( I1.empty()||I2.empty())
        return -1;
    Mat paddedI1,paddedI2;                            //expand input image to optimal size
    int m = getOptimalDFTSize( I1.rows );
    int n = getOptimalDFTSize( I1.cols ); // on the border add zero values
    copyMakeBorder(I1, paddedI1, 0, m - I1.rows, 0, n - I1.cols, BORDER_CONSTANT, Scalar::all(0));
    copyMakeBorder(I2, paddedI2, 0, m - I2.rows, 0, n - I2.cols, BORDER_CONSTANT, Scalar::all(0));

    Mat planesI1[] = {Mat_<float>(paddedI1), Mat::zeros(paddedI1.size(), CV_32F)};
    Mat planesI2[] = {Mat_<float>(paddedI2), Mat::zeros(paddedI2.size(), CV_32F)};
    Mat magI,phaI;
    Mat complexI1,complexI2;
    merge(planesI1, 2, complexI1);         // Add to the expanded another plane with zeros
	merge(planesI2, 2, complexI2);         

    dft(complexI1, complexI1);            // this way the result may fit in the source matrix
	dft(complexI2, complexI2);

    // compute the magnitude and switch to logarithmic scale
    // => log(1 + sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))
    split(complexI1, planesI1);
    split(complexI2, planesI2);
    
    magnitude(planesI1[0], planesI1[1], magI); 
    //magI=magI+(100);   
    phase(planesI2[0],planesI2[1],phaI);
    //phaI=phaI*.95;   
    
    Mat newPlane[2];
	polarToCart(magI, phaI, newPlane[0], newPlane[1]);
	
	Mat mixedComplexI,mixedI;
	
	merge(newPlane, 2, mixedComplexI);
	dft(mixedComplexI,mixedI , DFT_INVERSE|DFT_REAL_OUTPUT);
	normalize(mixedI, mixedI, 0, 1, CV_MINMAX);

	// Show the result
    imshow("Input Image 1"       , I1   ); 
    imshow("Input Image 2"       , I2   );    
    imshow("Mixed image", mixedI);

    waitKey();
    return 0;
}
