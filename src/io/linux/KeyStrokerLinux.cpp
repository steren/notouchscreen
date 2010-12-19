/*
 * KeyStrokerLinux.cpp
 *
 *  Created on: 18 déc. 2010
 *      Author: canard
 */

#include "KeyStrokerLinux.h"

#include "config.h"
#ifdef LINUX

#include <X11/extensions/XTest.h>
#include "NoTouchScreenException.h"

KeyStrokerLinux::KeyStrokerLinux() : KeyStroker() {
	m_X11Display = XOpenDisplay(NULL);
	if( NULL == m_X11Display)
		throw NoTouchScreenException("X11 display cannot be opened.");

	m_KeyMap.push_back(XK_Left);
	m_KeyMap.push_back(XK_Right);
	m_KeyMap.push_back(XK_Up);
	m_KeyMap.push_back(XK_Down);
}

KeyStrokerLinux::~KeyStrokerLinux() {
	XCloseDisplay(m_X11Display);
}

void KeyStrokerLinux::StrokeKey(KeyStroker::Key iKey, bool iCtrl, bool iAlt, bool iShift)
{
	unsigned int keycode = XKeysymToKeycode(m_X11Display, m_KeyMap[iKey]);

	unsigned int KeyCtrl = XKeysymToKeycode(m_X11Display, XK_Control_L);
	unsigned int KeyAlt = XKeysymToKeycode(m_X11Display, XK_Alt_L);
	unsigned int KeyShift = XKeysymToKeycode(m_X11Display, XK_Shift_L);

	if(iCtrl)
		XTestFakeKeyEvent(m_X11Display, KeyCtrl, True, 0);

	if(iAlt)
		XTestFakeKeyEvent(m_X11Display, KeyAlt, True, 0);

	if(iShift)
		XTestFakeKeyEvent(m_X11Display, KeyShift, True, 0);

	XTestFakeKeyEvent(m_X11Display, keycode, True, 0);
	XTestFakeKeyEvent(m_X11Display, keycode, False, 0);

	if(iCtrl)
		XTestFakeKeyEvent(m_X11Display, KeyCtrl, False, 0);

	if(iAlt)
		XTestFakeKeyEvent(m_X11Display, KeyAlt, False, 0);

	if(iShift)
		XTestFakeKeyEvent(m_X11Display, KeyShift, False, 0);

	XFlush(m_X11Display);
}

#endif
