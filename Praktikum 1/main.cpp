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



using namespace std;
using namespace cv;


Mat img; Mat templ, dst; Mat result; char* image_window = "Source Image";
char* result_window = "Result window";

int match_method;
int max_Trackbar = 5;

/// Function Headers
void MatchingMethod(int, void*);

int main() {
	/// Load image and template
	img = imread("1_800.png", 1);
	templ = imread("1a.png", 1);
	//cv::resize(img, img, cv::Size(512, 512));
	//cv::resize(templ, templ, cv::Size(512, 512));
	//cv::resize(templ, templ, cv::Size(254, 254));
	/// Create windows


	/// Create Trackbar
	char* trackbar_label = "Method: \n 0: SQDIFF \n 1: SQDIFF NORMED \n 2: TM CCORR \n 3: TM CCORR NORMED \n 4: TM COEFF \n 5: TM COEFF NORMED";


	//waitKey(0);
	while (true)
	{
		printf("input");
		char c = (char)waitKey(0);

		if ((char)c == 27)
		{
			break;
		}
		if ((char)c == 'u')
		{
			pyrUp(templ, templ, Size(templ.cols * 1.2, templ.rows * 1.2));
			//printf("** Zoom In: Image x 2 \n");
		}
		else if ((char)c == 'd')
		{
			pyrDown(templ, templ, Size(templ.cols / 1.2, templ.rows / 1.2));
			//printf("** Zoom Out: Image / 2 \n");
		}



		imshow("test", templ);
		createTrackbar(trackbar_label, image_window, &match_method, max_Trackbar, MatchingMethod);
		MatchingMethod(0, 0);
		templ = templ;
	}

	return 0;
}

void MatchingMethod(int, void*)
{
	Mat img_display; img.copyTo(img_display);

	/// Create the result matrix
	int result_cols = img.cols - templ.cols + 1; int result_rows = img.rows - templ.rows + 1;

	result.create(result_rows, result_cols, CV_32FC1);

	/// Do the Matching and Normalize
	matchTemplate(img, templ, result, match_method);
	normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());
	/// Localizing the best match with minMaxLoc
	double minVal; double maxVal;

	Point minLoc;
	Point maxLoc;
	Point matchLoc;

	minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());

	/// For SQDIFF and SQDIFF_NORMED, the best matches are lower values.for all the other methods, the higher the better

	if (match_method == CV_TM_SQDIFF || match_method == CV_TM_SQDIFF_NORMED)
	{
		matchLoc = minLoc;
	}
	else
	{
		matchLoc = maxLoc;
	}

	/// Show me what you got
	rectangle(img_display, matchLoc, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), Scalar::all(0), 2, 8, 0);
	rectangle(result, matchLoc, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), Scalar::all(0), 2, 8, 0);

	imshow(image_window, img_display);
	imshow("result_window", result);
	//imshow( "templ", templ );

	return;
}
