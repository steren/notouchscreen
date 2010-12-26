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

#include "GestureSignature.h"

#include "config.h"
#ifdef WINDOWS
	#define OpenCvHighGuiEchapKeyCode 27
#endif
#ifdef LINUX
	#define OpenCvHighGuiEchapKeyCode 1048603
#endif

#include "KeyStroker.h"
#include "IoServices.h"
#include "NoTouchScreenException.h"
#include "Fifo.hpp"
#include "ActionManager.h"



NoTouchScreen::NoTouchScreen() {
}

NoTouchScreen::~NoTouchScreen() {
}

void NoTouchScreen::MainLoop()
{
	const double DURATION 	= 0.7;

	const int SCORE_FRAMES 	= 20;

	const double PANRIGHT_THRESHOLD = 25.0;
	const double PANLEFT_THRESHOLD  = 25.0;
	const double ZOOMOUT_THRESHOLD  = 40.0;

	const double SCORE_GOAL_LEFT 	= 0;
	const double SCORE_GOAL_RIGHT 	= 180;

	using namespace cv;

	VideoCapture cap1(0);
	namedWindow("Visu", CV_WINDOW_AUTOSIZE);

	if(cap1.isOpened())
	{
		Mat frames[2];
		int currentFrame = 0;
		int nextFrame = 1;

		Mat currentCap;
		cap1 >> currentCap;
		Mat silhouette;
		Mat mhi(currentCap.size(), CV_32FC1); // the Motion History image
		Mat mask, orientation, rightRestrictedMask, leftRestrictedMask;
		Mat mhiVisu; // a display of the MHI
		Mat capGray;
		Mat compositingVisu;

		// A rectangle of the left side of the image
		Rect leftRect(0,0, (int) (currentCap.size().width / 2), currentCap.size().height);
		// A rectangle of the right side of the image
		Rect rightRect((int) (currentCap.size().width / 2), 0, (int) (currentCap.size().width / 2), currentCap.size().height);

		// Define the gestures
		RotationDescriptor leftDescriptor(0);
		RotationDescriptor rightDescriptor(180);

		std::vector<FrameDescriptorBundle> panLeftFrames;
		std::vector<FrameDescriptorBundle> panRightFrames;
		std::vector<FrameDescriptorBundle> zoomOutFrames;
		for(int i = 0; i < SCORE_FRAMES; i++) {
			panLeftFrames.push_back( FrameDescriptorBundle(leftDescriptor,1,leftDescriptor,0,rightDescriptor,0));
			panRightFrames.push_back( FrameDescriptorBundle(rightDescriptor,1,leftDescriptor,0,rightDescriptor,0));
			zoomOutFrames.push_back( FrameDescriptorBundle(rightDescriptor,0,leftDescriptor,0.5,rightDescriptor,0.5));
		}
		GestureSignature panLeft("Pan Left", panLeftFrames);
		GestureSignature panRight("Pan Right", panRightFrames);
		GestureSignature zoomOut("Zoom Out", zoomOutFrames);

		Fifo<FrameDescriptorBundle> frameDescriptors(SCORE_FRAMES, panRightFrames[0]);

		KeyStroker& stroker = IoServices::GetKeyStrokerInstance();

		bool buzy = false; // is an action currently performed ?
		int buzyWait = 0;
		std::string buzyAction = "";


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
			double globalAngle = cv::calcGlobalOrientation(orientation, mask, mhi, timestamp, DURATION);

			// Left Angle
			leftRestrictedMask = mask.clone();
			Mat rightImage(leftRestrictedMask, rightRect);
			rightImage = Scalar(0);
			double leftAngle = cv::calcGlobalOrientation(orientation, leftRestrictedMask, mhi, timestamp, DURATION);

			// Right Angle
			rightRestrictedMask = mask.clone();
			Mat leftImage(rightRestrictedMask, leftRect);
			leftImage = Scalar(0);
			double rightAngle = cv::calcGlobalOrientation(orientation, rightRestrictedMask, mhi, timestamp, DURATION);

			// angle == 0 if no movement detected, this sucks.
			if(globalAngle != 0) {
				frameDescriptors.push( FrameDescriptorBundle(RotationDescriptor(globalAngle),0,RotationDescriptor(leftAngle),0,RotationDescriptor(rightAngle),0) );
			} else {
				RotationDescriptor random = RotationDescriptor( std::rand() % 360 );
				frameDescriptors.push( FrameDescriptorBundle(random,0, random,0, random,0) );
			}
			double distanceLeft = panLeft.compare(frameDescriptors);
			printDoubleOnImage(compositingVisu, "Pan Left", static_cast<int>(distanceLeft), 80);

			double distanceRight = panRight.compare(frameDescriptors);
			printDoubleOnImage(compositingVisu, "Pan Right", static_cast<int>(distanceRight), 100);

			double distancezoomOut = zoomOut.compare(frameDescriptors);
			printDoubleOnImage(compositingVisu, "Zoom Out", static_cast<int>(distancezoomOut), 120);

			if(buzyWait > 50) {
				buzy = false;
				buzyWait = 0;
			}
			if(!buzy) {
				if(distanceLeft < PANLEFT_THRESHOLD * SCORE_FRAMES) {
					ActionManager::Instance().SendEvent("OnLeftTranslation");
					buzy = true;
					buzyAction = "left";
				}
				if(distanceRight < PANRIGHT_THRESHOLD * SCORE_FRAMES) {
					ActionManager::Instance().SendEvent("OnRightTranslation");
					buzy = true;
					buzyAction = "right";
				}
				if(distancezoomOut < ZOOMOUT_THRESHOLD * SCORE_FRAMES) {
					//ActionManager::Instance().SendEvent("OnLeftTranslation");
					buzy = true;
					buzyAction = "Zoom Out";
				}
			} else {
				cv::putText(compositingVisu, buzyAction + " - WAITING", Point(50,50), 1, 1, 255);
				buzyWait++;
			}

			// Display Orientation with a line
			if(globalAngle != 0) {
				printDoubleOnImage(compositingVisu, "Angle", static_cast<int>(globalAngle), 20);
				int x = static_cast<int>(30.*cos(globalAngle*CV_PI/180));
				int y = static_cast<int>(30.*sin(globalAngle*CV_PI/180));
				cv::line(compositingVisu, Point(30,30), Point(30+x,30+y),255, 1);

				printDoubleOnImage(compositingVisu, "leftAngle", static_cast<int>(leftAngle), 180);
				printDoubleOnImage(compositingVisu, "rightAngle", static_cast<int>(rightAngle), 200);
			}

			//imshow("Visu", compositingVisu);
			imshow("Visu", silhouette);

			int key = waitKey(2);
			if( OpenCvHighGuiEchapKeyCode == key )
			{
				break;
			}
		}
	}
}

void NoTouchScreen::printDoubleOnImage(cv::Mat image, std::string name, int number, unsigned int y)
{
	std::ostringstream s;
	s << number;
	cv::putText(image, name + ": " + s.str(), cv::Point(0,y), 1, 1, 255);
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
