/*
 * KeyStroker.cpp
 *
 *  Created on: 18 déc. 2010
 *      Author: canard
 */

#include "KeyStroker.h"
#include "config.h"

#ifdef WINDOWS
#include <windows.h>
#endif
#ifdef LINUX
	#include <iostream>
	#include <X11/extensions/XTest.h>
	#include <unistd.h>
#endif

KeyStroker::KeyStroker() {

#ifdef LINUX
	m_X11Display = XOpenDisplay(NULL);
#endif
}

KeyStroker::~KeyStroker() {

#ifdef LINUX
	XCloseDisplay(m_X11Display);
#endif
}

void KeyStroker::StrokeKey(KeyStroker::Key iKey, bool iCtrl, bool iAlt, bool iShift)
{

#ifdef WINDOWS
#endif

#ifdef LINUX
	unsigned int keycode = XKeysymToKeycode(m_X11Display, iKey);

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
#endif

}
