#include "KeyStrokerWindows.h"
#ifdef WINDOWS

KeyStrokerWindows::KeyStrokerWindows() : KeyStroker()
{
	m_KeyMap.reserve(NumberOfKeys);
	m_KeyMap[Left] = VK_LEFT;
	m_KeyMap[Right] = VK_RIGHT;
	m_KeyMap[Up] = VK_UP;
	m_KeyMap[Down] = VK_DOWN;
	m_KeyMap[Ctrl] = VK_CONTROL;
	m_KeyMap[Alt] = VK_MENU;
	m_KeyMap[Shift] = VK_SHIFT;
}

KeyStrokerWindows::~KeyStrokerWindows()
{
	Clean();
}

void KeyStrokerWindows::PressKey(Key iKey, bool iPress);
{
    m_Cpt = 0;
    ZeroMemory(m_Input, sizeof m_Input);
    PushKey(m_KeyMap[iKey], iPress);
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