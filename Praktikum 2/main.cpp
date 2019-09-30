#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<Windows.h>
#include<iostream>

#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<opencv2\ml\ml.hpp>
#include<opencv2\objdetect\objdetect.hpp>
#include<opencv2\video\background_segm.hpp>
#include<opencv2\video\tracking.hpp>
#include<opencv2\imgcodecs.hpp>


using namespace cv;
using namespace std;

//Percobaan 1 Menggambar dan menulis
/* 
static void help()
{
	printf("\nThis program demonstrates OpenCV drawing and text output functions.\n" "Usage:\n" " ./drawing\n");
}
static Scalar randomColor(RNG& rng)
{
	int icolor = (unsigned)rng;
	return  Scalar(icolor & 255, (icolor >> 8) & 255, (icolor >> 16) & 255);
}

int main()
{
	help();
	char wndname[] = "Drawing Demo";
	const int NUMBER = 1;
	const int DELAY = 5;
	int lineType = LINE_AA; // change it to LINE_8 to see non-antialiased graphics 
	int i, width = 1000, height = 700;
	int x1 = -width / 2, x2 = width * 3 / 2, y1 = -height / 2, y2 = height * 3 / 2; 
	RNG rng(0xFFFFFFFF);

	Mat image = Mat::zeros(height, width, CV_8UC3); 
	imshow(wndname, image);
	waitKey(DELAY);
	/* 
	for (i = 0; i < NUMBER * 2; i++)
	{
		Point pt1, pt2;
		pt1.x = rng.uniform(x1, x2); pt1.y = rng.uniform(y1, y2); pt2.x = rng.uniform(x1, x2); pt2.y = rng.uniform(y1, y2);
		int arrowed = rng.uniform(0, 6); if (arrowed < 3)
			line(image, pt1, pt2, randomColor(rng), rng.uniform(1, 10), lineType);
		else
			arrowedLine(image, pt1, pt2, randomColor(rng), rng.uniform(1, 10), lineType);

		imshow(wndname, image); if (waitKey(DELAY) >= 0)
			return 0;
	}
	*/
	/* 
	for (i = 0; i < NUMBER * 2; i++)
	{
		Point pt1, pt2;
		pt1.x = rng.uniform(x1, x2); 
		pt1.y = rng.uniform(y1, y2); 
		pt2.x = rng.uniform(x1, x2); 
		pt2.y = rng.uniform(y1, y2);
		int thickness = rng.uniform(-3, 10); 
		int marker = rng.uniform(0, 10);
		int marker_size = rng.uniform(30, 80);

		if (marker > 5)
			rectangle(image, pt1, pt2, randomColor(rng), MAX(thickness, -1), lineType);
		else
			drawMarker(image, pt1, randomColor(rng), marker, marker_size);

		imshow(wndname, image); if (waitKey(DELAY) >= 0)
			return 0;
	}
	*/

	/* 
	for (i = 0; i < NUMBER; i++)
	{
		Point center;
		center.x = rng.uniform(x1, x2); center.y = rng.uniform(y1, y2); Size axes;
		axes.width = rng.uniform(0, 200); axes.height = rng.uniform(0, 200); double angle = rng.uniform(0, 180);

		ellipse(image, center, axes, angle, angle - 100, angle + 200, randomColor(rng), rng.uniform(-1, 9), lineType);

		imshow(wndname, image); if (waitKey(DELAY) >= 0)
			return 0;
	}
	*/
	/* 
	for (i = 0; i< NUMBER; i++)
	{
		Point pt[2][3];
		pt[0][0].x = rng.uniform(x1, x2);
		pt[0][0].y = rng.uniform(y1, y2);
		pt[0][1].x = rng.uniform(x1, x2);
		pt[0][1].y = rng.uniform(y1, y2);
		pt[0][2].x = rng.uniform(x1, x2);
		pt[0][2].y = rng.uniform(y1, y2);
		pt[1][0].x = rng.uniform(x1, x2);
		pt[1][0].y = rng.uniform(y1, y2);
		pt[1][1].x = rng.uniform(x1, x2);
		pt[1][1].y = rng.uniform(y1, y2);
		pt[1][2].x = rng.uniform(x1, x2);
		pt[1][2].y = rng.uniform(y1, y2);
		const Point* ppt[2] = { pt[0], pt[1] }; int npt[] = { 3, 3 };

		polylines(image, ppt, npt, 2, true, randomColor(rng), rng.uniform(1, 10), lineType);

		imshow(wndname, image);
		if (waitKey(DELAY) >= 0)
			return 0;
	}
	*/
	/* 
	for (i = 0; i< NUMBER; i++)
	{
		Point pt[2][3];
		pt[0][0].x = rng.uniform(x1, x2);
		pt[0][0].y = rng.uniform(y1, y2);
		pt[0][1].x = rng.uniform(x1, x2);
		pt[0][1].y = rng.uniform(y1, y2);
		pt[0][2].x = rng.uniform(x1, x2);
		pt[0][2].y = rng.uniform(y1, y2);
		pt[1][0].x = rng.uniform(x1, x2);
		pt[1][0].y = rng.uniform(y1, y2);
		pt[1][1].x = rng.uniform(x1, x2);
		pt[1][1].y = rng.uniform(y1, y2);
		pt[1][2].x = rng.uniform(x1, x2);
		pt[1][2].y = rng.uniform(y1, y2);
		const Point* ppt[2] = { pt[0], pt[1] }; int npt[] = { 3, 3 };
		fillPoly(image, ppt, npt, 2, randomColor(rng), lineType);

		imshow(wndname, image);
		if (waitKey(DELAY) >= 0)
			return 0;
	}
	*/

	/* 
	for (i = 0; i < NUMBER; i++)
	{
		Point center;
		center.x = rng.uniform(x1, x2); center.y = rng.uniform(y1, y2);

		circle(image, center, rng.uniform(0, 300), randomColor(rng),
			rng.uniform(-1, 9), lineType);

		imshow(wndname, image);
		if (waitKey(DELAY) >= 0)
			return 0;
	}
	*/

	/* 
	for (i = 1; i < NUMBER; i++)
	{
		Point org;
		org.x = rng.uniform(x1, x2); org.y = rng.uniform(y1, y2);
		putText(image, "Testing text rendering", org, rng.uniform(0, 8), rng.uniform(0, 100)*0.05 + 0.1, randomColor(rng), rng.uniform(1, 10), lineType);
		imshow(wndname, image);
		if (waitKey(DELAY) >= 0)
			return 0;
	}
	*/
	/*
	Size textsize = getTextSize("OpenCV forever!", FONT_HERSHEY_COMPLEX, 3, 5, 0);
	Point org((width - textsize.width) / 2, (height - textsize.height) / 2);

	Mat image2;
	for (i = 0; i < 255; i += 2)
	{
		image2 = image - Scalar::all(i);

		putText(image2, "OpenCV forever!", org, FONT_HERSHEY_COMPLEX, 3, Scalar(i, i, 255), 5, lineType);

		imshow(wndname, image2); if (waitKey(DELAY) >= 0)
			return 0;
	}
	

	waitKey();
	return 0;
}
*/
//Percobaan 2 Region of Interest
/* 
int main(int argc, const char** argv)
{
	// Load the image from file Mat LoadedImage;

	// Just loaded image Lenna.png from project dir to LoadedImage
	Mat LoadedImage = imread("OrangeCat.jpg", IMREAD_COLOR);

	// Show what is in the Mat after load
	namedWindow("Step 1 image loaded", WINDOW_AUTOSIZE);
	imshow("Step 1 image loaded", LoadedImage);

	waitKey(1000);
	// Save the result from LoadedImage to Step1.JPG
	imwrite("Step1.JPG", LoadedImage);

	// This construct Rectangle Rec start at x=100 y=100, width=200 and heigth=200
	Rect Rec(50, 100, 150, 150);

	//Draw the rectangle into LoadedImage
	//Parameters are (into Mat, Rec describe position where to draw rectangle
	// Scalar is Color, 1 is thickness, 8 is line type and 0 shift position
	rectangle(LoadedImage, Rec, Scalar(255), 1, 8, 0);

	// Show what rectangle
	namedWindow("Step 2 draw Rectangle", WINDOW_AUTOSIZE);
	imshow("Step 2 draw Rectangle", LoadedImage);
	waitKey(1000);

	// Save the result from LoadedImage to Step2.JPG
	imwrite("Step2.JPG", LoadedImage);

	//Select area described by REC and result write to the Roi
	Mat Roi = LoadedImage(Rec);
	namedWindow("Step 3 Draw selected Roi", WINDOW_AUTOSIZE);
	imshow("Step 3 Draw selected Roi", Roi);
	waitKey(1000);

	// Save the result from LoadedImage to Step3.JPG
	imwrite("Step3.JPG", Roi);
	// Put roi back into source image
	// If you want to show the detail and visualize with context of source image

	// This rectangle describe target, where you want to
	// put your roi into original image
	// width and height of where rect must match Roi size
	// Let put our Roi into origin
	Rect WhereRec(250, 100, Roi.cols, Roi.rows);
	// This copy Roi Image into loaded on position Where rec
	Roi.copyTo(LoadedImage(WhereRec));

	namedWindow("Step 4 Final result", WINDOW_AUTOSIZE);
	imshow("Step 4 Final result", LoadedImage);
	waitKey(10000);

	// Same the result from LoadedImage to Step4.JPG
	imwrite("Step4.JPG", LoadedImage);
	}
*/

//Percobaan 3 Mouse events
/* 
void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
	if (event == EVENT_LBUTTONDOWN)
	{
		cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
	}
	else if (event == EVENT_RBUTTONDOWN)
	{
		cout << "Right button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
	}
	else if (event == EVENT_MBUTTONDOWN)
	{
		cout << "Middle button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
	}
	else if (event == EVENT_MOUSEMOVE)
	{
		cout << "Mouse move over the window - position (" << x << ", " << y << ")" << endl;
	}
}

int main(int argc, char** argv)
{
	// Read image from file
	Mat img = imread("../cat.jpg");
	// gunakan gambar yang anda inginkan (jpg, bmp, png)

	//if fail to read the image
	if ( img.empty() )
	{
		cout << "Error loading the image" << endl;
		return -1;
	}
	//Create a window
	namedWindow("Bismillah", 1);

	//set the callback function for any mouse event
	setMouseCallback("Bismillah",  CallBackFunc, NULL);

	//show the image
	imshow("Bismillah", img);

	// Wait until user press some key
	waitKey(0);

	return 0;
}

*/

// Tugas Percobaan 3
/* 
void mouseEvent(int evt, int x, int y, int flags, void* param)
{
	Mat* rgb = (Mat*)param;
	if (evt == CV_EVENT_LBUTTONDOWN)
	{
		printf("Nilai pixel pada koordinat (%d,%d): B=%d, G=%d, R=%d\n",x, y,
			(int)(*rgb).at<Vec3b>(y, x)[0],
			(int)(*rgb).at<Vec3b>(y, x)[1],
			(int)(*rgb).at<Vec3b>(y, x)[2]);
	}
}

int main(int argc, char** argv)
{
	// Read image from file
	Mat img = imread("OrangeCat.JPG");

	//if fail to read the image
	if (img.empty())
	{
		cout << "Error loading the image" << endl;
		return -1;
	}

	//Create a window
	namedWindow("My Window", 1);

	//set the callback function for any mouse event
	setMouseCallback("My Window", mouseEvent, &img);

	//show the image
	imshow("My Window", img);

	// Wait until user press some key
	waitKey(100000);

	return 0;
}
*/
//Percobaan 4 Trackbar (Slider) Control

/// Global variables

int threshold_value = 0;
int threshold_type = 3;
int const max_value = 255;
int const max_type = 4;
int const max_BINARY_value = 255;

Mat src, src_gray, dst;
const char* window_name = "Threshold Demo";

const char* trackbar_type = "Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted";
const char* trackbar_value = "Value";

/// Function headers
void Threshold_Demo(int, void*);


int main(int argc, char** argv)
{
	//! [load]
	String imageName("OrangeCat.jpg"); // by default 
	if (argc > 1)
	{
		imageName = argv[1];
	}
	src = imread(imageName, IMREAD_COLOR); // Load an image

	if (src.empty())
	{
		return -1;
	}

	cvtColor(src, src_gray, COLOR_BGR2GRAY); // Convert the image to Gray
											 //! [load]

											 //! [window]
	namedWindow(window_name, WINDOW_AUTOSIZE); // Create a window to display results
											   //! [window]

											   //! [trackbar]
	createTrackbar(trackbar_type, window_name, &threshold_type, max_type, Threshold_Demo);
	//  Create  Trackbar  to  choose  type of Threshold

	createTrackbar(trackbar_value, window_name, &threshold_value,
		max_value, Threshold_Demo);
	// Create Trackbar to choose  Threshold value
	//! [trackbar]
	Threshold_Demo(0, 0);
	// Call the function to initiali
	/// Wait until user finishes program 
	for (;;)
	{
		char c = (char)waitKey(20);
		if (c == 27)
		{
			break;
		}
	}
}


void Threshold_Demo(int, void*)
{
	// 0: Binary
	// 1: Binary Inverted
	// 2: Threshold Truncated 
	// 3: Threshold to Zero
	// 4: Threshold to Zero Inverted
	
	threshold(src_gray, dst, threshold_value, max_BINARY_value, threshold_type);
	imshow(window_name, dst);
}



//Percobaan 5 Moving around video with slider
/* 
int g_slider_position = 0;
CvCapture* g_capture = NULL;

void onTrackbarSlide(int pos)
{
	cvSetCaptureProperty(g_capture,CV_CAP_PROP_POS_FRAMES,pos);
}

int main( int argc, char** argv )
{
	cvNamedWindow( "AVI", CV_WINDOW_AUTOSIZE );
	g_capture  = cvCreateFileCapture("../Megamind.avi");

	int frames = (int) cvGetCaptureProperty(g_capture,CV_CAP_PROP_FRAME_COUNT);

	if( frames!= 0 ) {
			cvCreateTrackbar("Position","AVI",&g_slider_position,frames,onTrackbarSlide);
		}

	IplImage* frame;
	while(1)
	{
		frame = cvQueryFrame( g_capture );
		if( !frame ) break;
		cvShowImage( "AVI", frame );
		char c = cvWaitKey(25);
		if( c == 27 ) break;
	}

	cvReleaseCapture( &g_capture );
	cvDestroyWindow( "AVI" );

	return(0);
}
*/