#ifndef CYNET_COMM_CAN_H
#define CYNET_COMM_CAN_H

#include <stddef.h>
#include "cynet_config.h"

enum CyCanBitRate
{
    CY_RATE_1M		= 1000000,
    CY_RATE_800K		= 800000,
    CY_RATE_500K		= 500000,
    CY_RATE_250K		= 250000,
    CY_RATE_125K		= 125000,
    CY_RATE_100K		= 100000,
    CY_RATE_50K		= 50000,
    CY_RATE_20K		= 20000,
    CY_RATE_10K		= 10000,
    CY_RATE_5K		= 5000
};

enum CyCanMsgType
{
    CY_CAN_MSG_ST = 0,
    CY_CAN_MSG_EXT = 1
};


#if !defined(CY_SUPPORT_PCAN) && !defined(CY_SUPPORT_ESDCAN)
typedef struct { int32_t bitrate; int32_t msgtype; } CyBusParamsCan;
#else

#include "cynet_comm.h"


struct CyBusParamsCan
{
	CyBusParamsCan(CyCommPhase bp = CY_PHASE_BOOTLOAD) : bitrate(CY_RATE_1M), msgtype(bp == CY_PHASE_BOOTLOAD?CY_CAN_MSG_EXT:CY_CAN_MSG_ST) {}
	CyBusParamsCan(CyCommPhase bp, CyCanBitRate b, CyCanMsgType m) : bitrate(b), msgtype(m) {}
	CyCanBitRate bitrate;
	CyCanMsgType msgtype;
};

struct CanMessageIncomplete
{
	uint8_t *message;
	uint32_t len;
	uint32_t mem_size;
	CanMessageIncomplete(): message(NULL), len(0), mem_size(0) {}
	~CanMessageIncomplete() { /* Note: don't destruct, the pointer has been passed to someone else */ }
};

struct CyCanPacket
{
	uint32_t id;
	uint8_t len;
	uint8_t data[8];
};

class CyCommCan: public CyComm
{
	public:
		CyCommCan(CyCommPhase p);
		CyCommCan(CyCommPhase p, CyBusParamsCan params_bootload, CyBusParamsCan params_app);
		virtual ~CyCommCan();

		virtual bool is_comm_open() = 0;
		virtual void switch_phase(CyCommPhase p);

	protected:
		/* functions that manage memories, handle packets and do cleanup */
		virtual int32_t open(CyBusIterator &bus) FINAL;
		virtual void close(CyBusIterator &bus) FINAL;
		virtual int32_t read(CyBusIterator &bus, CyCommRxData &data) FINAL;
		virtual int32_t write(CyBusIterator &bus, CyIhbInfo ihb, CyPacket *packet) FINAL;

		/* functions that handle the bus, implementation specific */
		virtual void *open_bus(uint32_t bus_id) = 0;			/* open returns a handle, or NULL if error */
		virtual void close_bus(void *handle) = 0;			/* close takes that handle */
		/* 0 means ok, negative is error and positive means time out */
		virtual int read_packet(void *handle, CyCanPacket &pkt) = 0;	/* must ignore packets of the wrong type */
		virtual int write_packet(void *handle, const CyCanPacket &pkt) = 0;

		/* this prevents inclusion of can specific headers */
		CyBusParamsCan can_params_bootload;
		CyBusParamsCan can_params_app;
		CyBusParamsCan can_params;
		uint32_t cy_can_msg_type;
		uint32_t cy_can_id_bits;
		uint32_t cy_can_asm_bits;
};
#endif

#endif
