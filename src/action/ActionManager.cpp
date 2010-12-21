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
			KeyStroker::Key key = KeyStroker::RightKey;
			if(0 == matches[5].compare("Right"))
				key = KeyStroker::RightKey;

			if(0 == matches[5].compare("Left"))
				key = KeyStroker::LeftKey;

			if(0 == matches[5].compare("Up"))
				key = KeyStroker::UpKey;

			if(0 == matches[5].compare("Down"))
				key = KeyStroker::DownKey;

			Action_var action(new KeystrokeAction(
					key,
					matches[2].length() > 0,
					matches[3].length() > 0,
					matches[4].length() > 0));

			m_Register[matches[1]] = action;
		}
	}
}

void ActionManager::SendEvent(const Event& iEvent)
{
	Action_var action = m_Register[iEvent];
	if( action )
		action->Fire();
}
