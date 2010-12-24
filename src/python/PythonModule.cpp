/*
 * PythonConfigLoader.cpp
 *
 *  Created on: 24 déc. 2010
 *      Author: canard
 */

#include "PythonModule.h"
#include <iostream>
#include "KeystrokeAction.h"
#include "ActionManager.h"

PythonModule::PythonModule() {
}

PythonModule::~PythonModule() {
}

std::string PythonModule::getNum()
{
	return std::string("Roger");
}

void PythonModule::addActionOnEvent(const Event& iEvent,const std::string& iKeyboardSerie)
{
	static const boost::regex exp("(Ctrl\\+)?(Alt\\+)?(Shift\\+)?(Right|Left|Up|Down)");
	boost::smatch matches;
	if(boost::regex_match(iKeyboardSerie,matches,exp))
	{
		KeystrokeAction_var action(new KeystrokeAction());

		if(matches[1] > 0)
			action->AddKey(KeyStroker::Ctrl);

		if(matches[2] > 0)
			action->AddKey(KeyStroker::Alt);

		if(matches[3] > 0)
			action->AddKey(KeyStroker::Shift);

		if(0 == matches[4].compare("Right"))
			action->AddKey(KeyStroker::Right);

		if(0 == matches[4].compare("Left"))
			action->AddKey(KeyStroker::Left);

		if(0 == matches[4].compare("Up"))
			action->AddKey(KeyStroker::Up);

		if(0 == matches[4].compare("Down"))
			action->AddKey(KeyStroker::Down);

		ActionManager::Instance().RegisterActionOnEvent(iEvent,action);
	}
}
