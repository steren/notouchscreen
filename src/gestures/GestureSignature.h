/*
 * GestureModel.h
 *
 *      Author: steren
 */

#include <string>
#include <vector>
#include "FrameDescriptorBundle.h"
#include "Fifo.hpp"
#include "Event.h"

#ifndef GESTURESIGNATURE_H_
#define GESTURESIGNATURE_H_

class GestureSignature {

private:
	double m_threshold;
	Event m_eventToThrow;
	std::string m_name;
	std::vector<FrameDescriptorBundle> m_frames;

public:
	GestureSignature();
	GestureSignature(
			const std::string& iName,
			const Event& iEventToThrow,
			std::vector<FrameDescriptorBundle> iFrames,
			double iThreshold = 20);

	virtual ~GestureSignature();

	const std::string& getName() const;
	const FrameDescriptorBundle& get(unsigned int iIndex) const;
	double getThreshold() const;
	void FireEvent();

	/**
	 * compare two signatures
	 * @return: the distance between these two signatures
	 */
	double compare(Fifo<FrameDescriptorBundle>& frames);
};

#endif /* GESTURESIGNATURE_H_ */
