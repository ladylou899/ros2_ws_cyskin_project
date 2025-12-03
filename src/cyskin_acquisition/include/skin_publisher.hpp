
#pragma once

#include <iostream>
#include "updater_interface.h"

class SkinPublisher
{
protected:
    std::shared_ptr<UpdaterInterface> u;
    double print_freq;
    double thresh;
public:
    virtual void publish() = 0;
};
