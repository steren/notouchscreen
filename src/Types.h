#ifndef TYPES_H_
#define TYPES_H_

#include <vector>

#define NTS_DeclareClassTypes(Class) \
	typedef Class * Class##_ptr; \
	typedef std::vector<Class##_ptr> Class##_vec; \
	typedef std::vector<Class##_ptr>::iterator Class##_viter


#endif
