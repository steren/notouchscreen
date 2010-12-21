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

class KeystrokeAction : public Action
{
public:
	KeystrokeAction(KeyStroker::Key iKey, bool iCtrl = false, bool iAlt = false, bool iShift = false);
	KeystrokeAction(const KeystrokeAction&);
	virtual ~KeystrokeAction();

	virtual void Fire();

private:
	KeyStroker::KeyID m_key;
};

#endif /* KEYSTROKEACTION_H_ */
