/*
 * GestureFrame.cpp
 *
 *      Author: steren
 */

#include "FrameDescriptorBundle.h"

FrameDescriptorBundle::FrameDescriptorBundle() : m_rotation() {}

FrameDescriptorBundle::FrameDescriptorBundle(const RotationDescriptor& iRotation) : m_rotation(iRotation) {}

FrameDescriptorBundle::~FrameDescriptorBundle() {
}

double FrameDescriptorBundle::compare(FrameDescriptorBundle& frameSignature) {
	return m_rotation.compare(frameSignature.m_rotation);
}
