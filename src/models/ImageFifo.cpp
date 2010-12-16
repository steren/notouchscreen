/*
 * ImageFifo.cpp
 *
 *      Author: Steren Giannini <steren.giannini@gmail.com>
 *      Author: Jean Bernard Jansen <jblecanard@gmail.com>
 */

#include "ImageFifo.h"


ImageFifo::ImageFifo(const int & iSize, const int& iWidth, const int& iHeight)
{
	m_pointers.resize(iSize);
	m_images = new cv::Mat[iSize];
	for(unsigned int i=0; i < iSize; i++)
	{
		cv::Mat mat(iHeight,iWidth,CV_8UC1);
		m_images[i] = mat;
		m_pointers.assign(i,i);
	}
}

ImageFifo::~ImageFifo() {
	delete [] m_images;
}

cv::Mat & ImageFifo::getFirst() const
{
	return m_images[m_pointers.front()];
}

cv::Mat & ImageFifo::getLast() const
{
	return m_images[m_pointers.back()];
}

std::list<int>::const_iterator ImageFifo::getBegin() const
{
	return m_pointers.begin();
}

std::list<int>::const_iterator ImageFifo::getEnd() const
{
	return m_pointers.end();
}

void ImageFifo::pushImage(cv::VideoCapture & iCap)
{
	round();
	iCap >> getFirst();
}

void ImageFifo::round()
{
	m_pointers.push_front(m_pointers.back());
	m_pointers.pop_back();
}
