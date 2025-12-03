#ifndef CYNET_COMM_DATA_H
#define CYNET_COMM_DATA_H

#include <cstring>
#include "cynet_packet.h"
#include "cynet_ihb_info.h"
#include "cynet_comm_utils.h"
#include <iostream>

enum CyTransmitState
{
	CY_TRANSMIT_READY = 0,		/* ready to transmit */
	CY_TRANSMIT_DONE,		/* transmit successful */
	CY_TRANSMIT_FAILED,		/* transmit failed */
	CY_TRANSMIT_ABORTED		/* transmit aborted by user */
};

class CyComm;

class CyTransmitProgress
{
	public:
		CyTransmitProgress(CyTransmitState s = CY_TRANSMIT_READY) : state(s) {}
		~CyTransmitProgress() {}

		CyTransmitState state;
		int32_t wait_transmit(CyUSec timeout=CY_INFINITE, CyUSec microsec=CY_1_MSEC) //0 loops forever
		{
			if (wait_func_change([this](){ return state != CY_TRANSMIT_READY; }, timeout, microsec))
				return -1;
			return state;
		}
	private:
};


class CyCommData
{
	public:
		CyIhbInfo ihb;			/* id of ihb to transmit data to or received data from */

		CyCommData(): packet(NULL) {}
		CyCommData(CyPacket *p, CyIhbInfo i) : ihb(i), packet(p)
		{
			if (packet)
				packet->attach();
		}
		CyCommData(const CyCommData &c): ihb(c.ihb), packet(c.packet)
		{
			if (packet)
				packet->attach();
		}
		CyCommData(CyCommData &&c): ihb(c.ihb), packet(c.packet) { c.packet = NULL; }
		CyCommData& operator=(const CyCommData& c)
		{
			if (packet)
				packet->release();
			ihb = c.ihb;
			packet = c.packet;
			if (packet)
				packet->attach();
			return *this;
		}
		~CyCommData()
		{
			if (packet)
				packet->release();
		}
		CyPacket *get_packet() { return this->packet; }

	protected:
		CyPacket *packet;		/* shared between many CyCommData */
	private:
	friend class CyComm;
};

/* Actually CyCommRxData it's equal to CyCommData */
class CyCommRxData : public CyCommData
{
	public:
		CyCommRxData(): CyCommData() { }
		CyCommRxData(CyPacket *p, CyIhbInfo i): CyCommData(p,i) { }
		/* copy constructor: take care of packet's reference count */
		CyCommRxData(const CyCommRxData &c): CyCommData(c.packet, c.ihb) { }
		/* move constructor: set right hand side's packet to NULL, so it's reference count wouldn't be affected by destructor */
		CyCommRxData(CyCommRxData &&c): CyCommData(c.packet, c.ihb) { }
		CyCommRxData& operator=(const CyCommRxData& c)
		{
			if (packet)
				packet->release();
			ihb = c.ihb;
			packet = c.packet;
			if (packet)
				packet->attach();
			return *this;
		}


		~CyCommRxData() {}
	private:
		friend class CyComm;
};

/* Copies in a new area of memory the data
 *
 * All the commented code is due to the fact that in future we could need the status in this class
 *
 * */
class CyCommTxData : public CyCommData
{
	public:
		//CyCommTxData(bool w = false): CyCommData(), wait_transmit_end(w) { }
		CyCommTxData(const CyPacket *p, CyIhbInfo i, bool w=false): CyCommData(NULL, i),  wait_transmit_end(w)
		{
			set_packet(p);
			//important: don't have to set this->packet to null because it's already set to null by the CyCommData constructor
		}
		/* copy constructor: take care of packet's reference count */
		CyCommTxData(const CyCommTxData &c): CyCommData(NULL, c.ihb), wait_transmit_end(c.wait_transmit_end)
		{
			set_packet(c.packet);
		}
		/* move constructor: set right hand side's packet to NULL, so it's reference count wouldn't be affected by destructor */
		CyCommTxData(CyCommTxData &&c): CyCommData(NULL, c.ihb), wait_transmit_end(c.wait_transmit_end)
		{
			set_packet(c.packet);
		}

		~CyCommTxData()
		{
		//	if (wait_transmit_end)
			//	wait_transmit(CY_10_MSEC);
			clear_packet();
		}

		CyCommTxData& operator=(const CyCommTxData& c)
		{
			ihb = c.ihb;
			set_packet(c.packet);
			return *this;
		}

		void set_wait_transmit_at_end(bool v) { wait_transmit_end = v; }
		bool get_wait_transmit_at_end() { return wait_transmit_end; }

		void set_packet(const CyPacket *p)
		{
			if (p && p->data_len)
			{
				clear_packet();
				unsigned char *data = new unsigned char[p->data_len];
				memcpy(data, p->data, p->data_len * sizeof(*p->data));
				this->packet = new CyPacket(data, p->data_len, true);
			}
		}

		void clear_packet()
		{
			if (this->packet)
				delete this->packet;
			this->packet = NULL;
		}

	private:
		bool wait_transmit_end;
		friend class CyComm;
};

#endif
