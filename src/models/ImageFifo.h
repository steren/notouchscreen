/*
 * ImageFifo.h
 *
 *      Author: Steren Giannini <steren.giannini@gmail.com>
 *      Author: Jean Bernard Jansen <jblecanard@gmail.com>
 */

#ifndef IMAGEFIFO_H_
#define IMAGEFIFO_H_

#include "Types.h"
#include "Fifo.hpp"
#include "OpenCVLibs.h"

#include <list>
#include <vector>

class ImageFifo : public Fifo<cv::Mat> {
public:
	ImageFifo(const int& iSize, cv::Mat iInit);
	virtual ~ImageFifo();
	void pushImage(cv::VideoCapture& iCap);

private:
	ImageFifo(const ImageFifo&);
	ImageFifo& operator= (const ImageFifo&);
};

NTS_DeclareClassTypes(ImageFifo);


#endif /* IMAGEFIFO_H_ */
