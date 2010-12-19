/*
 * RotationDescriptor.cpp
 *
 *      Author: steren
 */
#include <cmath>

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
	return std::abs(m_angle - descriptor.getAngle());
}
