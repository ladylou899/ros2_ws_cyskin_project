#ifndef CYNET_COMM_ESDCAN_H
#define CYNET_COMM_ESDCAN_H

#include "cynet_comm.h"
#include "cynet_comm_can.h"

#ifdef CY_SUPPORT_ESDCAN

class CyCommEsdCan: public CyCommCan
{
	public:
		// Base Constructor with default parameters
		CyCommEsdCan(CyCommPhase p = CY_PHASE_BOOTLOAD);
		// Constructor with custom parameters for both phases
		CyCommEsdCan(CyCommPhase p, CyBusParamsCan params_bootload, CyBusParamsCan params_app);
		virtual ~CyCommEsdCan();

		virtual bool is_comm_open() { return true; }
		virtual void switch_phase(CyCommPhase p);

	protected:
		virtual void *open_bus(uint32_t bus_id);
		virtual void close_bus(void *handle);
		virtual int read_packet(void *handle, CyCanPacket &pkt);
		virtual int write_packet(void *handle, const CyCanPacket &pkt);
};

#endif /* CY_SUPPORT_ESDCAN */

#endif
