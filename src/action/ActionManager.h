/*
 * ActionManager.h
 *
 *  Created on: 21 déc. 2010
 *      Author: canard
 */

#ifndef ACTIONMANAGER_H_
#define ACTIONMANAGER_H_

#include <map>
#include <string>

#include "Action.h"
#include "Event.h"

class ActionManager {
public:
	virtual ~ActionManager();
	static ActionManager& Instance();

	/** @brief Loads the configuration file
	 *
	 * This method parses the configuration file and registers
	 * corresponding actions.
	 */
	void FillRegisterWithConfigFile(const std::string& iFileName);

	/** @brief tells the manager a event occured
	 *
	 * The corresponding actions (if any) are immediately executed.
	 */
	void SendEvent(const Event& iEvent);

private:
	ActionManager();
	ActionManager(const ActionManager&);
	ActionManager& operator= (const ActionManager&);

	typedef std::map<Event,Action_var> RegisterType;
	typedef RegisterType::value_type RegisterValueType;
	RegisterType m_Register;
};

#endif /* ACTIONMANAGER_H_ */
