#include <iostream>
#include <vector>
#include <cv.h>
#include <cv.hpp>
#include <highgui.h>
#include <highgui.hpp>

int main(int argc, char * argv[])
{
	cv::VideoCapture cap(0);
	cv::namedWindow("Cam", CV_WINDOW_AUTOSIZE);

	if(cap.isOpened())
	{

		for(;;)
		{
			cv::Mat image;
			cap >> image;
			cv::imshow("Cam", image);
			if(cv::waitKey(30) >= 0) break;
		}

	}
}

