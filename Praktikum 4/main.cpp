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

//Praktikum 1 Brightness and Contrast

double alpha; // Simple contrast control 
int beta;	// Simple brightness control 
int main()
{
	/// Read image given by user
	Mat image = imread("Cat.jpg"); // nama gambar silakan diganti sesuai gambar yang anda gunakan
	Mat new_image = Mat::zeros(image.size(), image.type());

	/// Initialize values
	cout << " Basic Linear Transforms " << endl; 
	cout << "-------------------------" << endl;
	cout << "* Enter the alpha value [1.0-3.0]: "; 
	cin >> alpha;
	cout << "* Enter the beta value [0-100]: "; 
	cin >> beta;

	/// Do the operation new_image(i, j) = alpha*image(i, j) + beta;
		for( int y = 0; y < image.rows; y++ )
			{ for (int x = 0; x < image.cols; x++)
				{
					for (int c = 0; c < 3; c++)
					{
						new_image.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(alpha*(image.at<Vec3b>(y, x)[c])+beta);
					}
				}
			}
	/// Create Windows namedWindow("Original Image", 1);
	namedWindow("New Image", 1);

	/// Show stuff
	imshow("Original Image", image); 
	imshow("New Image", new_image);

	/// Wait until user press some key 
	waitKey();
	return 0;
}


//Praktikum 2 Color Transformation
/* 
int main()
{
	Mat image;
	image = imread("OrangeCat.jpg", CV_LOAD_IMAGE_COLOR);

	if (!image.data)
	{
		cout << "Could not open or find the image" <<
			std::endl;
		return -1;
	}

	// Create a new matrix to hold the gray image 
	Mat gray;

	// convert RGB image to gray 
	cvtColor(image, gray, CV_BGR2GRAY);

	imwrite("GrayCat.jpg", gray);

	namedWindow("Display window", CV_WINDOW_AUTOSIZE); 
	imshow("Display window", image);

	namedWindow("Result window", CV_WINDOW_AUTOSIZE); 
	imshow("Result window", gray);

	waitKey(0); 
	return 0;
}
*/

//Praktikum 3 Compositing and matting
/* 
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
	if( input >= 0.0 && input <= 1.0 )
	{ alpha = input; }

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
*/

//Praktikum 4 Histogram
/* 
int main()
{
	Mat src, dst;
	/// Load image
	src = imread("OrangeCat.jpg", 1);
	if (!src.data)
	{
		return -1;
	}
	/// Separate the image in 3 places ( B, G and R )
	vector<Mat> bgr_planes; 
	split(src, bgr_planes);

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
	for( int i = 1; i < histSize; i++ )
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

//Praktikum 5 Histogram Equalization
/* 
int main()
{
	Mat src, dst;
	char* source_window = "Source image";
	char* equalized_window = "Equalized Image";

	/// Load image
	src = imread("OrangeCat.jpg", 1);

	if (!src.data)
	{
		cout << "Usage: ./Histogram_Demo <path_to_image>" << endl; 
		return -1;
	}

	/// Convert to grayscale
	cvtColor(src, src, CV_BGR2GRAY);

	/// Apply Histogram Equalization
	equalizeHist(src, dst);

	/// Display results
	namedWindow(source_window, CV_WINDOW_AUTOSIZE); 
	namedWindow(equalized_window, CV_WINDOW_AUTOSIZE);
		
	imshow(source_window, src);
	imshow(equalized_window, dst);

	/// Wait until user exits the program 
	waitKey(0);

	return 0;
}
*/

//Tugas
/* 

int main() {

	// Don't use global variables if they are not needed!
	VideoCapture vid(0);
	Mat frame;
	while (true)
	{
		// Read frame
		vid.read(frame);

		/// Separate the image in 3 places ( B, G and R )
		vector<Mat> bgr_planes;
		split(frame, bgr_planes);

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

		Size sz1 = frame.size();
		Size sz2 = histImage.size();


		Mat im3(sz1.height, sz1.width+sz2.width, CV_8UC3);
		Mat Left(im3, Rect(0, 0, sz1.width, sz1.height));
		frame.copyTo(Left);
		Mat Right(im3, Rect(sz1.width,0,sz2.width,sz2.height));
		histImage.copyTo(Right);

		/// Display
		imshow("Webcam", im3);

		if ((waitKey(30) & 0xFF) == 27) { // for portability
			break;
		}
	}
}



*/