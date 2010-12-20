#include "IoServices.h"

#include "config.h"
#ifdef WINDOWS
    #include "KeyStrokerWindows.h"
#endif

KeyStroker& IoServices::GetKeyStrokerInstance()
{
    #ifdef WINDOWS
    static KeyStrokerWindows stroker;
    #endif

    return stroker;
}
