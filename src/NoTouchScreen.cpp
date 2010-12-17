/**
 * NoTouchScreen implementation
 *
 *  Created on: 16 déc. 2010
 *      @author canard (jeanbernard.jansen@gmail.com)
 *      @author steren (steren.giannini@gmail.com)
 */

#include "NoTouchScreen.h"
#include <iostream>
#include <ctime>

NoTouchScreen::NoTouchScreen() {
}

NoTouchScreen::~NoTouchScreen() {
}

void NoTouchScreen::MainLoop()
{
	const double DURATION = 0.5;
	using namespace cv;

	VideoCapture cap1(0);
	namedWindow("Visu", CV_WINDOW_AUTOSIZE);
	namedWindow("Motion History", CV_WINDOW_AUTOSIZE);

	if(cap1.isOpened())
	{
		Mat frames[2];
		int currentFrame = 0;
		int nextFrame = 1;

		Mat currentCap;
		cap1 >> currentCap;

		Mat silhouette;
		Mat mhi(currentCap.size(), CV_32FC1); // the Motion History image

		Mat mask, orientation;

		Mat mhiVisu; // a display of the MHI
		Mat capGray;
		Mat compositingVisu;

		double timestamp;
		for(;;)
		{
			Mat silhouette = GetNextSilhouette(cap1);

			timestamp = (double)clock()/CLOCKS_PER_SEC;
			updateMotionHistory(silhouette, mhi, timestamp, DURATION);

			// Display the MHI (need scaling)
			mhi.convertTo(mhiVisu, CV_8UC1, 255./DURATION, (DURATION - timestamp)*255./DURATION);

			// Add the Motion History on the original image, just for fun.
			cvtColor( currentCap, capGray, CV_BGR2GRAY );
			cv::add( capGray, mhiVisu, compositingVisu);

			cv::calcMotionGradient( mhi, mask, orientation, 0.5, 0.05);
			double angle = cv::calcGlobalOrientation(orientation, mask, mhi, timestamp, DURATION);

			// Display Orientation with a line
			if(angle != 0) {
				/*
				// print angle value
				std::ostringstream s;
				s << angle;
				cv::putText(compositingVisu, s.str(), Point(20,20), 1, 1, 255);
				*/
				cv::line(compositingVisu, Point(30,30), Point(30 + 30*cos(angle*CV_PI/180), 30 + 30*sin(angle*CV_PI/180) ),255, 1);
			}

			imshow("Visu", compositingVisu);
			imshow("Motion History", mhiVisu);

			if(waitKey(30) >= 0) break;
		}
	}
}

cv::Mat& NoTouchScreen::GetNextSilhouette(cv::VideoCapture& iCap)
{
	using namespace cv;

	static Mat currentCap;
	// Getting the current image;
	iCap >> currentCap;

	// Computing gray in one channel image
	static Mat gray;
	cvtColor( currentCap, gray, CV_BGR2GRAY );

	// Initialising frames cache with static variables
	// It avoids to reallocate them each time
	static Mat frames[2] = {gray.clone(), gray.clone()};
	static unsigned int currentFrame = 0;
	unsigned int nextFrame = (currentFrame+1)%2;

	// Computing silhouette
	static Mat diff;
	gray.copyTo(frames[currentFrame]);
	absdiff(frames[currentFrame],frames[nextFrame],diff);

	cv::GaussianBlur(diff, diff, cv::Size(15,15), 5, 5);

	static Mat silhouette;
	threshold(diff, silhouette, NTS_SILHOUETTE_THRESHOLD, NTS_SILHOUETTE_VALUE,THRESH_BINARY);

	currentFrame = nextFrame;
	return silhouette;
}
