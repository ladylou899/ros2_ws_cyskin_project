#ifndef CYNET_COMM_PCAN_H
#define CYNET_COMM_PCAN_H

#include "cynet_comm_can.h"

#ifdef CY_SUPPORT_PCAN

class CyCommPCan: public CyCommCan
{
	public:
		CyCommPCan(CyCommPhase p = CY_PHASE_BOOTLOAD);
		CyCommPCan(CyCommPhase p, CyBusParamsCan params_bootload, CyBusParamsCan params_app);
		virtual ~CyCommPCan();

		virtual bool is_comm_open() { return true; }
		virtual void switch_phase(CyCommPhase p);
	protected:
		virtual void *open_bus(uint32_t bus_id);
		virtual void close_bus(void *handle);
		virtual int read_packet(void *handle, CyCanPacket &pkt);
		virtual int write_packet(void *handle, const CyCanPacket &pkt);
};

#endif /* CY_SUPPORT_PCAN */

#endif
