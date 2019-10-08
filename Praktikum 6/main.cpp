//Percobaan 1 Dilasi
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

using namespace cv;
using namespace std;

//Percobaan 1 Dilasi
/* 
int main()
{
	Mat source, destination;
	source = imread("../data/OrangeCat.jpg", CV_LOAD_IMAGE_COLOR);

	// Create a structuring element
	int dilation_size = 3;	// Ukuran operator dilasi 
	Mat element = getStructuringElement(cv::MORPH_CROSS,
		cv::Size(2 * dilation_size + 1, 2 * dilation_size +1),
		cv::Point(dilation_size, dilation_size) );

		// Apply dilation on the image 
	dilate(source,destination,element);

	namedWindow("Display window", CV_WINDOW_AUTOSIZE); 
	imshow("Display window", source);

	namedWindow("Result window", CV_WINDOW_AUTOSIZE); 
	imshow("Result window", destination);

	waitKey(0); 
	return 0;
}
*/
//Percobaan 2 Erosi
/*
int main()
{
	Mat source, destination;
	source = imread("../data/OrangeCat.jpg", CV_LOAD_IMAGE_COLOR);

	// Create a structuring element
	int erosion_size = 3;	// Ukuran operator erosi 
	Mat element = getStructuringElement(cv::MORPH_CROSS,
	cv::Size(2 * erosion_size + 1, 2 * erosion_size + 1), 
		cv::Point(erosion_size, erosion_size) );

	// Apply erosion on the image 
	erode(source,destination,element);

	namedWindow("Display window", CV_WINDOW_AUTOSIZE); 
	imshow("Display window", source);

	namedWindow("Result window", CV_WINDOW_AUTOSIZE); 
	imshow("Result window", destination);

	waitKey(0);
	return 0;
}
*/
//Percobaan 3 Distance transform

int main()
{
	// Load the image
	Mat src = imread("../data/cat.jpg", 1);
	// Check if everything was fine 
	if (!src.data)
		return -1;

	// Show source image 
	imshow("Source Image", src);

	// Change the background from white to black, since that will help later to extract
	// Create binary image from source image 
	Mat bw;
	cvtColor(src, bw, CV_BGR2GRAY);
	threshold(bw, bw, 40, 255, CV_THRESH_BINARY | CV_THRESH_OTSU); 
	imshow("Binary Image", bw);

	// Perform the distance transform algorithm
	Mat dist;
	distanceTransform(bw, dist, CV_DIST_L2, 3);

	// Normalize the distance image for range = {0.0, 1.0}
	// so we can visualize and threshold it 
	normalize(dist, dist, 0, 1., NORM_MINMAX);
	imshow("Distance Transform Image", dist);

	waitKey(100000);
	return 0;
}
