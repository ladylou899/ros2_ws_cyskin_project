#ifndef CYNET_COMM_H
#define CYNET_COMM_H

#include <unordered_map>
#include <thread>
#include <stdint.h>
#include <stddef.h>
#include <new>
#include <cynet_dispatcher.h>
#include "cynet_buffer.h"
#include "cynet_compiler.h"

#define CY_TX_THREAD_US_SLEEP CY_2_MSEC
#define CY_RX_THREAD_US_SLEEP CY_2_MSEC
#define CY_MAXIMUM_BUSES_OPEN 0xFFFF

struct CyCommInternalPacket
{
	CyCommTxData *data;
	CyTransmitProgress *status;
	CyCommInternalPacket() : data(NULL), status(NULL) {}
	CyCommInternalPacket(CyCommTxData *d, CyTransmitProgress *s) : data(d), status(s) {}
};

struct CyCommInternalBus
{
	CyBuffer<CyCommInternalPacket> *transmit_buffer;
	std::thread *tx_thread, *rx_thread;
	uint32_t count;
	bool thread_should_stop;
	void *extra;

	CyCommInternalBus() : transmit_buffer(NULL), tx_thread(NULL), rx_thread(NULL),
			count(0), thread_should_stop(false), extra(NULL) {}
	CyCommInternalBus(const CyCommInternalBus &c) : transmit_buffer(c.transmit_buffer),
			tx_thread(c.tx_thread), rx_thread(c.rx_thread), count(c.count),
			thread_should_stop(c.thread_should_stop), extra(NULL) {}
};

enum CyBusType
{
	CY_PCAN = 0,
	CY_ECAT,
	CY_TCP
};

enum CyCommPhase
{
	CY_PHASE_BOOTLOAD = 0,
    CY_PHASE_APPLICATION = 1
};

typedef std::unordered_map<uint32_t, CyCommInternalBus>::iterator CyBusIterator;

class CyComm
{

    /* reference to dispatcher, for reader threads to send packets to */
    CyDispatcher *dispatcher;

    protected:
        CyCommPhase phase;

	public:
        CyComm(CyCommPhase p): dispatcher(new CyDispatcher), phase(p){bus_info.reserve(CY_MAXIMUM_BUSES_OPEN);}

        virtual ~CyComm();

		virtual bool is_comm_open() = 0;
		virtual void switch_phase(CyCommPhase p) = 0;

		/* add a transmission buffer for given bus */
		int32_t add_bus(uint32_t bus);
		int32_t remove_bus(uint32_t bus);
		/*
		 * transmit a packet on bus (specified in comm_data).  If CY_ALL_BUSES given, broadcasts message.
		 * If bus is not CY_ALL_BUSES and is not previously added (by `add_bus`), it will call `add_bus` first.
		 */
		int32_t send_data(CyCommTxData &data, CyTransmitProgress *status = NULL);
		int32_t send_data(const CyCommData &data, CyTransmitProgress *status = NULL);
		int32_t send_data(const CyPacket &p, CyIhbInfo &info, CyTransmitProgress *status = NULL);

        CyDispatcher *get_dispatcher() const { return dispatcher; }

		/*return a lists of all the buses opened */
		std::vector<uint32_t> get_open_buses(void);
		bool is_bus_open(uint32_t bus) { return bus_info.find(bus) == bus_info.end() ? false : true; }

        CyCommPhase get_phase() { return phase; }
	protected:
		/*
		 * interface for underlying communication channels
		 *
		 * All functions that have return value, return 0 on success and a negative value on failure.
		 * - open may be called many times on the same bus at the same time, and only once it should take effect.
		 * - close would be called as many times as open is called, and only the last call should take effect.
		 * - read returns a received packet, possibly assembled from multiple physical packets.  This function shall
		 *   be called only from a single thread per bus.  If stop becomes true, it will return without reading a packet.
		 * - write writes a packet, possibly dividing into multiple physical packets.
		 * Negative value on failure
		 */
		virtual int32_t open(CyBusIterator &bus) = 0;
		virtual void close(CyBusIterator &bus) = 0;
		virtual int32_t read(CyBusIterator &bus, CyCommRxData &data) = 0;
		virtual int32_t write(CyBusIterator &bus, CyIhbInfo ihb, CyPacket *packet) = 0;
		/* call close on all buses that have a registered buffer */
		void close_all();

		std::unordered_map<uint32_t, CyCommInternalBus> bus_info;
        //CyCommPhase phase;
	private:
		/* reference to dispatcher, for reader threads to send packets to */
        //CyDispatcher *dispatcher;
		/* bus information*/

		std::mutex mutex;

		void transmit_thread(uint32_t bus);
		void receive_thread(uint32_t bus);

};

#endif
