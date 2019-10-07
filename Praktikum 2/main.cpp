//Percobaan 1 Smoothing
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

using namespace cv;

void main()
{
	Mat img;
	Mat blur;
	img = imread("../data/OrangeCat.jpg", 1); //anda gunakan, angka “1” menunjukkan bahwa gambar tersebut adalah berwarna
	cv::blur(img, blur, Size(3, 3), Point(-1, -1), 4);

	imshow("ORIGINAL", img); 
	imshow("BLURRING", blur);
	imwrite("blurred.bmp", blur); 
	waitKey(1);
}

//Percobaan 2 Sharpening
/* 
void main()
{
	Mat img; Mat sharp;

	img = imread("blurred.bmp", 1);
	GaussianBlur(img, sharp, Size(1, 1), 0, 0);
	addWeighted(img, 1.5, sharp, -0.5, 0, sharp);

	imshow("ORIGINAL", img);
	imshow("SHARP", sharp);

	waitKey(1);
}

//Percobaan 3 Edge
void main()
{
	Mat img;
	Mat edge;

	img = imread("img.bmp", 1);
	Sobel(img, edge, 3, 1, 1, 3, 1.0, 0.0, 4);

	imshow("ORIGINAL", img);
	imshow("EDGE", edge);

	waitKey(1);
}

*/
