
#pragma once


#include "updater_interface.h"
#include <cynetwork.h>


#define COMPUTE_UID(a,b)({a << 4 | b;})

class Updater : public UpdaterInterface
{
    private:

    std::vector<CyIhb*> *ihbs;
    bool remove_baseline;
    uint32_t steps_baseline;

    std::vector<skin_data> baseline;
            
    public:

    Updater(std::vector<CyIhb *> *_ihbs, double _T, bool _remove_baseline);
    void init();
    void updateOnce();
};