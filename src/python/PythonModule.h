/*
 * PythonConfigLoader.h
 *
 *  Created on: 24 déc. 2010
 *      Author: canard
 */

#ifndef PYTHONMODULE_H_
#define PYTHONMODULE_H_

#include <string>
#include <boost/regex.hpp>
#include "Event.h"

class PythonModule {
public:
	PythonModule();
	virtual ~PythonModule();

	std::string getNum();
	void addActionOnEvent(const Event& iEvent,const std::string& iKeyboardSerie);
};

#endif /* PYTHONCONFIGLOADER_H_ */
