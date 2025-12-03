
#pragma once


#include "updater_interface.h"
#include <cynetwork.h>


#define COMPUTE_UID(a,b)({a << 4 | b;})

class UpdaterFake : public UpdaterInterface
{
    private:

    std::vector<CyIhb*> *ihbs;
            
    public:

    UpdaterFake(double T);
    void init();
    void updateOnce();
};