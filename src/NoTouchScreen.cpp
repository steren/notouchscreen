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

#include <boost/scoped_array.hpp>
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

		for(;;)
		{
			Mat silhouette = GetNextSilhouette(cap1);
			processVectorRecognition(silhouette,true);

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
	s << name << ": " << number;
	cv::putText(image,s.str(),cv::Point(0,y), 1, 1, 255);
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

void NoTouchScreen::processVectorRecognition(cv::Mat& silhouette,bool iShowCompositingVisu)
{
	using namespace cv;

	// Const part
	const double DURATION 	= 0.7;




	const double THRESHOLD  = 25.0;

	const double SCORE_GOAL_LEFT 	= 0;
	const double SCORE_GOAL_RIGHT 	= 180;

	// Init part
	static Mat mhi(silhouette.size(), CV_32FC1); // the Motion History image
	static Mat mask, orientation, rightRestrictedMask, leftRestrictedMask;
	static Mat mhiVisu; // a display of the MHI
	static Mat capGray;
	static Mat compositingVisu(silhouette.size(),silhouette.type());

	// A rectangle of the left side of the image
	static Rect leftRect(0,0, (int) (silhouette.size().width / 2), silhouette.size().height);
	// A rectangle of the right side of the image
	static Rect rightRect((int) (silhouette.size().width / 2), 0, (int) (silhouette.size().width / 2), silhouette.size().height);



	static std::vector<GestureSignature> gestures;
	// The static usage of a bool is a trick to avoid a if block
	static bool isInit = initVectorRecognition(gestures);
	static boost::scoped_array<double> distances(new double[gestures.size()]);


	static Fifo<FrameDescriptorBundle> frameDescriptors(SCORE_FRAMES, gestures[0].get(0));
	static KeyStroker& stroker = IoServices::GetKeyStrokerInstance();
	static bool buzy = false; // is an action currently performed ?
	static int buzyWait = 0;
	static double timestamp;

	// Here goes the algotrithm
	{
		std::string buzyAction("");

		timestamp = (double)clock()/CLOCKS_PER_SEC;
		updateMotionHistory(silhouette, mhi, timestamp, DURATION);

		// Display the MHI (need scaling)
		mhi.convertTo(mhiVisu, CV_8UC1, 255./DURATION, (DURATION - timestamp)*255./DURATION);

		// Add the Motion History on the original image, just for fun.
		if(iShowCompositingVisu)
		{
			compositingVisu = Scalar(0);
			cv::add( compositingVisu, mhiVisu, compositingVisu);
		}

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

		if(buzyWait > 50) {
			buzy = false;
			buzyWait = 0;
		}

		for(unsigned int i=0; i < gestures.size(); i++)
		{
			double distance = gestures[i].compare(frameDescriptors);
			if(iShowCompositingVisu)
				printDoubleOnImage(compositingVisu, gestures[i].getName(), static_cast<int>(distance), 80 + i*20);

			if( !buzy)
			{
				if( distance < gestures[i].getThreshold()*SCORE_FRAMES)
				{
					//ActionManager::Instance().SendEvent("OnLeftTranslation");
					gestures[i].FireEvent();
					buzy = true;
					buzyAction.append("left");
				}
			}
			else {
				if( iShowCompositingVisu )
				{
					buzyAction.append(" - WAITING");
					cv::putText(compositingVisu, buzyAction, Point(50,50), 1, 1, 255);
				}
				buzyWait++;
			}
		}

		if(iShowCompositingVisu)
		{
			// Display Orientation with a line
			if(globalAngle != 0) {
				printDoubleOnImage(compositingVisu, "Angle", static_cast<int>(globalAngle), 20);
				int x = static_cast<int>(30.*cos(globalAngle*CV_PI/180));
				int y = static_cast<int>(30.*sin(globalAngle*CV_PI/180));
				cv::line(compositingVisu, Point(30,30), Point(30+x,30+y),255, 1);

				printDoubleOnImage(compositingVisu, "leftAngle", static_cast<int>(leftAngle), 180);
				printDoubleOnImage(compositingVisu, "rightAngle", static_cast<int>(rightAngle), 200);
			}

			// Shows it
			try
			{
			imshow("Visu", compositingVisu);
			}
			catch(cv::Exception& e)
			{
				e.formatMessage();
				std::cerr << e.msg << std::endl;
			}
		}
	}

}

bool NoTouchScreen::initVectorRecognition(std::vector<GestureSignature>& oGestures)
{
	const double PANRIGHT_THRESHOLD = 25.0;
	const double PANLEFT_THRESHOLD  = 25.0;
	const double ZOOMOUT_THRESHOLD  = 40.0;

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

	oGestures.push_back(GestureSignature("Pan Left", "OnLeftTranslation", panLeftFrames, PANLEFT_THRESHOLD));
	oGestures.push_back(GestureSignature("Pan Right", "OnRightTranslation", panRightFrames, PANRIGHT_THRESHOLD));
	oGestures.push_back(GestureSignature("Zoom Out", "", zoomOutFrames, ZOOMOUT_THRESHOLD));

	return true;
}
