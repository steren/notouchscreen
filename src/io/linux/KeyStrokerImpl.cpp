/*
 * KeyStrokerImpl.cpp, linux version
 *
 *  Created on: 18 déc. 2010
 *      Author: JB Jansen
 */

#include "KeyStrokerImpl.h"

#include <X11/extensions/XTest.h>
#include <iostream>
#include "NoTouchScreenException.h"

KeyStrokerImpl::KeyStrokerImpl() : KeyStroker() {
	m_X11Display = XOpenDisplay(NULL);
	if( NULL == m_X11Display)
		throw NoTouchScreenException("X11 display cannot be opened.");

	m_KeyMap.reserve(NumberOfKeys);
	m_KeyMap[Left] = XK_Left;
	m_KeyMap[Right] = XK_Right;
	m_KeyMap[Up] = XK_Up;
	m_KeyMap[Down] = XK_Down;
	m_KeyMap[Ctrl] = XK_Control_L;
	m_KeyMap[Alt] = XK_Alt_L;
	m_KeyMap[Shift] = XK_Shift_L;
}

KeyStrokerImpl::~KeyStrokerImpl() {
	Clean();
	XCloseDisplay(m_X11Display);
}

void KeyStrokerImpl::PressKey(Key iKey, bool iPress)
{
	unsigned int keycode = XKeysymToKeycode(m_X11Display, m_KeyMap[iKey]);
	XTestFakeKeyEvent(m_X11Display, keycode, iPress ? True : False, 0);
	XFlush(m_X11Display);
}

