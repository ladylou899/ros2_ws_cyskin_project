#ifndef CYNET_NETWORK_H
#define CYNET_NETWORK_H

#include <vector>
#include <atomic>
#include "cynet_config.h"
#include "cynet_comm.h"
#include "cynet_ihb.h"
#include "cynet_dispatcher.h"
#include "cynet_comm_utils.h"
#include "cynet_compiler.h"

/* class CyNetwork */
class CyNetwork
{
	public:

		CyNetwork(CyComm *c, int32_t cst_btld, int32_t cst_app): comm(c),
			utils(new CyCommUtils(c, cst_btld, cst_app)){};

		/* ~CyNetwork() will delete the object, so don't delete it */
		CyNetwork(CyComm *c):CyNetwork(c,CY_CHECKSUM_CRC_16,CY_CHECKSUM_CRC_8){};
		~CyNetwork();

		void shutdown();

		void switch_phase(CyCommPhase p);

		std::vector<CyIhb*> &get_network_structure(bool refresh=true, CyUSec timeout = (CY_1_SEC*3));
		std::vector<uint32_t> get_open_buses() { return comm->get_open_buses(); }

		CyComm *get_comm() { return comm; }
		CyCommUtils *get_utils() { return utils; }

		#ifdef CY_SUPPORT_SKIN
		void switch_skin_phase(CyCommPhase p);
		void start_skin_acquisition(uint16_t autosync = 50); // 50ms acquisition loop
		void stop_skin_acquisition();
		void skin_loop(CyBuffer<CyCommRxData> &recv_buf);
		#endif
		
	private:
		CyComm *comm;
		CyCommUtils *utils;
		std::vector<CyIhb*> ihbs;
		#ifdef CY_SUPPORT_SKIN
		static volatile std::atomic_int interrupted;
		#endif

		void clear_network_structure(void);
		void discover_ihbs(std::vector<CyIhbInfo> *ret, CyUSec timeout = CY_100_MSEC);
		//void discover_subnets(std::vector<CyIhbInfo> *ret, CyUSec timeout = CY_100_MSEC);
		#ifdef CY_SUPPORT_SKIN
		static void sig_handler(int signal){
			CyNetwork::interrupted = 1;
		}

		void setup_interrupt_handler();
		void discover_skin(std::vector<CyIhbInfo> *ret, CyUSec timeout = CY_100_MSEC);
		void decode_and_process_skin_data( CyIhbInfo ihb, uint8_t *data, uint32_t data_len);
		#endif
};

#endif
