
#pragma once

#include "updater.h"
#include "skin_publisher.hpp"

// There is a shared buffer with fixed length containing information on the acquisition parameters
#define HEADER_LENGTH 10
#define HEADER_SIZE HEADER_LENGTH * sizeof(uint32_t)
#define HEADER_KEY_ID 65
#define ID_NUMBER_OF_SENSORS 0
#define ID_ACQUISITION_TYPE 1
#define ID_DATA_BUFFER_KEY 2
// IDs from 4 to 10 are reserved for a future extension
// Data buffer fixed members
#define ID_SAMPLE 0
#define ID_TIME 1
#define ID_NUMBER_OF_ACTIVE_SENSORS 2
#define ID_DATA_FRAME_START 3

#if __linux__ // Include the headers for linux bases systems
#include <sys/ipc.h>
#include <sys/shm.h>
#include <fstream>
#include <stdlib.h>
// Shared memory keys (must match the acquisition module)
#define HEADER_KEY 450

#endif // __linux__

#if defined(_WIN32) // include the windows headers
#include <windows.h>
// Name of the Memory Mapped File
#define HEADER_KEY "skin_acquisition_header"
#define DATA_KEY "skin_acquisition_data"

#endif // WIN32

class SharedMemoryPublisher : public SkinPublisher
{
private:
    
    uint32_t *header_buffer, *data_buffer;
    uint32_t DATA_LENGTH;
    uint32_t DATA_SIZE;
    uint32_t sensors;
    #if __linux__
    int shmid_header, shmid_data;
    #endif // __linux__
    #if defined(_WIN32)
    HANDLE header_map_file, data_map_file;
    #endif // WIN32

public:
    SharedMemoryPublisher( std::shared_ptr<UpdaterInterface> _u , double _print_freq, double _thresh );
    ~SharedMemoryPublisher();
    void publish();
};
