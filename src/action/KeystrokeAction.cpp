/*
 * KeystrokeAction.cpp
 *
 *  Created on: 21 déc. 2010
 *      Author: canard
 */

#include "KeystrokeAction.h"
#include "IoServices.h"


KeystrokeAction::KeystrokeAction() : Action()
{
}

KeystrokeAction::~KeystrokeAction()
{
}

void KeystrokeAction::AddKey(const KeyStroker::Key& iKey)
{
	m_keys.push_back(iKey);
}

void KeystrokeAction::Fire()
{
	IoServices::GetKeyStrokerInstance().StrokeKeys(m_keys);
}
