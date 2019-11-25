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

//Percobaan 1
/* 
int main()
{
	Mat src, dst;
	/// Load image
	src = imread("../data/OrangeCat.jpg", 1);
	if (!src.data)
	{
		return -1;
	}
	/// Separate the image in 3 places ( B, G and R )
	vector<Mat> bgr_planes;
	split(src, bgr_planes);

	/// Establish the number of bins
	int histSize = 16;

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

	/// Display
	namedWindow("calcHist Demo", CV_WINDOW_AUTOSIZE);
	imshow("calcHist Demo", histImage);
	waitKey(0);
	return 0;
}

*/

//Percobaan 2
/* 
extern "C"
{
	void extractCM();
	vector<double> getCM(IplImage* hsv);
	double getSkewness(IplImage* img, CvScalar mean, CvScalar std);
}

extern "C" {

	// 81-dimensions color moments features extraction
	// 1. divide a image into 9 same rectangle blocks
	// 2. each block contains 9-dimensions color moments features
	// 3. 9-dim CM features: mean of hsv, std of hsv, skewness of hsv
	// 4. each feature need normalization

	//void extractCM()
	int main(int argc, char** argv)
	{
		int block = 9;

		// load image
		IplImage* image = cvLoadImage("../data/OrangeCat.jpg");

		// rgb to hsv
		IplImage* hsv = cvCreateImage(cvGetSize(image), image->depth,3);
		cvCvtColor(image, hsv, CV_BGR2HSV);

		vector<double> CM; // 81-dimensions vector 
		int height = hsv->height;
		int width = hsv->width;
		int block_height = height / block; 
		int block_width = width / block;
		for (int row = 0; row < block; row++)
		{
			for (int col = 0; col < block; col++)
			{
				// image division
				CvRect rect = cvRect(col*block_width,
					row*block_height, block_width,
					block_height); // coordinate of	image block
				CvMat *mat = cvCreateMatHeader(block_height, block_width, CV_8UC1); // ceate mat header
				CvMat *hsvMat = cvGetSubRect(hsv, mat, rect); // save image block into matrix
				IplImage hsvSubImg;
				cvGetImage(hsvMat, &hsvSubImg); // get subimage from mat
					getCM(&hsvSubImg);

				cvReleaseMat(&mat);
			}
		}

		// release 
		cvReleaseImage(&image); 
		cvReleaseImage(&hsv);

		return 0;
	}

	vector<double> getCM(IplImage* hsv)
	{
		int height = hsv->height; 
		int width = hsv->width; 
		int size = height*width;
		vector<double> CM; // 9-dimensions vector

		// split hsv into 3 channels - h, s, v
		IplImage* h = cvCreateImage(cvGetSize(hsv), 8, 1);
		IplImage* s = cvCreateImage(cvGetSize(hsv), 8, 1);
		IplImage* v = cvCreateImage(cvGetSize(hsv), 8, 1); 
		cvSplit(hsv, h, s, v, NULL);

		// mean and std, that is, first and secondary moment
		// std takes biased estimate
		// linear relation with mutiple
		CvScalar h_mean, h_std, s_mean, s_std, v_mean, v_std; 
		cvAvgSdv(h, &h_mean, &h_std);
		cvAvgSdv(s, &s_mean, &s_std); 
		cvAvgSdv(v, &v_mean, &v_std);

		CM.push_back(h_mean.val[0] / 180.0);
		CM.push_back(s_mean.val[0] / 255.0); 
		CM.push_back(v_mean.val[0] / 255.0 / 255.0); 
		CM.push_back(h_std.val[0] / 180.0); 
		CM.push_back(s_std.val[0] / 255.0);
		CM.push_back(v_std.val[0] / 255.0 / 255.0);

		// skewness, third central moment
		// treat NaN and Inf as missing values, remove them
		// no linear relation with mutiple 
		double h_skew, s_skew, v_skew;
		h_skew = getSkewness(h, h_mean, h_std);
		s_skew = getSkewness(s, s_mean, s_std); v_skew = getSkewness(v, v_mean, v_std);

		CM.push_back(h_skew); 
		CM.push_back(s_skew); 
		CM.push_back(v_skew); 
		vector<double>::iterator iter;
		for (iter = CM.begin(); iter != CM.end(); iter++) 
			cout << *iter << endl;

		// release 
		cvReleaseImage(&h); 
		cvReleaseImage(&s); 
		cvReleaseImage(&v);

		return CM;
	}

	double getSkewness(IplImage* img, CvScalar mean, CvScalar std)
	{
		double skew; double sum = 0.0;
		int height = img->height; 
		int width = img->width; 
		int size = height*width;
		uchar* data = (uchar *)img->imageData; 
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
				sum += pow(data[i*width + j] - mean.val[0], 3.0); skew = sum / size / pow(std.val[0], 3);

		return skew;
	}
}
*/

//Image Moment
/* 
Mat src; Mat src_gray;
int thresh = 100;
int max_thresh = 255;
RNG rng(12345);

/// Function header
void thresh_callback(int, void*);

// @function main 
int main(int argc, char** argv)
{
	/// Load source image and convert it to gray
	src = imread("../data/OrangeCat.jpg", 1);

	/// Convert image to gray and blur it
	cvtColor(src, src_gray, CV_BGR2GRAY);
	blur(src_gray, src_gray, Size(3, 3));

	/// Create Window
	char* source_window = "Source";
	namedWindow(source_window, CV_WINDOW_AUTOSIZE);
	imshow(source_window, src);

	createTrackbar(" Canny thresh:", "Source", &thresh, max_thresh, thresh_callback);
	thresh_callback(0, 0);

	waitKey(0);
	return(0);
}

//@function thresh_callback 
void thresh_callback(int, void*)
{
	Mat canny_output;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	/// Detect edges using canny
	Canny(src_gray, canny_output, thresh, thresh * 2, 3);
	/// Find contours
	findContours(canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

	/// Get the moments
	vector<Moments> mu(contours.size());
	for (int i = 0; i < contours.size(); i++)
	{
		mu[i] = moments(contours[i], false);
	}

	///  Get the mass centers:
	vector<Point2f> mc(contours.size());
	for (int i = 0; i < contours.size(); i++)
	{
		mc[i] = Point2f(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);
	}

	/// Draw contours
	Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
	for (int i = 0; i< contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());
		circle(drawing, mc[i], 4, color, -1, 8, 0);
	}

	/// Show in a window
	namedWindow("Contours", CV_WINDOW_AUTOSIZE);
	imshow("Contours", drawing);

	/// Calculate the area with the moments 00 and compare with the result of the OpenCV function
	printf("\t Info: Area and Contour Length \n");
	for (int i = 0; i< contours.size(); i++)
	{
		printf(" * Contour[%d] - Area (M_00) = %.2f - Area OpenCV: %.2f - Length: %.2f \n", i, mu[i].m00, contourArea(contours[i]), arcLength(contours[i], true));
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());
		circle(drawing, mc[i], 4, color, -1, 8, 0);
	}
}
*/

//Percobaan 3 Fourier

int main(int argc, char** argv)
{
	Mat img;
	Mat input(cv::Size(200, 150), CV_8UC1); 
	Mat inputf(cv::Size(200, 150), CV_32FC1); 
	int i, j, k, l;
	float temp_re, temp_im, re, im; 
	float pi = 3.1427;
	img = imread("../data/OrangeCat.jpg", 0);
	if (!img.data)
	{
		return -1;
	}

	resize(img, input, input.size(), 0, 0, 1); 
	input.convertTo(inputf, CV_32FC1, 1, 0);
	Mat output(input.size().width, input.size().height, CV_32FC1); 
	imshow("Input Image", input);
	// Fourier sumbu x 
	for(i=0;i<input.size().height;i++)
	{
		for (j = 0;j<input.size().width;j++)
		{
			temp_re = 0; temp_im = 0;
			for (k = 0;k<input.size().height;k++)
			{
				for (l = 0;l<input.size().width;l++)
				{

					re = inputf.at<float>(l, k)*cos(2 * pi*(((float)i*(float)k / (float)input.size().width) + ((float)j*(float)l / (float)input.size().height)));
					temp_re += re;

					im = inputf.at<float>(l, k)*sin(2 * pi*(((float)i*(float)k / (float)input.size().width) + ((float)j*(float)l / (float)input.size().height)));
					temp_im += im;
				}
			}

			output.at<float>(j, i) = 5 * (1.f / (float)sqrt((float)input.size().width*(float)input.size().height))*log(sqrt(pow((float)temp_re, 2) + pow((float)temp_im, 2)) + 1);
			printf("%.2f\t", output.at<float>(j, i));
		}
		printf("\n");
	}

	imshow("Output Image", output); 
	imwrite("fourier.bmp", output); 
	waitKey(50000);
	return 0;
}
