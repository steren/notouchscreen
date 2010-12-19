/*
 * RotationDescriptor.h
 *
 *      Author: steren
 */

#ifndef ROTATIONDESCRIPTOR_H_
#define ROTATIONDESCRIPTOR_H_

class RotationDescriptor {
private:
	double m_angle;

public:
	RotationDescriptor();
	RotationDescriptor( double angle );
	RotationDescriptor( const RotationDescriptor& descriptor );

	virtual ~RotationDescriptor();

	double getAngle() { return m_angle; }

	/**
	 * Compare
	 * @return : distance
	 */
	double compare(RotationDescriptor& descriptor);
};

#endif /* ROTATIONDESCRIPTOR_H_ */
