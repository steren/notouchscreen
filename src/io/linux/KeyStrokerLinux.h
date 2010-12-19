/*
 * KeyStrokerLinux.h
 *
 *  Created on: 18 déc. 2010
 *      Author: canard
 */

#ifndef KEYSTROKERLINUX_H_
#define KEYSTROKERLINUX_H_



#include "config.h"
#ifdef LINUX

#include <vector>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include "KeyStroker.h"

class KeyStrokerLinux : public KeyStroker
{
public:
	KeyStrokerLinux();
	virtual ~KeyStrokerLinux();
	virtual void StrokeKey(KeyStroker::Key iKey, bool iCtrl = false, bool iAlt = false, bool iShift = false);

private:
	KeyStrokerLinux(const KeyStrokerLinux&);
	KeyStrokerLinux& operator= (const KeyStrokerLinux&);

	std::vector<unsigned int> m_KeyMap;
	Display * m_X11Display;
};

#endif
#endif /* KEYSTROKER_H_ */
