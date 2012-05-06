#include "IoServices.h"
#include "KeyStrokerImpl.h"

KeyStroker& IoServices::GetKeyStrokerInstance()
{
    static KeyStrokerImpl stroker;
    return stroker;
}

