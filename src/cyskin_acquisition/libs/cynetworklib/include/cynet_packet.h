#ifndef CYNET_PACKET_H
#define CYNET_PACKET_H

#include <mutex>
#include <stdint.h>

/*
 * CyPacket(unsigned char *arg1, size arg2, bool arg3, unsigned arg4)
 *
 * if arg3 is true then the data is deleted at the deconstructor
 */
class CyPacket
{
	public:
		uint8_t *data;
		uint32_t data_len;

		CyPacket(uint8_t *d, uint32_t l, bool y = true, uint32_t r = 1): data(d), data_len(l), dynamic(y), reference_count(r) {}
		~CyPacket() { if (dynamic && data) delete[] data; }
		/* add reference count */
		void attach();
		/* decrease reference count and possibly delete object */
		void release();
	protected:
		bool dynamic;
		uint32_t reference_count;
		std::mutex mutex;
};

#endif
