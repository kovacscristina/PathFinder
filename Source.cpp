#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>

using namespace std;
//using namespace cv;
int main()
{
	cv::Mat image = cv::imread("maze.png");
	cv::Mat gray;
	cv::Mat trsh;
	vector<std::vector<cv::Point> > contours;
	cv::Mat kernel;
	cv::Mat ero;
	cv::Mat res;
	
	/*From RGB to Gray*/
	cv::cvtColor(image, gray, cv::COLOR_RGBA2GRAY);

	/*From Gray to Binary*/
	cv::threshold(gray, trsh, 100, 255, cv::THRESH_BINARY_INV);

	/*Detect Contours in an Image*/
	cv::findContours(trsh, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
	cv::Mat path = cv::Mat::zeros(image.size(), CV_8UC1);
	cv::drawContours(path, contours, 0, (255, 255, 255), cv::FILLED);

	/*Setting the kernel*/
	kernel = cv::Mat::ones(21, 21, CV_8UC1);

	/*Dilatation and Erodation*/
	cv::dilate(path, path, kernel);
	cv::erode(path, ero, kernel);

	/*Substracting Eroded from Dilated*/
	cv::absdiff(path, ero, path);

	/*Drawing the path*/
	vector<cv::Mat> channels;
	cv::split(image, channels);
	channels[0] &= ~path;
	channels[1] &= ~path;
	channels[2] |= path;
	cv::Mat dst;
	cv::merge(channels, dst);

	/*Solution*/
	cv::imshow("solution", dst);
	cv::waitKey(0);
	return 0;
}