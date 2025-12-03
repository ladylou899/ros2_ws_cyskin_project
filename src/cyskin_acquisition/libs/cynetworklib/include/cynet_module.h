#ifndef CYNET_MODULE_H
#define CYNET_MODULE_H

#include "cynet_config.h"

#ifdef CY_SUPPORT_SKIN

#include <vector>
#include <iostream>
#include <cynet_sensor.h>
#include <mutex>

class CyNetwork;
class CyModule;

class CyModulePublisher{

protected:
    CyModule *m;

public:
    CyModulePublisher(CyModule *module){m = module;}
    virtual ~CyModulePublisher(){};

    virtual void publish() = 0;

    friend class CyModule;
};

class CyModule{


    std::vector<CySensor> sensors;
    uint32_t sui;
    uint8_t grouping;
    uint16_t already_cut_sensors;
    //std::ofstream *out;	/* if logging this module, this stream would be open */
    std::vector<CyModulePublisher *> publishers;

    std::mutex mutex;

public:

    CyModule(): sensors(0),sui(0),grouping(0),already_cut_sensors(0), publishers(0){}
    CyModule(const CyModule &);

    CyModule& operator=(const CyModule& m);

    uint32_t get_sui() const { return sui; }
    uint8_t get_grouping() const { return grouping; }
    uint16_t get_cut_sensors() const { return already_cut_sensors; }
    std::vector<CySensor> & get_sensors() { return sensors; }

    void attach_publisher(CyModulePublisher *);
    void detach_publisher(CyModulePublisher *);
    void clear_publishers();
    void publish();

    friend class CyNetwork;
    friend class CyModulePublisher;
};


class CyModuleConsolePublisher: public CyModulePublisher{


public:
    CyModuleConsolePublisher(): CyModulePublisher(0){};
    CyModuleConsolePublisher(CyModule *module): CyModulePublisher(module){};
    virtual ~CyModuleConsolePublisher(){};

    virtual void publish(){
        if(m){
            std::cout<<m->get_sui()<< "\t";
            for(auto const &i: m->get_sensors()){
                std::cout<< i.get_measurement() << "\t";
            }
            std::cout<<std::endl;
        }
    };
};

#endif

#endif
