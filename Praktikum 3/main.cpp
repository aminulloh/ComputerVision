#include<stdlib.h>
#include<math.h>
#include<string.h>
#include <iostream>


#include<opencv2\opencv.hpp>
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<opencv2\ml\ml.hpp>
#include<opencv2\objdetect\objdetect.hpp>

using namespace std;
using namespace cv;

//Praktikum 1 Membaca video dari File
/* 
int main() {

	// Create a VideoCapture object and open the input file
	// If the input is the web camera, pass 0 instead of the video file name
	VideoCapture cap("Megamind.avi");

	// Check if camera opened successfully 
	if (!cap.isOpened()) {
		cout << "Error opening video stream or file" << endl;
		return -1;
	}
	while (1) {
		Mat frame;
		// Capture frame-by-frame 
		cap >> frame;

		//double fps = cap.get(CAP_PROP_FPS);
		//cout << "Frames per second : " << fps << endl;

		// If the frame is empty, break immediately 
		if (frame.empty())
			break;

		// Display the resulting frame 
		imshow("Frame", frame);

		// Press	ESC on keyboard to exit 
		char c = (char)waitKey(25);
		if (c == 27)
			break;
	}

	// When everything done, release the video capture object 
	cap.release();

	// Closes all the frames 
	destroyAllWindows();

	return 0;
}


//Praktikum 2 Mengakses kamera secara online
/* 
int main() {

	// Create a VideoCapture object and use camera to capture the video
	VideoCapture cap1(1);

	// Check if camera opened successfully
	if (!cap1.isOpened())
	{
		cout << "Error opening video stream" << endl;
		return -1;
	}

	// Default resolution of the frame is obtained.The default resolution is system dependent.
	int frame_width = cap1.get(CV_CAP_PROP_FRAME_WIDTH);
	int frame_height = cap1.get(CV_CAP_PROP_FRAME_HEIGHT);

	// Define the codec and create VideoWriter object.The output is stored in 'outcpp.avi' file.
	VideoWriter video("out.avi", CV_FOURCC('M', 'J', 'P', 'G'), 10, Size(frame_width, frame_height));
	while (1)
	{
		Mat frame;

		// Capture frame-by-frame
		cap1 >> frame;

		// If the frame is empty, break immediately
		if (frame.empty())
		break;

		// Write the frame into the file 'outcpp.avi'
		video.write(frame);

		// Display the resulting frame
		imshow("Frame", frame);

		// Press	ESC on keyboard to	exit
		char c = (char)waitKey(1);
		if (c == 27)
		break;
	}

	// When everything done, release the video capture and write object
	cap1.release();
	video.release();

	// Closes all the windows
	destroyAllWindows();
	return 0;
}

*/
//Praktikum 3 Menyimpan hasil capture kamera ke file video
/* 
int main() {

	// Create a VideoCapture object and use camera to capture the video
	VideoCapture cap(1);

	// Check if camera opened successfully 
	if (!cap.isOpened())
	{
		cout << "Error opening video stream" << endl;
		return -1;
	}

	// Default resolution of the frame is obtained.The default resolution is system dependent.
	int frame_width = cap.get(CV_CAP_PROP_FRAME_WIDTH);
	int frame_height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
	double fps = cap.get(CV_CAP_PROP_FPS);

	// Define the codec and create VideoWriter object.The output is stored in 'outcpp.avi' file.
	VideoWriter video("out.avi", CV_FOURCC('M', 'J', 'P', 'G'), 10, Size(frame_width, frame_height));
	while (1)
	{
		Mat frame;

		// Capture frame-by-frame 
		cap >> frame;

		// If the frame is empty, break immediately 
		if (frame.empty())
			break;

		double fps = cap.get(CV_CAP_PROP_FPS);

		putText(frame, fps, Point(5, 100), FONT_HERSHEY_DUPLEX, 1, Scalar(0, 0, 255), 2);

		// Write the frame into the file 'outcpp.avi' 
		video.write(frame);

		// Display the resulting frame 
		imshow("Frame", frame);

		// Press	ESC on keyboard to	exit
		char c = (char)waitKey(1);
		if (c == 27)
			break;
	}

	// When everything done, release the video capture and write object
	cap.release();
	video.release();

	// Closes all the windows 
	destroyAllWindows();
	return 0;
}

*/

// Tugas

//int R, G, B;

void mouseEvent(int evt, int x, int y, int flags, void* param)
{
	Mat* rgb = (Mat*)param;
	if (evt == CV_EVENT_LBUTTONDOWN)
	{
		printf("Nilai pixel pada koordinat (%d,%d): B=%d, G=%d, R=%d\n", x, y,
			(int)(*rgb).at<Vec3b>(y, x)[0],
			(int)(*rgb).at<Vec3b>(y, x)[1],
			(int)(*rgb).at<Vec3b>(y, x)[2]);
	}


}

int main() {

	// Create a VideoCapture object and use camera to capture the video
	VideoCapture cap(0);

	// Check if camera opened successfully
	if (!cap.isOpened())
	{
		cout << "Error opening video stream" << endl;
		return -1;
	}

	// Default resolution of the frame is obtained.The default resolution is system dependent. 
	int frame_width = cap.get(CV_CAP_PROP_FRAME_WIDTH);
	int frame_height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
	int fps = cap.get(CV_CAP_PROP_FPS);
	

	// Define the codec and create VideoWriter object.The output is stored in 'outcpp.avi' file. 
	VideoWriter video("outcpp.avi", CV_FOURCC('M', 'J', 'P', 'G'), 10, Size(frame_width, frame_height));
	while (1)
	{
		Mat frame;

		// Capture frame-by-frame 
		cap >> frame;

		// If the frame is empty, break immediately
		if (frame.empty())
			break;
		
		// Display FPS
		cout << "FPS =" << fps << endl;
		string s = to_string(fps);
		putText(frame, s , Point(5, (frame_height-5)), FONT_HERSHEY_DUPLEX, 1, Scalar(0, 0, 255), 2);
		//putText(frame, R + G + B, Point(35, (frame_height - 5)), FONT_HERSHEY_DUPLEX, 1, Scalar(0, 0, 255), 2);

		// Draw rectangle
		Rect RectangleToDraw4(300, 300, 100, 100);
		rectangle(frame, RectangleToDraw4, Scalar(255, 0, 0), 2, 8, 0);

		// Write the frame into the file 'outcpp.avi'
		video.write(frame);

		//set the callback function for any mouse event
		setMouseCallback("My Window", mouseEvent, &frame);

		// Display the resulting frame    
		imshow("Frame", frame);

		// Press  ESC on keyboard to  exit
		char c = (char)waitKey(1);
		if (c == 27)
			break;
	}

	// When everything done, release the video capture and write object
	cap.release();
	video.release();

	// Closes all the windows
	destroyAllWindows();
	return 0;
}