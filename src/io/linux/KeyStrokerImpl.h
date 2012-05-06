/*
 * KeyStrokerLinux.h
 *
 *  Created on: 18 déc. 2010
 *      Author: canard
 */

#ifndef KEYSTROKERIMPL_H_
#define KEYSTROKERIMPL_H_

#include <vector>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include "KeyStroker.h"

class KeyStrokerImpl : public KeyStroker
{
public:
	KeyStrokerImpl();
	virtual ~KeyStrokerImpl();

protected:
	virtual void PressKey(Key iKey, bool iPress);

private:
	KeyStrokerImpl(KeyStrokerImpl const &);
	KeyStrokerImpl& operator= (KeyStrokerImpl const &);

	std::vector<unsigned int> m_KeyMap;
	Display * m_X11Display;
};

#endif /* KEYSTROKERIMPL_H_ */
