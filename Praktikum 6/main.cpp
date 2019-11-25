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
	Mat input, source, destination;
	source = imread("../data/morph.jpg", CV_LOAD_IMAGE_COLOR);
	input = imread("../data/morph.jpg", CV_LOAD_IMAGE_COLOR);

	// Create a structuring element
	int dilation_size = 3;	// Ukuran operator dilasi 
	Mat element = getStructuringElement(cv::MORPH_ELLIPSE,
		cv::Size(2 * dilation_size + 1, 2 * dilation_size +1),
		cv::Point(dilation_size, dilation_size) );

	
	// Apply dilation on the image 
	Mat temp;
	Mat temp1;
	temp = source;
	int N = 10;
	for (size_t i = 0; i < N; i++)
	{
		dilate(temp, temp1, element);
		temp1 = temp;
	}

	namedWindow("Source", CV_WINDOW_AUTOSIZE); 
	imshow("Source", input);

	namedWindow("Result", CV_WINDOW_AUTOSIZE); 
	imshow("Result", temp1);

	waitKey(0); 
	return 0;
}
*/

//Percobaan 2 Erosi
/* 
int main()
{
	Mat input, source, destination;
	source = imread("../data/morph.jpg", CV_LOAD_IMAGE_COLOR);
	input = imread("../data/morph.jpg", CV_LOAD_IMAGE_COLOR);

	// Create a structuring element
	int erosion_size = 3;	// Ukuran operator erosi 
	Mat element = getStructuringElement(cv::MORPH_ELLIPSE,
	cv::Size(2 * erosion_size + 1, 2 * erosion_size + 1), 
		cv::Point(erosion_size, erosion_size) );


	// Apply erosion on the image 
	Mat temp;
	Mat temp1;
	temp = source;
	int N = 10;
	for (size_t i = 0; i < N; i++)
	{
		erode(temp, temp1, element);
		temp1 = temp;
	}

	namedWindow("Source", CV_WINDOW_AUTOSIZE);
	imshow("Source", input);

	namedWindow("Result", CV_WINDOW_AUTOSIZE);
	imshow("Result", temp1);

	waitKey(0);
	return 0;
}
*/

//Percobaan 3 Opening and Closing
//Program Opening
 /* 
int main() {
	Mat source1, destination1, destination2;
	source1 = imread("../data/morph.jpg", CV_LOAD_IMAGE_COLOR);
	
	int sz = 3;
	// Create a structuring element
	int erosion_size = sz;	// Ukuran operator erosi 
	Mat element1 = getStructuringElement(cv::MORPH_ELLIPSE,
		cv::Size(2 * erosion_size + 1, 2 * erosion_size + 1),
		cv::Point(erosion_size, erosion_size));

	// Create a structuring element
	int dilation_size = sz;	// Ukuran operator dilasi 
	Mat element2 = getStructuringElement(cv::MORPH_ELLIPSE,
		cv::Size(2 * dilation_size + 1, 2 * dilation_size + 1),
		cv::Point(dilation_size, dilation_size));
	
	Mat temp;
	Mat temp1;
	Mat temp2;
	temp = source1;
	int N = 10;
	for (size_t i = 0; i < N; i++)
	{
		// Apply erosion on the image 
		erode(temp, temp1, element1);
		// Apply dilation on the image 
		dilate(temp1, temp2, element2);

		//dilate(temp, temp1, element);
		temp2 = temp;
	}
	// Apply erosion on the image 
	erode(source1, destination1, element1);
	// Apply dilation on the image 
	dilate(destination1, destination2, element2);

	namedWindow("Source", CV_WINDOW_AUTOSIZE);
	imshow("Source", source1);

	namedWindow("Erode", CV_WINDOW_AUTOSIZE);
	imshow("Erode", temp1);

	namedWindow("Dilate", CV_WINDOW_AUTOSIZE);
	imshow("Dilate", temp2);

	waitKey(0);
	return 0;
}
*/

//Program Clossing

int main() {
	Mat source1, destination1,destination2;
	source1 = imread("../data/morph.jpg", CV_LOAD_IMAGE_COLOR);
	int sz = 3;
	// Create a structuring element
	int dilation_size = sz;	// Ukuran operator dilasi 
	Mat element1 = getStructuringElement(cv::MORPH_ELLIPSE,
		cv::Size(2 * dilation_size + 1, 2 * dilation_size + 1),
		cv::Point(dilation_size, dilation_size));

	// Create a structuring element
	int erosion_size = sz;	// Ukuran operator erosi 
	Mat element2 = getStructuringElement(cv::MORPH_ELLIPSE,
		cv::Size(2 * erosion_size + 1, 2 * erosion_size + 1),
		cv::Point(erosion_size, erosion_size));

	Mat temp;
	Mat temp1;
	Mat temp2;
	temp = source1;
	int N = 10;
	for (size_t i = 0; i < N; i++)
	{
		// Apply dilation on the image 
		dilate(temp, temp1, element1);
		// Apply erosion on the image 
		erode(temp1, temp2, element2);

		//dilate(temp, temp1, element);
		temp2 = temp;
	}

	// Apply dilation on the image 
	dilate(source1, destination1, element1);
	// Apply erosion on the image 
	erode(destination1, destination2, element2);

	namedWindow("Source", CV_WINDOW_AUTOSIZE);
	imshow("Source", source1);

	namedWindow("Dilate", CV_WINDOW_AUTOSIZE);
	imshow("Dilate", temp1);

	namedWindow("Erode", CV_WINDOW_AUTOSIZE);
	imshow("Erode", temp2);

	waitKey(0);
	return 0;
}

//Percobaan 4 Distance transform
/* 
int main()
{
	// Load the image
	Mat src = imread("../data/morph.jpg", 1);
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
*/