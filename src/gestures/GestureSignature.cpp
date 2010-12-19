/*
 * GestureModel.cpp
 *
 *      Author: steren
 */

#include <GestureSignature.h>

GestureSignature::GestureSignature(std::string name, std::vector<FrameDescriptorBundle> frames) {
	m_name = name;
	m_frames = frames;
}

GestureSignature::GestureSignature() {
	m_name = "Empty";
	m_frames = std::vector<FrameDescriptorBundle>();
}

GestureSignature::~GestureSignature() {
}

double GestureSignature::compare(Fifo<FrameDescriptorBundle>& framesToCompare) {
	int size1 = m_frames.size();
	int size2 = framesToCompare.size();

	if(m_frames.size() != framesToCompare.size()) {
		return 100000.0; // TODO = infinity
	}

	double distance = 0;
	// TODO : this may not be the ideal way to compare things
	for( int i = 0; i < m_frames.size(); i++ ) {
		distance += m_frames[i].compare(framesToCompare.get(i));
	}

	return distance;
}

