/*
 * ImageFifo.h
 *
 *      Author: Steren Giannini <steren.giannini@gmail.com>
 *      Author: Jean Bernard Jansen <jblecanard@gmail.com>
 */

#ifndef IMAGEFIFO_H_
#define IMAGEFIFO_H_

#include <list>
#include <vector>
#include <cv.h>
#include <cv.hpp>
#include <highgui.h>
#include <highgui.hpp>

class ImageFifo {
public:
	ImageFifo(const int& iSize, const int& iWidth, const int& iHeight);
	virtual ~ImageFifo();

	cv::Mat& getFirst() const;
	cv::Mat& getLast() const;

	std::list<int>::const_iterator getBegin() const;
	std::list<int>::const_iterator getEnd() const;

	void pushImage(cv::VideoCapture& iCap);

private:
	void round();

	std::list<int> m_pointers;
	cv::Mat * m_images;
};


#endif /* IMAGEFIFO_H_ */
