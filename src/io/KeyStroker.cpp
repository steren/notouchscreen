/*
 * KeyStroker is an interface : no implementation in there.
 */

#include "KeyStroker.h"

#include "utils/BoostForeach.h"

KeyStroker::KeyStroker(){}
KeyStroker::~KeyStroker(){
};

void KeyStroker::Clean()
{
	for(unsigned int i=0; i < NumberOfKeys; i++)
		PressKey(static_cast<Key>(i),false);
}

void KeyStroker::StrokeKeys(std::vector<Key> iKeys)
{
	foreach(Key& key,iKeys)
		PressKey(key,true);

	reverse_foreach(Key& key,iKeys)
		PressKey(key,false);
}
