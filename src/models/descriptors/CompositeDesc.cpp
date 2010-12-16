/*
 * CompositeDesc.cpp
 *
 *  Created on: 16 déc. 2010
 *      Author: canard
 */

#include "CompositeDesc.h"

CompositeDesc::CompositeDesc(unsigned int iNbDesc) {
	m_descs.resize(iNbDesc);
}

CompositeDesc::~CompositeDesc() {
}

void CompositeDesc::addDescriptor(Descriptor_ptr ipDesc)
{
	m_descs.push_back(ipDesc);
}
