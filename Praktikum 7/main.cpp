#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<iostream>

#include<opencv2\opencv.hpp>
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<opencv2\ml\ml.hpp>
#include<opencv2\objdetect\objdetect.hpp>

using namespace std;
using namespace cv;

//Praktikum 1 Brightness and Contrast
int main() {
	cv::Mat I = cv::imread("../data/OrangeCat.jpg", CV_LOAD_IMAGE_GRAYSCALE);

	if (I.empty())
		return -1;

	cv::Mat padded;	//expand input image to optimal size
	int m = cv::getOptimalDFTSize(I.rows);
	int n = cv::getOptimalDFTSize(I.cols); // on the border add zero values
	cv::copyMakeBorder(I, padded, 0, m - I.rows, 0, n - I.cols, 1/*BORDER_CONSTANT*/, cv::Scalar::all(0));

	cv::Mat	planes[] = { cv::Mat_<float>(padded), cv::Mat::zeros(padded.size(), CV_32F) };
	cv::Mat complexI;
	merge(planes, 2, complexI);	// Add to the expanded another plane with zeros

	dft(complexI, complexI);	// this way the result may fit in the source matrix

								// compute the magnitude and switch to logarithmic scale
								// => log(1 + sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))
	split(complexI, planes);	// planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
	magnitude(planes[0], planes[1], planes[0]);//	planes[0]	= magnitude
	cv::Mat magI = planes[0];

	magI += cv::Scalar::all(1);	// switch to logarithmic scale
	log(magI, magI);

	// crop the spectrum, if it has an odd number of rows or columns 
	magI = magI(cv::Rect(0, 0, magI.cols & -2, magI.rows & -2));

	// rearrange the quadrants of Fourier image so that the origin is at the image center
	int cx = magI.cols / 2; 
	int cy = magI.rows / 2;

	cv::Mat q0(magI, cv::Rect(0, 0, cx, cy));	// Top-Left - Create a ROI per quadrant
	cv::Mat q1(magI, cv::Rect(cx, 0, cx, cy));	// Top-Right 
	cv::Mat q2(magI, cv::Rect(0, cy, cx, cy));	// Bottom-Left
	cv::Mat q3(magI, cv::Rect(cx, cy, cx, cy)); // Bottom-Right
	
	cv::Mat tmp;		// swap quadrants (Top-Left with Bottom-Right)
	q0.copyTo(tmp); 
	q3.copyTo(q0); 
	tmp.copyTo(q3);

	q1.copyTo(tmp);		// swap quadrant (top-right with Bottom-left)
	q2.copyTo(q1);
	tmp.copyTo(q2);

	normalize(magI, magI, 0, 1, CV_MINMAX);
	imshow("Input Image", I);
	imshow("spectrum magnitude", magI);
	imshow("Quadrant 4", q3);
	waitKey();

	return 0;
}

