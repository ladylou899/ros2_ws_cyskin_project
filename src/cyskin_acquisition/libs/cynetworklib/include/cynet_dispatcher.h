#ifndef CYNET_DISPATCHER_H
#define CYNET_DISPATCHER_H

#include <unordered_set>
#include <unordered_map>
#include <mutex>
#include "cynet_buffer.h"
#include "cynet_comm_data.h"

class CyDispatcher
{
	public:
		CyDispatcher() { subscriptions.reserve(0x400); } //reserves space for 1024 elements
		~CyDispatcher() {}

		/* add `buffer` to list of buffers for messages from `ihb` */
		void subscribe(CyIhbInfo ihb, CyBuffer<CyCommRxData> *buffer);
		/* remove `buffer` from list of buffers assigned to `ihb` */
		void unsubscribe(CyIhbInfo ihb, CyBuffer<CyCommRxData> *buffer);

		/* dispatch a packet to subscribers */
		void dispatch(const CyCommRxData &data);
	private:
		/* each bus:ihb has a reference to a list of subscribed buffers */
		std::unordered_map<CyIhbInfo, std::unordered_set<CyBuffer<CyCommRxData> *>> subscriptions;
		std::mutex mutex;
};

#endif
