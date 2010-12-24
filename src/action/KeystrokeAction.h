/*
 * KeystrokeAction.h
 *
 *  Created on: 21 déc. 2010
 *      Author: canard
 */

#ifndef KEYSTROKEACTION_H_
#define KEYSTROKEACTION_H_

#include "Action.h"
#include "KeyStroker.h"
#include <vector>
#include <boost/shared_ptr.hpp>

class KeystrokeAction : public Action
{
public:
	KeystrokeAction();
	virtual ~KeystrokeAction();

	void AddKey(const KeyStroker::Key& iKey);
	virtual void Fire();

private:
	KeystrokeAction(const KeystrokeAction&);
	KeystrokeAction& operator=(const KeystrokeAction&);

	std::vector<KeyStroker::Key> m_keys;
};

typedef boost::shared_ptr<KeystrokeAction> KeystrokeAction_var;

#endif /* KEYSTROKEACTION_H_ */
