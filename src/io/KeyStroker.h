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

class KeyStroker {
public:
	enum Key
	{
		LeftKey,
		RightKey,
		UpKey,
		DownKey
	};

	typedef struct keyid
	{
		Key key;
		bool ctrl;
		bool alt;
		bool shift;
	} KeyID;

	virtual ~KeyStroker();

	/**
	 * Stroke a key.
	 * iCtrl, iAlt and iShift is for using combos with left ctrl, left alt and left shift.
	 */
	virtual void StrokeKey(KeyStroker::Key iKey, bool iCtrl = false, bool iAlt = false, bool iShift = false) = 0;

protected:
	KeyStroker();

private:
	KeyStroker(const KeyStroker&);
	KeyStroker& operator= (const KeyStroker&);
};

#endif /* KEYSTROKER_H_ */
