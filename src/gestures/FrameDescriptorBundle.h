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
	// TODO : use a vector of Descriptors
	RotationDescriptor m_rotation;
	double m_rotImportance;
	RotationDescriptor m_leftRotation;
	double m_rotLeftImportance;
	RotationDescriptor m_rightRotation;
	double m_rotRightImportance;

public:
	FrameDescriptorBundle();
	FrameDescriptorBundle(const RotationDescriptor& rotation, double rotImportance, const RotationDescriptor& leftRotation, double rotLeftImportance, const RotationDescriptor& rightRotation, double rotRightImportance);
	virtual ~FrameDescriptorBundle();

	/**
	 * compare with another frame
	 * @return: distance between the two frames
	 */
	double compare(FrameDescriptorBundle& framesignature);
};

#endif /* GESTUREFRAME_H_ */
