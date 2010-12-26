/*
 * NoTouchScreen.h
 *
 *  Created on: 16 déc. 2010
 *      Author: canard
 */

#ifndef NOTOUCHSCREEN_H_
#define NOTOUCHSCREEN_H_

#include "OpenCVLibs.h"
#include "GestureSignature.h"

#define NTS_SILHOUETTE_THRESHOLD 20.0
#define NTS_SILHOUETTE_VALUE 255

class NoTouchScreen {
public:
	NoTouchScreen();
	virtual ~NoTouchScreen();

	/**
	 * Main program loop
	 *
	 * Contains the infinite loop that compute and detext the movement
	 */
	void MainLoop();

private:
	NoTouchScreen(const NoTouchScreen&);
	NoTouchScreen& operator= (const NoTouchScreen&);

	/**
	 * Get the next silhouette from video stream
	 *
	 * The methode stores a frame from the stream and computes the silhouette with the previous one.
	 * @param iCap The OpenCV video capture device. MUST be opened().
	 */
	cv::Mat& GetNextSilhouette(cv::VideoCapture& iCap);

	static const int SCORE_FRAMES 	= 20;
	void processVectorRecognition(cv::Mat& silhouette,bool iShowCompositingVisu = false);
	bool initVectorRecognition(std::vector<GestureSignature>& oGestures);

	void printDoubleOnImage(cv::Mat image, std::string name, int number, unsigned int y);
};

#endif /* NOTOUCHSCREEN_H_ */
