/*
 * NoTouchScreen.h
 *
 *  Created on: 16 déc. 2010
 *      Author: canard
 */

#ifndef NOTOUCHSCREEN_H_
#define NOTOUCHSCREEN_H_

#include "OpenCVLibs.h"

class NoTouchScreen {
public:
	NoTouchScreen();
	virtual ~NoTouchScreen();
	void MainLoop();
	cv::Mat& GetNextSilhouette(cv::VideoCapture& iCap);

private:
	NoTouchScreen(const NoTouchScreen&);
	NoTouchScreen& operator= (const NoTouchScreen&);
};

#endif /* NOTOUCHSCREEN_H_ */
