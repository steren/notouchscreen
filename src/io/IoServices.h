#ifndef IOSERVICES_H
#define IOSERVICES_H

#include "KeyStroker.h"

class IoServices
{
    public:
        static KeyStroker& GetKeyStrokerInstance();

    private:
        IoServices();
        virtual ~IoServices();
        IoServices(const IoServices& other);
        IoServices& operator=(const IoServices& other);
};

#endif // IOSERVICES_H
