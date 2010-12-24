/*
 * KeyStroker.h
 *
 *  Created on: 18 déc. 2010
 *      Author: canard
 */

#ifndef KEYSTROKER_H_
#define KEYSTROKER_H_

#include "config.h"
#ifdef WINDOWS
#endif
#ifdef LINUX
	#include <X11/Xlib.h>
	#include <X11/keysym.h>
#endif

#include <vector>

class KeyStroker {
public:
	enum Key
	{
		Left,
		Right,
		Up,
		Down,
		Ctrl,
		Shift,
		Alt,
		NumberOfKeys
	};

	virtual ~KeyStroker();
	void StrokeKeys( std::vector<Key> iKeys);

protected:
	KeyStroker();
	void Clean();
	virtual void PressKey(Key iKey, bool iPress) = 0;

private:
	KeyStroker(const KeyStroker&);
	KeyStroker& operator= (const KeyStroker&);
};

#endif /* KEYSTROKER_H_ */
