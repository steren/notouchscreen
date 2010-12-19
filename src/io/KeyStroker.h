/*
 * KeyStroker.h
 *
 *  Created on: 18 déc. 2010
 *      Author: canard
 */

#ifndef KEYSTROKER_H_
#define KEYSTROKER_H_

class KeyStroker {
public:
	virtual ~KeyStroker();
	static void StrokeKey(const char * iInput);

private:
	KeyStroker();
	KeyStroker(const KeyStroker&);
	KeyStroker& operator= (const KeyStroker&);
};

#endif /* KEYSTROKER_H_ */
