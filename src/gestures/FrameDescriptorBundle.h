/*
 * GestureFrame.h
 *
 *      Author: steren
 */

#include "RotationDescriptor.h"

#ifndef GESTUREFRAME_H_
#define GESTUREFRAME_H_

class FrameDescriptorBundle {
private:
	RotationDescriptor m_rotation;

public:
	FrameDescriptorBundle();
	FrameDescriptorBundle(const RotationDescriptor& rotation);
	virtual ~FrameDescriptorBundle();

	/**
	 * compare with another frame
	 * @return: distance between the two frames
	 */
	double compare(FrameDescriptorBundle& framesignature);
};

#endif /* GESTUREFRAME_H_ */
