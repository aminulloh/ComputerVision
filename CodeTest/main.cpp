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

void mouseEvent(int evt, int x, int y, int flags, void* param)
{
	Mat* rgb = (Mat*)param;
	if (evt == CV_EVENT_LBUTTONDOWN)
	{
		printf("Nilai pixel pada koordinat (%d,%d): B=%f, G=%f, R=%f\n", x, y,
			(double)(*rgb).at<Vec3b>(y, x)[0],
			(double)(*rgb).at<Vec3b>(y, x)[1],
			(double)(*rgb).at<Vec3b>(y, x)[2]);
	}
}

int main()
{
	/// Read image given by user
	Mat image = imread("../Dataset/BN785_0.jpg"); // nama gambar silakan diganti sesuai gambar yang anda gunakan
	Mat new_image(image.size(), image.type(), CV_64FC3);

	/// Initialize values
	float Mp = 0.2, Ap = 0.1;

	/// Do the ToA operation new_image(i, j) = Mp*image(i, j) + Ap;
	for (int y = 0; y < image.rows; y++)
	{
		for (int x = 0; x < image.cols; x++)
		{
			for (int c = 0; c < 3; c++)
			{
				new_image.at<Vec3b>(y, x)[c] = saturate_cast<double>(Mp*(image.at<Vec3b>(y, x)[c]) + Ap);
			}
		}
	}
	
	/// Separate the image in 3 places ( B, G and R )
	vector<Mat> bgr_planes;
	split(image, bgr_planes);

	/// Establish the number of bins
	int histSize = 256;

	/// Set the ranges ( for B,G,R) )
	float range[] = { 0, 256 };
	const float* histRange = { range };

	bool uniform = true;
	bool accumulate = false;

	Mat b_hist, g_hist, r_hist;
	/// Compute the histograms:
	calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate);

	// Draw the histograms for B, G and R 
	int hist_w = 512;
	int hist_h = 400;
	int bin_w = cvRound((double)hist_w / histSize);

	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));

	/// Normalize the result to [ 0, histImage.rows ]
	normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	/// Draw for each channel 
	for (int i = 1; i < histSize; i++)
	{
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))), Point(bin_w*(i), hist_h - cvRound(b_hist.at<float>(i))),
			Scalar(255, 0, 0), 2, 8, 0);
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))), Point(bin_w*(i), hist_h - cvRound(g_hist.at<float>(i))),
			Scalar(0, 255, 0), 2, 8, 0);
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))), Point(bin_w*(i), hist_h - cvRound(r_hist.at<float>(i))),
			Scalar(0, 0, 255), 2, 8, 0);
	}

	/// Display Histogram
	namedWindow("Histogram", CV_WINDOW_AUTOSIZE);
	imshow("Histogram", histImage);

	/// Create Windows 
	namedWindow("Original Image", 1);
	namedWindow("ToA", 1);

	/// Show stuff

	imshow("Original Image", image);
	imshow("ToA", new_image);

	//Pixel Value
	setMouseCallback("ToA", mouseEvent, &new_image);

	Size sz1 = image.size();
	Size sz2 = histImage.size();

	Mat im3(sz1.height, sz1.width + sz2.width, CV_8UC3);
	Mat Left(im3, Rect(0, 0, sz1.width, sz1.height));
	new_image.copyTo(Left);
	Mat Right(im3, Rect(sz1.width, 0, sz2.width, sz2.height));
	histImage.copyTo(Right);
	

	// Display
	//namedWindow("Webcam", 1);
	//imshow("Webcam", im3);

	// Wait until user press some key 
	waitKey();
	return 0;
}

// Histogram Greyscale
/* 
void mouseEvent(int evt, int x, int y, int flags, void* param)
{
	Mat* grey = (Mat*)param;
	if (evt == CV_EVENT_LBUTTONDOWN)
	{
		printf("Nilai pixel pada koordinat (%d,%d): %0.3f\n", x, y,
			(float)(*grey).at<Vec3b>(y, x)[0]);
			//(int)(*rgb).at<Vec3b>(y, x)[0]);
	}
}

int main() {
	/// Load image
	Mat src1, src2;
	src1 = imread("../Dataset/BN785_0.jpg", CV_LOAD_IMAGE_COLOR);
	src2 = Mat::zeros(src1.rows, src1.cols, CV_8UC1);

	if (!src1.data) { printf("Error loading src1 \n"); return -1; }

	//Manual Greyscale Computation
	for (int i = 0; i<src1.cols; i++) {
		for (int j = 0; j<src1.rows; j++)
		{
			Vec3b color1 = src1.at<Vec3b>(Point(i, j));
			Scalar color2 = src2.at<uchar>(Point(i, j));
			color2 = (color1.val[0] + color1.val[1] +
				color1.val[2]) / 3;

			src2.at<uchar>(Point(i, j)) = color2.val[0];
		}
	}

	/// Initialize values
	Mat ToA;
	ToA = Mat::zeros(src2.rows, src2.cols, CV_8UC1);
	float Mp = 0.2, Ap = 0.1;

	/// Do the ToA operation new_image(i, j) = Mp*image(i, j) + Ap;
	for (int y = 0; y < src2.rows; y++)
	{
		for (int x = 0; x < src2.cols; x++)
		{
			ToA.at<Vec3b>(y, x)[0] = saturate_cast<uchar>(Mp*(src2.at<Vec3b>(y, x)[0]) + Ap);	
		}
	}

	/// Establish the number of bins
	int histSize = 256;

	/// Set the ranges ( for B,G,R) )
	float range[] = { 0, 256 };
	const float* histRange = { range };

	bool uniform = true;
	bool accumulate = false;

	Mat gray_hist;

	/// Compute the histograms:
	calcHist(&src2, 1, 0, Mat(), gray_hist, 1, &histSize, &histRange, uniform, accumulate);

	// Draw the histograms for B, G and R 
	int hist_w = 512;
	int hist_h = 400;
	int bin_w = cvRound((double)hist_w / histSize);

	Mat histImage(hist_h, hist_w, CV_16UC3, Scalar(0, 0, 0));

	/// Normalize the result to [ 0, histImage.rows ]
	normalize(gray_hist, gray_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	/// Draw for each channel 
	for (int i = 1; i < histSize; i++)
	{
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(gray_hist.at<float>(i - 1))), Point(bin_w*(i), hist_h - cvRound(gray_hist.at<float>(i))),
			Scalar(128, 128, 128), 2, 8, 0);
	}

	/// Display
	namedWindow("calcHist gray", CV_WINDOW_AUTOSIZE);
	imshow("calcHist gray", histImage);

	namedWindow("Image", CV_WINDOW_AUTOSIZE);
	imshow("Image", src2);

	setMouseCallback("Image", mouseEvent, &src2);

	waitKey(0);
	return 0;
}

*/

//Grayscale Input
/* 
int main() {

	Mat src, dst;
	/// Load image
	src = imread("../Dataset/Dimas/2.jpg", 1);
	if (!src.data)
	{
		return -1;
	}

	Mat gray_image;
	cvtColor(src, gray_image, CV_RGB2GRAY);

	/// Establish the number of bins
	int histSize = 256;

	/// Set the ranges ( for B,G,R) )
	float range[] = { 0, 256 };
	const float* histRange = { range };

	bool uniform = true;
	bool accumulate = false;

	Mat gray_hist;

	/// Compute the histograms:
	calcHist(&gray_image, 1, 0, Mat(), gray_hist, 1, &histSize, &histRange, uniform, accumulate);

	// Draw the histograms for B, G and R 
	int hist_w = 512;
	int hist_h = 400;
	int bin_w = cvRound((double)hist_w / histSize);

	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));

	/// Normalize the result to [ 0, histImage.rows ]
	normalize(gray_hist, gray_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	/// Draw for each channel 
	for (int i = 1; i < histSize; i++)
	{
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(gray_hist.at<float>(i - 1))), Point(bin_w*(i), hist_h - cvRound(gray_hist.at<float>(i))),
			Scalar(128, 128, 128), 2, 8, 0);
	}

	/// Display
	namedWindow("calcHist gray", CV_WINDOW_AUTOSIZE);
	imshow("calcHist gray", histImage);

	namedWindow("Image", CV_WINDOW_AUTOSIZE);
	imshow("Image", gray_image);

	waitKey();
	return 0;
}
*/