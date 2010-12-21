/*
 * KeystrokeAction.cpp
 *
 *  Created on: 21 déc. 2010
 *      Author: canard
 */

#include "KeystrokeAction.h"
#include "IoServices.h"


KeystrokeAction::KeystrokeAction(KeyStroker::Key iKey, bool iCtrl, bool iAlt, bool iShift) :
Action()
//,m_key({iKey,iCtrl,iAlt,iShift) # C++0x feature
{
	m_key.key = iKey;
	m_key.ctrl = iCtrl;
	m_key.alt = iAlt;
	m_key.shift = iShift;
}

KeystrokeAction::~KeystrokeAction()
{
}

void KeystrokeAction::Fire()
{
	IoServices::GetKeyStrokerInstance().StrokeKey(m_key.key, m_key.ctrl, m_key.alt, m_key.shift);
}
