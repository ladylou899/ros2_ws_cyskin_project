#ifndef CYNET_COMM_TCP_CLIENT
#define CYNET_COMM_TCP_CLIENT
#include <cynet_comm.h>
#include <cynet_comm_tcp.h>
#include <thread>
#include <mutex>
#include <unordered_map>
#include <cstring>
#ifdef CY_SUPPORT_TCP_CLIENT


struct CyBusParamsTcpClient
{
	CyBusParamsTcpClient() : ipaddress(""), port(0), type(CY_PCAN), bus_params_len(0)
	{
		memset(bus_params, 0, 0xFF*sizeof(bus_params));
	}
	CyBusParamsTcpClient(std::string ia, uint16_t p, CyBusType t, unsigned l, uint8_t *par) : ipaddress(ia), port(p), type(t), bus_params_len(l)
	{
		memcpy(bus_params, par, bus_params_len*sizeof(bus_params[0]));
	}
	CyBusParamsTcpClient(const CyBusParamsTcpClient &c) :ipaddress(c.ipaddress), port(c.port), type(c.type), bus_params_len(c.bus_params_len)
	{
		memcpy(bus_params, c.bus_params, bus_params_len*sizeof(bus_params[0]));
	}

	std::string ipaddress;
	uint16_t port;
	CyBusType type;
	unsigned bus_params_len;
	uint8_t bus_params[0xFF];
};


class CyCommTcpClient: public CyComm
{
public:
	CyCommTcpClient(CyCommPhase p, CyBusParamsTcpClient params); //takes care of setting up a connection
	virtual ~CyCommTcpClient();

	//virtual bool is_comm_open() { int32_t error; socklen_t len = sizeof(error); return ( getsockopt (tcp_socket, SOL_SOCKET, SO_ERROR, &error, &len ) == 0 ? true : false); }
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
	struct addrinfo *server_info, *server_info_llist;
	int tcp_socket;
	std::thread *rx_thread;
	std::mutex msg_mutex;
	bool stop_rx_thread;
	CyBusParamsTcpClient tcp_params;

	void process_incoming_packet();
	inline bool is_connected()
	{
		return is_comm_open();
	}
	virtual void switch_phase(CyCommPhase p){}
public:
	//not thread safe functions -- should only be called from constructor and deconstructor for now
	void close_connection();
    bool open_connection();

};

#endif /* CY_SUPPORT_TCP */
#endif
