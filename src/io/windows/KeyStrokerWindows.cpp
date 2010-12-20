#include "KeyStrokerWindows.h"
#ifdef WINDOWS

KeyStrokerWindows::KeyStrokerWindows()
{
    m_KeyMap.push_back(VK_LEFT);
    m_KeyMap.push_back(VK_RIGHT);
    m_KeyMap.push_back(VK_UP);
    m_KeyMap.push_back(VK_DOWN);
}

KeyStrokerWindows::~KeyStrokerWindows()
{
}

/** @brief (implements KeyStroker::StrokeKey)
  *
  */
void KeyStrokerWindows::StrokeKey(KeyStroker::Key iKey, bool iCtrl, bool iAlt, bool iShift)
{
    m_Cpt = 0;
    ZeroMemory(m_Input, sizeof m_Input);

    if (iShift)
    	PushKey(VK_SHIFT);

    if (iCtrl)
    	PushKey(VK_CONTROL);

    if (iAlt)
    	PushKey(VK_MENU);

    PushKey(m_KeyMap[iKey]);
    PushKey(m_KeyMap[iKey], false);

    if (iShift)
    	PushKey(VK_SHIFT, false);

    if (iCtrl)
    	PushKey(VK_CONTROL, false);

    if (iAlt)
    	PushKey(VK_MENU, false);

    SendInput(m_Cpt, m_Input, sizeof INPUT);
}

void KeyStrokerWindows::PushKey(unsigned int iVirtualKeyCode,bool iPress)
{
	m_Input[m_Cpt].type = INPUT_KEYBOARD;
	m_Input[m_Cpt].ki.wVk = iVirtualKeyCode;
	m_Input[m_Cpt].ki.wScan = MapVirtualKey(iVirtualKeyCode, 0);
	if(!iPress)
		m_Input[m_Cpt].ki.dwFlags = KEYEVENTF_KEYUP;

	m_Cpt++;
}

#endif
