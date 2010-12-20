#include "IoServices.h"

#include "config.h"
#ifdef WINDOWS
    #include "KeyStrokerWindows.h"
	#define NTS_IOSERVICES_KEYSTROKER KeyStrokerWindows
#endif

KeyStroker& IoServices::GetKeyStrokerInstance()
{
    static NTS_IOSERVICES_KEYSTROKER stroker;
    return stroker;
}
