#ifndef KEYSTROKERWINDOWS_H_
#define KEYSTROKERWINDOWS_H_

#include <windows.h>
#include <vector>
#include "KeyStroker.h"

class KeyStrokerImpl : public KeyStroker
{
public:
    KeyStrokerImpl();
    virtual ~KeyStrokerImpl();

    /** @see KeyStroker::StrokeKey() */

protected:
    virtual void PressKey(Key iKey, bool iPress);

private:
	KeyStrokerImpl(KeyStrokerImpl const &);
	KeyStrokerImpl& operator= (KeyStrokerImpl const &);
    void PushKey(unsigned int iVirtualKeyCode,bool iPress = true);

    std::vector<unsigned int> m_KeyMap;
    INPUT m_Input[256];
    unsigned int m_Cpt;
};

#endif
