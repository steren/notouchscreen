/*
 * RotationDescriptor.cpp
 *
 *      Author: steren
 */
#include <cmath>
#include <algorithm>

#include "RotationDescriptor.h"

RotationDescriptor::RotationDescriptor() {
	m_angle = 0;
}

RotationDescriptor::RotationDescriptor( double iAngle ) {
	m_angle = iAngle;
}

RotationDescriptor::RotationDescriptor( const RotationDescriptor& descriptor ) {
	m_angle = descriptor.m_angle;
}

RotationDescriptor::~RotationDescriptor() {}

double RotationDescriptor::compare(RotationDescriptor& descriptor) {

	// as we are on a circle (0 = 360) take the minimum distance.
	double dist = std::abs(m_angle - descriptor.getAngle());
	return std::min(dist, 360.0 - dist);
}
