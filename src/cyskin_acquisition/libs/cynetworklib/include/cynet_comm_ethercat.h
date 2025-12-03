#ifndef CYNET_COMM_ETHERCAT_H
#define CYNET_COMM_ETHERCAT_H

#include "cynet_comm.h"
#include "cynet_config.h"

#ifdef CY_SUPPORT_ETHERCAT

struct CyBusParamsEcat
{
	CyBusParamsEcat() {}
};

class CyCommEthercat: public CyComm
{
	public:
		CyCommEthercat(CyCommPhase p, CyBusParamsEcat params);
		virtual ~CyCommEthercat();

		virtual bool is_comm_open() { return false; }
	protected:
		virtual int32_t open(CyBusIterator &bus);
		virtual void close(CyBusIterator &bus);
		virtual int32_t read(CyBusIterator &bus, CyCommRxData &data);
		virtual int32_t write(CyBusIterator &bus, CyIhbInfo ihb, CyPacket *packet);
	private:
};

#endif /* CY_SUPPORT_ETHERCAT */

#endif
