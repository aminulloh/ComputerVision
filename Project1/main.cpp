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


int main()
{
	Mat image;
	image = imread("face.jpg", CV_LOAD_IMAGE_COLOR);	// Ganti myface.jpg dengan gambar anda sendiri
	namedWindow("window1", 1); 
	imshow("window1", image);

	// Load Face cascade (.xml file) 
	CascadeClassifier face_cascade;
	face_cascade.load("haarcascade_frontalface_alt.xml");	// Letakkan file xml tersebut di satu folder yang sama dengan debug/release

	if (face_cascade.empty())
		//  if(!face_cascade.load("D:\\opencv2410\\sources\\data\\haarcascades\\ha arcascade_frontalface_alt.xml"))
	{
		cerr << "Error Loading XML file" << endl; 
		return 0;
	}

	// Detect faces 
	std::vector<Rect> faces;
	face_cascade.detectMultiScale(image, faces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));

	// Draw circles on the detected faces 
	for(int i = 0; i < faces.size(); i++)
	{
		Point center(faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5);
		ellipse(image, center, Size(faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);
	}
	imshow("Detected Face", image); 
	waitKey(0);
	return 0;
}

/* 
int main()
{
	VideoCapture capture(1); 
		if (!capture.isOpened())
		printf("Error when reading file"); 
		namedWindow("window", 1);
		for (;;)
		{
			Mat  image; capture >> image; 
			if (image.empty()) break;

			// Load Face cascade (.xml file) 
			CascadeClassifier face_cascade;
			face_cascade.load("haarcascade_frontalface_alt.xml"); 
			if (!face_cascade.load("haarcascade_frontalface_alt.xml"))
			{
				cerr << "Error Loading XML file" << endl; 
				return 0;
			}

			// Detect faces 
			std::vector<Rect> faces;
			face_cascade.detectMultiScale(image, faces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(24, 24));

			// Draw circles on the detected faces 
			for(int i=0;i<faces.size();i++)
			{
				Point center(faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5);
				ellipse(image, center, Size(faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);
			}

			imshow("Detected Face", image); 
			waitKey(1);
		}

	return 0;
}
*/