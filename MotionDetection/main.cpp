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
 
int main() {
	VideoCapture cap(1);
	if (!cap.isOpened()) {
		cout << "Error opening video stream or file" << endl; return -1;
	}
	int n = 0, i = 0, nn = 0;
	int erosion_size = 1, d_size = 1;
	namedWindow("Control", CV_WINDOW_AUTOSIZE);
	cvCreateTrackbar("erosion_size", "Control", &erosion_size, 10);
	cvCreateTrackbar("dilate_size", "Control", &d_size, 10);
	cvCreateTrackbar("n_e", "Control", &n, 10);
	cvCreateTrackbar("n_d", "Control", &nn, 10);
	Mat hsv, finalmat; Mat result, result2, result3;
	double scaleSatUpper = 0.68;
	double scaleSatLower;
	//= 0.30;
	int intscaleSatLower = 5, intscaleSatUpper = 37;
	cvCreateTrackbar("scaleSatLower", "Control", &intscaleSatLower, 100);
	cvCreateTrackbar("scaleSatUpper", "Control", &intscaleSatUpper, 100);
	Mat element = getStructuringElement(cv::MORPH_ELLIPSE, Size(2 * erosion_size
		+ 1, 2 * erosion_size + 1), Point(erosion_size, erosion_size));
	Mat element2 = getStructuringElement(cv::MORPH_ELLIPSE, Size(2 * d_size + 1,
		2 * d_size + 1), Point(d_size, d_size));
	Mat frame;
	while (1) {
		cap >> frame;
		cvtColor(frame, hsv, CV_BGR2HSV);
		scaleSatLower = intscaleSatLower / 100.0;
		scaleSatLower = intscaleSatUpper / 100.0;
		Scalar lower = Scalar(0, scaleSatLower * 255, 0);
		Scalar upper = Scalar(25, scaleSatUpper * 255, 255);
		cv::inRange(hsv, lower, upper, result);
		//opening
		erode(result, result2, element, cv::Point(-1, -1), n);
		dilate(result2, result3, element2, cv::Point(-1, -1), nn);
		bitwise_and(frame, frame, finalmat, result3);
		imshow("Result", finalmat);
		finalmat.release();
		imshow("Original", frame);
		char c = (char)waitKey(25);
		if (c == 27) break;
	}
	cap.release();
	destroyAllWindows();
	return 0;
}


/* 
int main()
{
	int erosion_size = 5;
	Mat frame1, frame2;
	Mat grayImage1, grayImage2;
	Mat differnceImage;
	Mat thresholdImage;
	namedWindow("Webcam Video");
	//default webcam device id=0;
	//check if the webcam was opened properly
	Mat element = getStructuringElement(MORPH_RECT, Size(2 * erosion_size + 1, 2 *
		erosion_size + 1), Point(erosion_size, erosion_size));
	VideoCapture cap(1);
	while (1)
	{
		// cap.open(0);
		if (!cap.isOpened())
		{
			cout << "Webcam can't be opened" << endl;
			getchar();
			return -1;
		}
		cap.read(frame1);
		cvtColor(frame1, grayImage1, CV_RGB2GRAY);
		cap.read(frame2);
		cvtColor(frame2, grayImage2, CV_RGB2GRAY);
		absdiff(grayImage1, grayImage2, differnceImage);
		threshold(differnceImage, thresholdImage, 5, 255, CV_THRESH_BINARY);
		blur(thresholdImage, thresholdImage, Size(30, 30));
		threshold(differnceImage, thresholdImage, 5, 255, CV_THRESH_BINARY);
		erode(thresholdImage, thresholdImage, element, Point(-1, -1));
		imshow("Theshold", thresholdImage);
		imshow("Webcam Video", frame1);
		switch (waitKey(10))
		{
		case 27:
			return -1;
			break;
		}
	}
}
*/
