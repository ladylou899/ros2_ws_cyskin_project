#ifndef CYNET_BUFFER_H
#define CYNET_BUFFER_H

#include <mutex>
#include <queue>
#include "cynet_comm_data.h"
#include "cynet_comm_utils.h"

/*
 * CyBuffer is a FIFO protected for concurrent access.
 *
 * The interface is similar to std::queue
 */

class CyCommRxData;
template<class T>
class CyBuffer
{
	public:
		CyBuffer() {}
		~CyBuffer() {}

		void push(const T &t)	{ mutex.lock();              Q.push(t); mutex.unlock(); }
		T &front()		{ mutex.lock(); T &res =     Q.front(); mutex.unlock(); return res; }
		void pop()		{ mutex.lock();              Q.pop();   mutex.unlock(); }
		uint64_t size()		{ mutex.lock(); uint64_t s = Q.size();  mutex.unlock(); return s; }
		bool empty()		{ mutex.lock(); bool e =     Q.empty(); mutex.unlock(); return e; }
		bool wait_data(CyUSec timeout = CY_INFINITE, CyUSec microsec = CY_1_MSEC);


	private:
		std::mutex mutex;
		std::queue<T> Q;
};



template <class T>
bool CyBuffer<T>::wait_data(CyUSec timeout, CyUSec microsec)
{
	return false;
}

template <>
inline bool CyBuffer<CyCommRxData>::wait_data(CyUSec timeout, CyUSec microsec)
{
	return wait_func_change([this](){ return !empty(); }, timeout, microsec);
}

#endif
