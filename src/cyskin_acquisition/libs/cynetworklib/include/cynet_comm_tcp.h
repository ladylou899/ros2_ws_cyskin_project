#ifndef CYNET_COMM_TCP_H
#define CYNET_COMM_TCP_H

#include <stddef.h>
#include <inttypes.h>
#include <cstdlib>
#include <mutex>
#include "cynet_comm.h"
#include "cynet_config.h"

#if defined(CY_SUPPORT_TCP_CLIENT) || defined(CY_SUPPORT_TCP_SERVER)

#include <sys/types.h>
#if defined _WIN32 || defined _WIN64
#include <winsock2.h>
#include <windows.h>
#include<ws2tcpip.h>
#else
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#endif





#include <iostream>
#include <unistd.h>
/*
 * Maybe we need SSL to secure the TCP communication.
 */

/*
 * [Computer sending commands] <-> [ TCP CHANNEL ] <-> [Embedded device receveing commands] <-> [CAN BUS] <-> [SKIN]
 * We need some kind of protocol between the server and the client, something like this should be ok:
 *
 * CmdType (open, close, read, write) - 1 byte
 * Length - 2 bytes
 * Payload - x bytes
 *
 * 	[open] - the payload is the bus to open (4 bytes)
 * 	[close] - the payload is the bus to close (4byte)
 *  [write] - the payload is a CyIhbInfo structure + data
 */

enum CyTcpCmd
{
	CY_TCP_CMD_OPEN = CY_TCP + 1,			// open bus
	CY_TCP_CMD_CLOSE,				// close bus
	CY_TCP_CMD_READ,				// still to think about this
	CY_TCP_CMD_WRITE				// write command
};

class CyTcpPacket : public CyPacket
{
public:
	uint8_t cmd;

	CyTcpPacket() : CyPacket(NULL, 0, true) , cmd(-1) {}
	CyTcpPacket(uint8_t *d, uint32_t l, bool dyn = true) : CyPacket(d,l, dyn) , cmd(-1) {}
	CyTcpPacket(uint8_t *d, uint32_t l, uint8_t c, bool dyn = true) : CyPacket(d,l, dyn) , cmd(c) {}
	~CyTcpPacket() {}

	int32_t get_header_size() const { return (sizeof(cmd) + sizeof(data_len)); }
	int32_t get_packet_size() const { return (get_header_size() + data_len); }



	int32_t read_packet(int socket, std::mutex *mutex=NULL)
	{
		int32_t ret = 0, len = get_header_size();
		uint8_t header[get_header_size()];

		if (mutex)
			mutex->lock();

		if ((ret = _read(socket, header, len)) > 0)
		{
			memcpy(&cmd, header, sizeof(cmd));
			memcpy(&data_len, header+sizeof(cmd), sizeof(data_len));
			len = data_len;
			if (data)
				delete [] data;
			data = NULL;

			if (len > 0)
			{
				data = new uint8_t[len];
				ret = _read(socket, data, len);
			}
		}
		if (mutex)
			mutex->unlock();
		return ret;
	}

	int32_t send_packet(int socket, std::mutex *mutex=NULL)
	{
		int32_t ret = 0, len = get_packet_size();
		uint8_t packet[get_packet_size()];

		if (mutex)
		{
			mutex->lock();
		}



		memcpy(packet, &cmd, sizeof(cmd));
		memcpy(packet+sizeof(cmd), &data_len, sizeof(data_len));
		memcpy(packet+get_header_size(), data, data_len*sizeof(*data));

		//std::cout << "1 - Going to unlock mutex: " << mutex << std::endl;
		ret = _send(socket, packet, len);

		if (mutex)
		{
			mutex->unlock();
		}
		return ret;
	}

private:

	inline int32_t _read(int socket, void *data, int32_t len)
	{
		int32_t x = 0, ret = len;
		if (len>0)
		{
			do
			{
#if defined _WIN32 || defined _WIN64
                                if ((x=recv(socket, (char *)data, len, 0)) <= 0)
#else
                                if ((x=recv(socket, data, len, 0)) <= 0)
#endif
				{
					ret = x;
					break;
				}
			}while((len-=x) > 0);
		}
		return ret;
	}

	inline int32_t _send(int socket, void *data, int32_t len)
	{
		int32_t x = 0, ret = len;
		do
		{
#if defined _WIN32 || defined _WIN64
                        if ((x=send(socket, (char *)data, len, 0)) == -1)
#else
                        if ((x=send(socket, data, len, 0)) == -1)
#endif
			{
				ret = -1;
				break;
			}
		}while((len-=x) > 0);
		return ret;
	}

};


#endif /* CY_SUPPORT_TCP */

#endif


