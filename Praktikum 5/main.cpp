//Percobaan 1 Smoothing
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

using namespace cv;

//Percobaan 1 Smoothing
/* 
void main()
{
	Mat img;
	Mat blur;
	img = imread("../data/OrangeCat.jpg", 1); //anda gunakan, angka “1” menunjukkan bahwa gambar tersebut adalah berwarna
	cv::blur(img, blur, Size(3, 3), Point(-1, -1), 4);

	imshow("ORIGINAL", img); 
	imshow("BLURRING", blur);
	imwrite("blurred.jpg", blur); 
	waitKey(100000);
}
*/

//Percobaan 2 Sharpening
/* 
void main()
{
	Mat img; Mat sharp;

	img = imread("../data/cat.jpg", 1);
	GaussianBlur(img, sharp, Size(1, 1), 0, 0);
	addWeighted(img, 1.5, sharp, -0.5, 0, sharp);

	imshow("ORIGINAL", img);
	imshow("SHARP", sharp);

	waitKey(100000);
}
*/

//Percobaan 3 Edge
void main()
{
	Mat img;
	Mat edge, edge_abs;

	img = imread("../data/Lenna.jpg", 0);
	imshow("ORIGINAL", img);

	Mat output1(img.size().width, img.size().height,CV_8UC1);
	Mat output2(img.size().width, img.size().height, CV_8UC1);
	Mat grading(img.size().width, img.size().height, CV_8UC1);

	Mat abs_grad_x;
	Mat abs_grad_y;

	//Sobel(img, output1, CV_16S, 1, 0, 3, 1.0, 0.0, 4);
	//Sobel(img, output2, CV_16S, 0, 1, 3, 1.0, 0.0, 4);

	//Sobel(img, output1, CV_16S, 3, 0, 7, 1.0, 0.0, 4);
	//Sobel(img, output2, CV_16S, 0, 3, 7, 1.0, 0.0, 4);

	Sobel(img, output1, CV_16S, 5, 0, 11, 1.0, 0.0, 4);
	Sobel(img, output2, CV_16S, 0, 5, 11, 1.0, 0.0, 4);
	
	convertScaleAbs(output1,abs_grad_x);
	convertScaleAbs(output2, abs_grad_y);

	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5,0,grading);

	imshow("edge1",output1);
	imshow("edge2", output2);
	imshow("Grad", grading);

	waitKey(0);
}


/* 
void main()
{
	Mat img;
	Mat edge, edge_abs;

	img = imread("../data/Lenna.jpg", 0);
	imshow("ORIGINAL", img);


	Sobel(img, edge, CV_16S, 1, 1, 3, 1.0, 0.0, 4);
	//Sobel(img, edge, 3, 2, 2, 5, 1.0, 0.0, 4);
	//Sobel(img, edge, 3, 3, 3, 7, 1.0, 0.0, 4);
	//Sobel(img, edge, 5, 5, 5, 11, 1.0, 0.0, 4);

	convertScaleAbs(edge,edge_abs);

	imshow("ORIGINAL", img);
	imshow("EDGE", edge_abs);

	waitKey(0);
}
*/
//Tugas 3.1 
/* 
void main()
{
	Mat img;
	Mat edge;

	img = imread("../data/OrangeCat.jpg", 0);
	//Sobel(img, edge, 3, 2, 2, 5, 1.0, 0.0, 4);
	//Sobel(img, edge, 3, 1, 1, 3, 1.0, 0.0, 4);  // 1
	//Sobel(img, edge, 3, 3, 3, 7, 1.0, 0.0, 4);  // 2
	Sobel(img, edge, 5, 5, 5, 11, 1.0, 0.0, 4);  // 3

	imshow("ORIGINAL", img);
	imshow("EDGE", edge);

	waitKey(0);
}
*/

// Percobaan
/** @function main */
/* 
int main()
{

	Mat src, src_gray;
	Mat grad;
	//char* window_name = "Sobel Demo - Simple Edge Detector";
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;

	int c;

	/// Load an image
	src = imread("../data/OrangeCat.jpg", 0);

	if (!src.data)
	{
		return -1;
	}

	GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);

	/// Convert it to gray
	cvtColor(src, src_gray, CV_BGR2GRAY);

	/// Create window
	//namedWindow("bismillah", CV_WINDOW_AUTOSIZE);

	/// Generate grad_x and grad_y
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y;

	/// Gradient X
	//Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
	Sobel(src_gray, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(grad_x, abs_grad_x);

	/// Gradient Y
	//Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );
	Sobel(src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(grad_y, abs_grad_y);

	/// Total Gradient (approximate)
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);

	imshow("bismillah", grad);

	waitKey(0);

	return 0;
}
*/