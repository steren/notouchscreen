/*
 * KeyStrockerMain.cpp
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
	#include <X11/Xlib.h>
	#include <iostream>
	#include <X11/extensions/XTest.h>
	#include <unistd.h>
#endif

int main(int argc, char * argv[])
{
	KeyStroker stroker;

#ifdef LINUX
	// This snippet uses the shorcut Ctrl + Alt + Direction
	// to change the desktop on gnome.
	for(;;)
	{
		usleep(3000000);
		stroker.StrokeKey(KeyStroker::RightKey,true,true);
		usleep(3000000);
		stroker.StrokeKey(KeyStroker::LeftKey,true,true);
	}
#endif

	return 0;
}
