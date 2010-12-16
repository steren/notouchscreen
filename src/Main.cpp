#include <iostream>
#include <vector>
#include "OpenCVLibs.h"
#include "ImageFifo.h"

using namespace cv;


int main(int argc, char * argv[])
{
	cv::VideoCapture cap1(0);
	cv::namedWindow("Visu", CV_WINDOW_AUTOSIZE);

	if(cap1.isOpened())
	{
		cv::Mat frames[2];
		int currentFrame = 0;
		int nextFrame = 1;

		cv::Mat currentCap;
		cap1 >> currentCap;

		Scalar t(0);
		cv::Mat empty(currentCap.size(),currentCap.type(),t);
		frames[0] = empty.clone();
		frames[1] = empty.clone();

		cv::Mat silhouette;
		for(;;)
		{
			nextFrame = (currentFrame+1)%2;
			cap1 >> currentCap;
			frames[currentFrame] = currentCap.clone();
			currentCap.copyTo(frames[currentFrame]);
			cv::absdiff(frames[currentFrame],frames[nextFrame],silhouette);
			cv::imshow("Visu",silhouette);
			if(cv::waitKey(30) >= 0) break;
			currentFrame = nextFrame;
		}
	}

	return 0;
}

