#ifndef CYNET_IHB_DEV_H
#define CYNET_IHB_DEV_H

#include <cynet_config.h>
#include <cynet_node_info.h>

#ifdef CY_SUPPORT_SKIN
#include <cynet_module.h>
#endif

class CyNetwork;

class CyIhbDev{

    //std::vector<uint8_t> subnets; //one entry for each subnet. each element is the number of nodes of the subnet
	//std::vector<CyNodeInfo> *nodes; //array of vectors(one for each subnet) containing nodes information
#ifdef CY_SUPPORT_SKIN
    std::vector<CyModule> modules;
#endif
    public:

    CyIhbDev(){}
    CyIhbDev(const CyIhbDev &co){std::copy(co.modules.begin(), co.modules.end(),std::back_inserter(modules));}

#ifdef CY_SUPPORT_SKIN
    std::vector<CyModule>& get_modules(){return modules;};
#endif

    friend class CyNetwork;
};

#endif