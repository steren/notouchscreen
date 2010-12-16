/*
 * CompositeDesc.h
 *
 *  Created on: 16 déc. 2010
 *      Author: canard
 */

#ifndef COMPOSITEDESC_H_
#define COMPOSITEDESC_H_

#include "Descriptor.h"

class CompositeDesc : public Descriptor {
public:
	CompositeDesc(unsigned int iNbDesc = 1);

	virtual ~CompositeDesc();

	void addDescriptor(Descriptor_ptr ipDesc);

private:
	CompositeDesc(const CompositeDesc&);
	CompositeDesc& operator = (const CompositeDesc&);

	Descriptor_vec m_descs;
};

#endif /* COMPOSITEDESC_H_ */
