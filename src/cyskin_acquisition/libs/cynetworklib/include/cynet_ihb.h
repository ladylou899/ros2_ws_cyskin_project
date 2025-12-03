#ifndef CYNET_IHB_H
#define CYNET_IHB_H

#include <stdint.h>
#include <atomic>
#include <thread>
#include <cybtldr_api.h>
#include <cybtldr_api2.h>
#include <cynet_buffer.h>
#include <cynet_comm_data.h>
#include <cynet_ihb_info.h>

enum CyIhbOperation
{
	CY_OP_PROGRAM = 0,
	CY_OP_ERASE,
	CY_OP_VERIFY,
	CY_OP_ABORT
};

class CyComm;
class CyCommUtils;
class CyDispatcher;

/* class CyIhb */
class CyIhb : public CyBtldr_CommunicationsData
{
	public:
		CyIhb(CyIhbInfo i, CyComm *c, CyCommUtils *u);
		virtual ~CyIhb();

		uint32_t get_ihb_id() const { return info.ihb_id; }
		uint32_t get_bus_id() const { return info.bus_id; }
		//uint8_t  get_subnets() const { return info.subnets.size(); }
		//uint8_t  get_subnet_size(uint8_t i){ return i>=info.subnets.size()? 0: info.subnets[i]; }
		//CyNodeInfo get_node_info(uint8_t subnet, uint8_t node);
		const CyIhbInfo& get_ihb_info() const { return info; }
		CyIhbDev& get_ihb_devs() { return *info.ihb_devs; }

		/*
		 * run an operation on a thread.  If an operation already in progress, waits for it to stop.
		 * It returns the status of last finished job.  If operation is ABORT, it does not wait for the
		 * previous thread to finish and instead immediately executes the abort function.
		 *
		 * CyBtldr_ProgressUpdate is a function with the following signature:
		 *
		 *     void progress(CyBtldr_CommunicationsData *origin, unsigned char arrayId, unsigned short rowNum);
		 */
		uint32_t bootload_operation(CyIhbOperation, const char *, CyBtldr_ProgressUpdate *);
		uint32_t start_host_mode(uint8_t subnet, uint8_t node);

		bool is_data_available() { return recv_buf.empty(); }

		uint32_t wait_last_bootload_operation();
		bool operation_in_progress() { return thread_running; }
		uint32_t get_status_last_bootload_operation() { return status_last_bootload_op; }

		const CyBuffer<CyCommRxData> *get_recv_buffer() { return &recv_buf; }

	protected:
		void _program(const char *, CyBtldr_ProgressUpdate *);
		void _erase(const char *, CyBtldr_ProgressUpdate *);
		void _verify(const char *, CyBtldr_ProgressUpdate *);
		void _abort();

	private:
		CyIhbInfo info;
		std::atomic<uint32_t> status_last_bootload_op;
		bool thread_should_stop;
		bool thread_running;
		std::thread *_thread;
		/* reference to communicator.  It is used to output messages */
		CyComm *comm;
		/* reference to utilities.  It is used to build and process custom messages */
		CyCommUtils *utils;
		/* a buffer to receive messages.  It is subscribed to the dispatcher */
		CyDispatcher *dispatcher;
		CyBuffer<CyCommRxData> recv_buf;

		virtual int32_t OpenConnection(void);
		virtual int32_t CloseConnection(void);
		virtual int32_t ReadData(unsigned char *buf, int32_t size);
		virtual int32_t WriteData(unsigned char *buf, int32_t size);
};

#endif
