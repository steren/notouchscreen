#include <iostream>
#include <vector>
#include <cv.h>
#include <cv.hpp>
#include <highgui.h>
#include <highgui.hpp>
#include "ImageFifo.h"

using namespace cv;


int main(int argc, char * argv[])
{
	cv::VideoCapture cap(0);
	cv::namedWindow("Cam", CV_WINDOW_AUTOSIZE);

	if(cap.isOpened())
	{
		cv::Mat frame;
		cap >> frame;
		ImageFifo imageFifo(3, frame.cols, frame.rows );
		for(;;)
		{
			imageFifo.pushImage(cap);

			cv::imshow("Cam", imageFifo.getLast());
			/*
			cv::Mat edges;
			cv::Mat image;
			cap >> image;
	        cv::cvtColor(image, edges, CV_BGR2GRAY);
	        cv::GaussianBlur(edges, edges, cv::Size(25,25), 10, 10);
			cv::imshow("Cam", edges);
			*/
			if(cv::waitKey(30) >= 0) break;
		}

	}
}

