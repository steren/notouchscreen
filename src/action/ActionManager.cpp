/*
 * ActionManager.cpp
 *
 *  Created on: 21 déc. 2010
 *      Author: canard
 */

#include "ActionManager.h"

#include <iostream>
#include <fstream>
#include <boost/regex.hpp>
#include "Action.h"
#include "NoTouchScreenException.h"
#include "KeyStroker.h"
#include "KeystrokeAction.h"

ActionManager::ActionManager()
{
}

ActionManager::~ActionManager()
{
}

ActionManager& ActionManager::Instance()
{
	static ActionManager instance;
	return instance;
}

void ActionManager::FillRegisterWithConfigFile(const std::string& iFileName)
{
	std::ifstream ConfigFile(iFileName.c_str());
	if( ! ConfigFile.is_open())
		throw NoTouchScreenException("Configuration file not found.");

	std::string currentLine;
	while(std::getline(ConfigFile,currentLine))
	{
		static const boost::regex exp("(\\w+)\\s*->\\s*(Ctrl\\+)?(Alt\\+)?(Shift\\+)?(Right|Left|Up|Down)");
		//std::cout << boost::regex_match(currentLine,exp) << std::endl;
		boost::smatch matches;
		if(boost::regex_match(currentLine,matches,exp))
		{
			KeystrokeAction_var action(new KeystrokeAction());

			if(matches[2] == "Ctrl")
				action->AddKey(KeyStroker::Ctrl);

			if(matches[3] == "Alt")
				action->AddKey(KeyStroker::Alt);

			if(matches[4] == "Shift")
				action->AddKey(KeyStroker::Shift);

			if(0 == matches[5].compare("Right"))
				action->AddKey(KeyStroker::Right);

			if(0 == matches[5].compare("Left"))
				action->AddKey(KeyStroker::Left);

			if(0 == matches[5].compare("Up"))
				action->AddKey(KeyStroker::Up);

			if(0 == matches[5].compare("Down"))
				action->AddKey(KeyStroker::Down);

			m_Register[matches[1]] = action;
		}
	}
}

void ActionManager::RegisterActionOnEvent(const Event& iEvent,Action_var iAction)
{
	m_Register[iEvent] = iAction;
}

void ActionManager::SendEvent(const Event& iEvent)
{
	Action_var action = m_Register[iEvent];
	if( action )
		action->Fire();
}
