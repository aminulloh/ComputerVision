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
/* 
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
*/

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

//Tugas 2.1 Manual RGB2Gray
/* 
int main()
{
	const float pi = 3.14;
	Mat src1, src2;
	src1 = imread("OrangeCat.jpg", CV_LOAD_IMAGE_COLOR);
	src2 = Mat::zeros(src1.rows, src1.cols, CV_8UC1);

	if (!src1.data) { printf("Error loading src1 \n"); return -1; }

	for (int i = 0; i<src1.cols; i++) {
		for (int j = 0; j<src1.rows; j++)
		{
			Vec3b color1 = src1.at<Vec3b>(Point(i, j));
			Scalar color2 = src2.at<uchar>(Point(i, j));
			color2 = (color1.val[0] + color1.val[1] + color1.val[2]) / 3;

			src2.at<uchar>(Point(i, j)) = color2.val[0];
		}
	}

	//imwrite("C:\\Users\\arjun\\Desktop\\greyscale.jpg",src2);

	namedWindow("GRAYSCALE_IMAGE", CV_WINDOW_AUTOSIZE);
	imshow("GRAYSCALE_IMAGE", src2);

	namedWindow("Original Image", CV_WINDOW_AUTOSIZE);
	imshow("Original Image", src1);

	waitKey(0);
	return 0;
}
*/

//Tugas2.2
/*
int main() {
	Mat image;
	image = imread("cat.jpg", 1);

	Mat RGB2GRAY_image;
	cvtColor(image, RGB2GRAY_image, CV_RGB2GRAY);

	Mat RGB2XYZ_image;
	cvtColor(image, RGB2XYZ_image, CV_RGB2XYZ);

	Mat RGB2YCrCb_image;
	cvtColor(image, RGB2YCrCb_image, CV_RGB2YCrCb);

	Mat RGB2HSV_image;
	cvtColor(image, RGB2HSV_image, CV_RGB2HSV);

	Mat RGB2Lab_image;
	cvtColor(image, RGB2Lab_image, CV_RGB2Lab);

	namedWindow("original image", CV_WINDOW_AUTOSIZE);
	imshow("original image", image);

	namedWindow("RGB2GRAY image", CV_WINDOW_AUTOSIZE);
	imshow("RGB2GRAY image", RGB2GRAY_image);

	namedWindow("RGB2XYZ image", CV_WINDOW_AUTOSIZE);
	imshow("RGB2XYZ image", RGB2XYZ_image);

	namedWindow("RGB2YCrCb image", CV_WINDOW_AUTOSIZE);
	imshow("RGB2YCrCb image", RGB2YCrCb_image);

	namedWindow("RGB2HSV image", CV_WINDOW_AUTOSIZE);
	imshow("RGB2HSV image", RGB2HSV_image);

	namedWindow("RGB2Lab image", CV_WINDOW_AUTOSIZE);
	imshow("RGB2Lab image", RGB2Lab_image);

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
	src1 = imread("BlendApp.jpg");
	src2 = imread("BlendTrump.jpg");

	if (!src1.data) { printf("Error loading src1 \n"); return -1; } 
	if (!src2.data) { printf("Error loading src2 \n"); return -1; }

	/// Create Windows 
	namedWindow("Linear Blend", 1);

	beta = (1.0 - alpha);
	addWeighted(src1, alpha, src2, beta, 0.0, dst); 
	imshow("Linear Blend", dst);

	namedWindow("image1", CV_WINDOW_AUTOSIZE);
	imshow("image1", src1);
	namedWindow("image2", CV_WINDOW_AUTOSIZE);
	imshow("image2", src2);
	waitKey(0); 
	return 0;
}
*/

//Tugas 3.1 Blending
/*
void alphaBlend(Mat& foreground, Mat& background, Mat& alpha, Mat& outImage)
{
	// Find number of pixels. 
	int numberOfPixels = foreground.rows * foreground.cols * foreground.channels();

	// Get floating point pointers to the data matrices
	float* fptr = reinterpret_cast<float*>(foreground.data);
	float* bptr = reinterpret_cast<float*>(background.data);
	float* aptr = reinterpret_cast<float*>(alpha.data);
	float* outImagePtr = reinterpret_cast<float*>(outImage.data);

	// Loop over all pixesl ONCE
	for (
		int i = 0;
		i < numberOfPixels;
		i++, outImagePtr++, fptr++, aptr++, bptr++
		)
	{
		*outImagePtr = (*fptr)*(*aptr) + (*bptr)*(1 - *aptr);
	}
}

int main() {

	Mat foreground = imread("BlendTrump.jpg");
	Mat background = imread("BlendLenna.jpg");
	Mat alpha = imread("BlendApp.jpg");

	// Convert Mat to float data type
	foreground.convertTo(foreground, CV_32FC3);
	background.convertTo(background, CV_32FC3);

	// Storage for output image
	Mat ouImage = Mat::zeros(foreground.size(), foreground.type());

	alphaBlend(foreground,background,alpha,ouImage);

	imshow("alpha blended image", ouImage / 255);
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

//Tugas 4.1 Histogram grayscale
 
int main() {
	
	Mat src, dst;
	/// Load image
	src = imread("../data/OrangeCat.jpg", 1);
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



//Tugas 4.2 Histogram without calhist
/* 
vector<int> calcuHisto(const IplImage *src_pic, int anzBin)
{
	CvSize size = cvGetSize(src_pic);
	double binSize = 256.0 / anzBin;        //new definition
	vector<int> histogram(anzBin, 0);        //i don't know if this works so I
											 //so I will leave it

											 //goes through all rows
	for (int y = 0; y<size.height; y++)
	{
		//grabs an entire row of the imageData
		const uchar *src_pic_point = (uchar *)(src_pic->imageData + y*src_pic->widthStep);

		//goes through each column
		for (int x = 0; x<size.width; x++)
		{
			//for each bin
			for (int z = 0; z < anzBin; z++)
			{
				//check both upper and lower limits
				if (src_pic_point[x] >= z*binSize && src_pic_point[x] < (z + 1)*binSize)
				{
					//increment the index that contains the point
					histogram[z]++;
				}
			}
		}
	}
	return histogram;
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
/* 
double alpha; // Simple contrast control 
int beta;	// Simple brightness control 
float Mp = 0.2, Ap = 0.1;

int main()
{
	/// Read image given by user
	Mat image = imread("../data/Cat.jpg"); // nama gambar silakan diganti sesuai gambar yang anda gunakan
	Mat new_image = Mat::zeros(image.size(), image.type());

	/// Initialize values
	

	/// Do the operation new_image(i, j) = alpha*image(i, j) + beta;
	for (int y = 0; y < image.rows; y++)
	{
		for (int x = 0; x < image.cols; x++)
		{
			for (int c = 0; c < 3; c++)
			{
				new_image.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(Mp*(image.at<Vec3b>(y, x)[c]) + Ap);
			}
		}
	}
	/// Create Windows 
	namedWindow("Original Image", 1);
	namedWindow("New Image", 1);

	/// Show stuff
	imshow("Original Image", image);
	imshow("New Image", new_image);

	/// Wait until user press some key 
	waitKey();
	return 0;
}
*/