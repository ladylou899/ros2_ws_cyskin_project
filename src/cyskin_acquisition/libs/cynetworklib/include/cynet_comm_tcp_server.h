#ifndef CYNET_COMM_TCP_SERVER
#define CYNET_COMM_TCP_SERVER
#include <cynet_comm_tcp.h>
#include <mutex>
#include <thread>
#if defined(CY_SUPPORT_TCP_SERVER) && (defined(CY_SUPPORT_PCAN) || defined(CY_SUPPORT_ETHERCAT))

/*
 * Note: the tcp server acts like a proxy. The tcp client connects to the servers, whose connects to a CAN or ETHERCAT bus
 * So it's the client sending all the commands, so the open/close/read/write functions of the server do nothing.
 */

struct CyBusParamsTcpServer
{
	CyBusParamsTcpServer() : port(0) {}
	CyBusParamsTcpServer(uint16_t p) : port(p) {}
	uint16_t port;
};

class CyNetwork;
class CyCommPCan;
#ifdef CY_SUPPORT_PCAN
struct CyBusParamsCan;
#endif
class CyCommTcpServer: public CyComm
{
public:
	CyCommTcpServer(CyCommPhase p, CyBusParamsTcpServer params);
	virtual ~CyCommTcpServer();

	virtual bool is_comm_open()
	{
		return tcp_socket == -1 ? false : true;
	}
protected:
	virtual int32_t open(CyBusIterator &bus);
	virtual void close(CyBusIterator &bus);
	virtual int32_t read(CyBusIterator &bus, CyCommRxData &data);
	virtual int32_t write(CyBusIterator &bus, CyIhbInfo ihb, CyPacket *packet);
private:
	//net variables
	struct addrinfo *server_info, *server_info_llist;
	struct sockaddr_storage remote_addr;
	socklen_t remote_addr_size;
	int tcp_socket, remote_tcp_socket;
	//threads & mutexes
	std::thread *tx_thread, *rx_thread;
	std::mutex  msg_mutex;
	bool stop_threads;
	//
	CyComm *cynet;

	void start_server();
	void close_connection();

	inline bool is_connected()
	{
		return remote_tcp_socket == -1 ? false : true;
	}
	virtual void switch_phase(CyCommPhase p){
		if(cynet)
			cynet->switch_phase(p);
	}

	void process_incoming_packet();
	void process_outgoing_packet();
};

#endif /* CY_SUPPORT_TCP */

#endif
