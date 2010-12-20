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

#include "KeyStroker.h"
#include "IoServices.h"
#include "NoTouchScreenException.h"
#include "Fifo.hpp"

NoTouchScreen::NoTouchScreen() {
}

NoTouchScreen::~NoTouchScreen() {
}

void NoTouchScreen::MainLoop()
{
	const double DURATION 	= 0.7;

	const int SCORE_FRAMES 	= 20;
	const int SCORE_WIN 	= 10;

	const double SCORE_THRESHOLD = 30;
	const double SCORE_GOAL_LEFT 	= 0;
	const double SCORE_GOAL_RIGHT 	= 180;

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

		KeyStroker& stroker = IoServices::GetKeyStrokerInstance();

		bool buzy = false; // is an action currently performed ?
		int buzyWait = 0;

		// Define the gestures
		//std::vector<GestureFrame> panLeftFrames;
		//GestureSignature panLeft("Pan Left", panLeftFrames);

		Fifo<int>scoresLeft(SCORE_FRAMES, 0);
		Fifo<int>scoresRight(SCORE_FRAMES, 0);

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

			if( angle != 0 && std::abs(angle - SCORE_GOAL_LEFT) < SCORE_THRESHOLD) {
				scoresLeft.push(1);
			} else {
				scoresLeft.push(0);
			}
			if( angle != 0 && std::abs(angle - SCORE_GOAL_RIGHT) < SCORE_THRESHOLD) {
				scoresRight.push(1);
			} else {
				scoresRight.push(0);
			}

			int sumLeft 	= 0;
			int sumRight 	= 0;
			for( int i = 0; i < SCORE_FRAMES; i++) {
				sumLeft += scoresLeft.get(i);
				sumRight += scoresRight.get(i);
			}

			if(buzyWait > 50) {
				buzy = false;
				buzyWait = 0;
			}

			if(!buzy) {
				if(sumLeft >= SCORE_WIN) {
					cv::putText(compositingVisu, "LEFT", Point(50,50), 1, 1, 255);
					//stroker.StrokeKey(KeyStroker::RightKey,true,true);
					stroker.StrokeKey(KeyStroker::RightKey);
					buzy = true;
				}
				if(sumRight >= SCORE_WIN) {
					cv::putText(compositingVisu, "RIGHT", Point(50,50), 1, 1, 255);
					//stroker.StrokeKey(KeyStroker::LeftKey,true,true);
					stroker.StrokeKey(KeyStroker::LeftKey);
					buzy = true;
				}
			} else {
				buzyWait++;
			}

			// Display Orientation with a line
			if(angle != 0) {
				// print angle value
				std::ostringstream s;
				s << angle;
				cv::putText(compositingVisu, s.str(), Point(20,20), 1, 1, 255);
				int x = static_cast<int>(30.*cos(angle*CV_PI/180));
				int y = static_cast<int>(30.*sin(angle*CV_PI/180));
				cv::line(compositingVisu, Point(30,30), Point(30+x,30+y),255, 1);
			}

			imshow("Visu", compositingVisu);
			imshow("Motion History", mhiVisu);

			if(waitKey(2) == 1) break;
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
