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
#include<opencv2\videoio.hpp>


//Praktikum 1

using namespace std;
using namespace cv;

//Praktikum 1
/*
void main()
{
Mat img;
img = imread("cat.jpg", 0);
namedWindow("DISPLAY");
imshow("DISPLAY", img);
waitKey(10000);
}
*/

int main()
{
	Mat img;
	img = imread("cat1.jpg", 1);
	//Mat img = Mat::zeros(60, 60, CV_8UC3);
	//resize(img,img, Size(80,60));
	rectangle(img, Rect(10, 10, 100, 100), Scalar(255, 0, 0), 2, 4, 0);

	namedWindow("DISPLAY");
	imshow("DISPLAY", img);
	waitKey(10000);
}