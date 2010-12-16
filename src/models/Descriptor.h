/*
 * Descriptor.h
 *
 *  Created on: 16 déc. 2010
 *      Author: canard
 */

#ifndef DESCRIPTOR_H_
#define DESCRIPTOR_H_

#include "Types.h"

class Descriptor {
public:
	Descriptor();
	virtual ~Descriptor();
};

NTS_DeclareClassTypes(Descriptor);

#endif /* DESCRIPTOR_H_ */
