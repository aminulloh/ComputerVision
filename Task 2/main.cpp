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

int main(int argc, char** argv)
{
	double alpha = 0.5;
	double beta;
	double input;
	Mat src1, src2, dst;
	/// Ask the user enter alpha
	cout << " Simple Linear Blender " << endl;
	cout << "-----------------------" << endl;
	cout << "* Enter alpha [0-1]: ";
	cin >> input;

	/// We use the alpha provided by the user if it is between 0 and 1 
	if (input >= 0.0 && input <= 1.0)
	{
		alpha = input;
	}

	/// Read image ( same size, same type ) 
	src1 = imread("GrayCat.jpg");
	src2 = imread("OrangeCat.jpg");

	if (!src1.data) { printf("Error loading src1 \n"); return -1; }
	if (!src2.data) { printf("Error loading src2 \n"); return -1; }

	/// Create Windows 
	namedWindow("Linear Blend", 1);

	beta = (1.0 - alpha);
	addWeighted(src1, alpha, src2, beta, 0.0, dst);
	imshow("Linear Blend", dst);
	waitKey(0);
	return 0;
}
	

