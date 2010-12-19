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
	#include <X11/Xlib.h>
	#include <X11/keysym.h>
	#include <X11/extensions/XTest.h>
	#include <unistd.h>
#endif

KeyStroker::KeyStroker() {
}

KeyStroker::~KeyStroker() {
}

void KeyStroker::StrokeKey(const char * iInput)
{
#ifdef WINDOWS
#endif
#ifdef LINUX

	Display *display;
	unsigned int keycode;
	display = XOpenDisplay(NULL);
	keycode = XKeysymToKeycode(display, XK_A);
	for(;;)
	{
		usleep(3000*1000);
		XTestFakeKeyEvent(display, keycode, True, 0);
		XTestFakeKeyEvent(display, keycode, False, 0);
		XFlush(display);
	}
#endif
}
