#include <iostream>
#include <vector>
#include "OpenCVLibs.h"
#include "ImageFifo.h"

using namespace cv;

const double DURATION = 1;

int main(int argc, char * argv[])
{
	cv::VideoCapture cap1(0);
	cv::namedWindow("Visu", CV_WINDOW_AUTOSIZE);
	cv::namedWindow("Motion History", CV_WINDOW_AUTOSIZE);

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

		cv::Mat silhouette; 	// the silouhette image
		cv::Mat silhouette2; 	// the silouhette image
		double timestamp; 		// the timestamp of each silhouette

		cv::Mat mhi(empty.size(), CV_32FC1); // the Motion History image
		cv::Mat mhiVisu; // a display of the MHI

		for(;;)
		{
			nextFrame = (currentFrame+1)%2;
			cap1 >> currentCap;
			frames[currentFrame] = currentCap.clone();
			currentCap.copyTo(frames[currentFrame]);
			cv::absdiff(frames[currentFrame],frames[nextFrame],silhouette);
			cv::cvtColor( silhouette, silhouette2, CV_BGR2GRAY );
			cv::imshow("Visu", silhouette2);

			timestamp = (double)clock()/CLOCKS_PER_SEC;
			cv::updateMotionHistory(silhouette2, mhi, timestamp, DURATION);

			// Display the MHI (need scaling)
			cv::convertScaleAbs(mhi, mhiVisu, 255./DURATION, (DURATION - timestamp)*255./DURATION );
			cv::imshow("Motion History", mhiVisu);


			if(cv::waitKey(30) >= 0) break;
			currentFrame = nextFrame;
		}
	}

	return 0;
}

