/*
 * ImageFifo.cpp
 *
 *      Author: Steren Giannini <steren.giannini@gmail.com>
 *      Author: Jean Bernard Jansen <jblecanard@gmail.com>
 */

#include "ImageFifo.h"


ImageFifo::ImageFifo(const int & iSize, cv::Mat iInitMat) : Fifo<cv::Mat>(iSize,iInitMat)
{
}

ImageFifo::~ImageFifo() {
}

void ImageFifo::pushImage(cv::VideoCapture & iCap)
{
	round();
	iCap >> getFirst();
}
