/*
 * NoTouchScreen.cpp
 *
 *  Created on: 16 déc. 2010
 *      Author: canard
 */

#include "NoTouchScreen.h"

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

		Scalar t(0);
		Mat empty(currentCap.size(),currentCap.type(),t);
		frames[0] = empty.clone();
		frames[1] = empty.clone();

		Mat silhouette;
		for(;;)
		{
			Mat silhouette = GetNextSilhouette(cap1);
			imshow("Visu",silhouette);
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
	static Mat gray;
	cvtColor( currentCap, gray, CV_BGR2GRAY );

//	iCap >> currentCap;
//	std::vector<Mat> channels;
//	split(currentCap,channels);

	static Mat frames[2] = {gray.clone(), gray.clone()};
	static unsigned int currentFrame = 0;
	unsigned int nextFrame = (currentFrame+1)%2;

	// Computing silhouette
	static Mat diff;
	gray.copyTo(frames[currentFrame]);
	absdiff(frames[currentFrame],frames[nextFrame],diff);

	static Mat silhouette;
	threshold(diff, silhouette, 100., 255,THRESH_BINARY);

	currentFrame = nextFrame;
	return silhouette;
}
