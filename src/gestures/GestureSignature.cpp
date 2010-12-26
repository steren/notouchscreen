/*
 * GestureModel.cpp
 *
 *      Author: steren
 */

#include "GestureSignature.h"
#include "ActionManager.h"

GestureSignature::GestureSignature(
		const std::string& iName,
		const Event& iEventToThrow,
		std::vector<FrameDescriptorBundle> iFrames,
		double iThreshold)
: m_name(iName),
  m_eventToThrow(iEventToThrow),
  m_frames(iFrames),
  m_threshold(iThreshold)
{
}

GestureSignature::GestureSignature() : m_name("Empty"), m_eventToThrow("")
{
}

GestureSignature::~GestureSignature() {
}

const std::string& GestureSignature::getName() const
{
	return m_name;
}

const FrameDescriptorBundle& GestureSignature::get(unsigned int iIndex) const
{
	return m_frames[iIndex];
}

double GestureSignature::getThreshold() const
{
	return m_threshold;
}

void GestureSignature::FireEvent()
{
	ActionManager::Instance().SendEvent(m_eventToThrow);
}

double GestureSignature::compare(Fifo<FrameDescriptorBundle>& framesToCompare) {
	int size1 = m_frames.size();
	int size2 = framesToCompare.size();

	if(m_frames.size() != framesToCompare.size()) {
		return 100000.0; // TODO = infinity
	}

	double distance = 0;
	// TODO : this may not be the ideal way to compare things
	for( unsigned int i = 0; i < m_frames.size(); i++ ) {
		distance += m_frames[i].compare(framesToCompare.get(i));
	}

	return distance;
}

