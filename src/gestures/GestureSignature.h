/*
 * GestureModel.h
 *
 *      Author: steren
 */

#include <string>
#include <vector>
#include "FrameDescriptorBundle.h"
#include "Fifo.hpp"

#ifndef GESTURESIGNATURE_H_
#define GESTURESIGNATURE_H_

class GestureSignature {

private:
	std::string m_name;
	std::vector<FrameDescriptorBundle> m_frames;

public:
	GestureSignature();
	GestureSignature(std::string name, std::vector<FrameDescriptorBundle> frames);
	virtual ~GestureSignature();

	/**
	 * compare two signatures
	 * @return: the distance between these two signatures
	 */
	double compare(Fifo<FrameDescriptorBundle>& frames);
};

#endif /* GESTURESIGNATURE_H_ */
