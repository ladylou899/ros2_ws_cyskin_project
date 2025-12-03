#ifndef CYNET_IHB_INFO_H
#define CYNET_IHB_INFO_H

#include <stddef.h>
#include <vector>
#include <iostream>
#include <memory>
#include <cynet_ihb_dev.h>


#define CY_ALL_IHBS ((uint32_t)0xFFFFFFFF)
#define CY_ALL_BUSES ((uint32_t)0xFFFFFFFF)



/* structure for holding Ihb id and to which bus it belongs to */
struct CyIhbInfo
{
	uint32_t ihb_id;
    uint32_t bus_id;
	uint32_t ihb_original_id; //Store the IHB UID in the application phase

	//std::vector<uint8_t> subnets; //one entry for each subnet. each element is the number of nodes of the subnet
	//std::vector<CyNodeInfo> *nodes; //array of vectors(one for each subnet) containing nodes information
	//CYSKIN_DEC(std::vector<CyModule> modules);

	// Smart pointer to class describing all devices attached to the IHB
	std::shared_ptr<CyIhbDev> ihb_devs;

	CyIhbInfo(): ihb_id(CY_ALL_IHBS), bus_id(CY_ALL_BUSES), ihb_original_id(0xFFFFFFFF), ihb_devs(std::make_shared<CyIhbDev>()) {}
    CyIhbInfo(uint32_t i, uint32_t b): ihb_id(i), bus_id(b), ihb_original_id(0xFFFFFFFF), ihb_devs(std::make_shared<CyIhbDev>()) {}
	CyIhbInfo(const CyIhbInfo &co){ ihb_id = co.ihb_id; 
									bus_id = co.bus_id; 
									ihb_original_id = co.ihb_original_id;
									ihb_devs = co.ihb_devs;
								  }
	bool operator <(const CyIhbInfo &other) const
	{
		if (bus_id == other.bus_id)
			return ihb_id < other.ihb_id;
		return bus_id < other.bus_id;
	}

	bool operator ==(const CyIhbInfo &other) const
	{
		return ihb_id == other.ihb_id && bus_id == other.bus_id;
	}
};

namespace std
{
	template <>
	class hash<CyIhbInfo>
	{
	public:
		size_t operator()(const CyIhbInfo &ihb) const
		{
			return (uint64_t)ihb.ihb_id << 32 | ihb.bus_id;
		}
	};
}


#define CyBroadcast CyIhbInfo(CY_ALL_IHBS, CY_ALL_BUSES)

#endif
