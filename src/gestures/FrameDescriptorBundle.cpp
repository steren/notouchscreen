/*
 * GestureFrame.cpp
 *
 *      Author: steren
 */

#include "FrameDescriptorBundle.h"

FrameDescriptorBundle::FrameDescriptorBundle() : m_rotation(), m_rightRotation(), m_leftRotation() {}

FrameDescriptorBundle::FrameDescriptorBundle(const RotationDescriptor& rotation, double rotImportance, const RotationDescriptor& leftRotation, double rotLeftImportance, const RotationDescriptor& rightRotation, double rotRightImportance) :
		m_rotation(rotation),
		m_rotImportance(rotImportance),
		m_leftRotation(leftRotation),
		m_rotLeftImportance(rotLeftImportance),
		m_rightRotation(rightRotation),
		m_rotRightImportance(rotRightImportance)
		{}

FrameDescriptorBundle::~FrameDescriptorBundle() {
}

double FrameDescriptorBundle::compare(FrameDescriptorBundle& frameSignature) {
	return m_rotImportance * m_rotation.compare(frameSignature.m_rotation) +
			m_rotLeftImportance * m_leftRotation.compare(frameSignature.m_leftRotation) +
			m_rotRightImportance * m_rightRotation.compare(frameSignature.m_rightRotation);
}
