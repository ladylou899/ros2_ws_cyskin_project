
#include "shared_memory_publisher.hpp"

SharedMemoryPublisher::SharedMemoryPublisher(std::shared_ptr<UpdaterInterface> _u , double _print_freq, double _thresh)
{
    u = _u;
    print_freq = _print_freq;
    thresh = _thresh;

    // Get the number of sensors
    sensors = u->getNumberOfSensors();
    // Initialize constant values
    DATA_LENGTH = 2 * sensors + 3;
    DATA_SIZE = DATA_LENGTH*sizeof(uint32_t);

    #if __linux__

    // Reserving header shared memory
    shmid_header = shmget(HEADER_KEY, HEADER_LENGTH, 0666 | IPC_CREAT);
    if (shmid_header < 0)
    {
        perror("Shared memory");
        return;
    }
    header_buffer = (uint32_t *)shmat(shmid_header, nullptr, 0);
    header_buffer[ID_DATA_BUFFER_KEY] = 64;

    #endif // __linux__

    #if defined(_WIN32)

    header_map_file = CreateFileMapping(
                 INVALID_HANDLE_VALUE,    // use paging file
                 NULL,                    // default security
                 PAGE_READWRITE,          // read/write access
                 0,                       // maximum object size (high-order DWORD)
                 HEADER_SIZE,                // maximum object size (low-order DWORD)
                 HEADER_KEY);                 // name of mapping object

    if (header_map_file == NULL) { std::cout << "Cannot create file mapping object\n"; exit(0); }
    header_buffer = (uint32_t*) MapViewOfFile(header_map_file, FILE_MAP_ALL_ACCESS, 0, 0, HEADER_SIZE);
    if (header_buffer == NULL) { std::cout << "Could not map view of file.\n"; CloseHandle(header_map_file); exit(0); }

    #endif // WIN32

    header_buffer[ID_NUMBER_OF_SENSORS] = sensors; // N sensors
    header_buffer[ID_ACQUISITION_TYPE] = 0;
      
    #if __linux__

    shmid_data = shmget(header_buffer[ID_DATA_BUFFER_KEY], DATA_SIZE, 0666 | IPC_CREAT);
    if (shmid_data < 0)
    {
        perror("Shared memory");
        return;
    }
    data_buffer = (uint32_t *)shmat(shmid_data, nullptr, 0);

    #endif // __linux__

    #if defined(_WIN32)

    // It could be DATA_SIZE in the following
    data_map_file = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, DATA_SIZE, DATA_KEY); 
    if (data_map_file == NULL) { std::cout << "Cannot create file mapping object\n"; exit(0); }
    data_buffer = (uint32_t*) MapViewOfFile(data_map_file, FILE_MAP_ALL_ACCESS, 0, 0, DATA_SIZE);
    if (data_buffer == NULL) { std::cout << "Could not map view of file.\n"; CloseHandle(data_map_file); exit(0); }

    #endif // WIN32

}

SharedMemoryPublisher::~SharedMemoryPublisher()
{
    #if __linux__
    system("ipcrm -M 64 && ipcrm -M 450");
    #endif // __linux__
    #if defined(_WIN32)
    // TODO put header_buffer and data_buffer as global variables
    UnmapViewOfFile(header_buffer);
    CloseHandle(header_map_file);
    UnmapViewOfFile(data_buffer);
    CloseHandle(data_map_file);
    #endif // WIN32
    std::cout << "Shared Area Cleaned\n";
}

void SharedMemoryPublisher::publish()
{
   // Timestamp
    auto start = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point t;
    uint32_t time_elapsed;

    std::cout << "Created shared memory area for " << sensors << " sensors\n";
    
    uint32_t sample_id = 0;

    std::vector<skin_data> data;

    // Print shared memory area content
    std::thread print_thread([&]{
        uint64_t time_elapsed_ns;
        auto start = std::chrono::high_resolution_clock::now();
        if (print_freq > 0)
        {
            while(u->isRunning())
            {
                start = std::chrono::high_resolution_clock::now();

                // Print header
                std::cout << "\033[1;34mHeader:\033[0m [ ";
                for (int i = 0; i < HEADER_LENGTH; i++) std::cout << header_buffer[i] << " "; 
                std::cout << "]\n\n";
                // Print data
                std::cout << "\033[1;34mData:\033[0m [ ";
                for (unsigned int i = 0; i < DATA_LENGTH; i++) 
                {
                if ( i == ID_DATA_FRAME_START || i == sensors + ID_DATA_FRAME_START )
                std::cout << "\033[0;33m" << data_buffer[i] << "\033[0m "; 
                else 
                std::cout << data_buffer[i] << " "; 
                }
                std::cout << "]\n\n";

                time_elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start).count();
                std::this_thread::sleep_for(std::chrono::nanoseconds( (uint64_t)(print_freq*1000000000) - time_elapsed_ns ));
            }
        }
    });

    while (u->isRunning())
    {
        u->makeThisThreadWait();
        
        data = u->getDataBuffer();

        for(unsigned int i = 0; i < data.size()/2; i++)
        {
            data_buffer[ i + ID_DATA_FRAME_START ] = data[i];
            data_buffer[ i + sensors + ID_DATA_FRAME_START ] = data[i+data.size()/2]; // Considering all active sensors
        }

        t = std::chrono::high_resolution_clock::now();
        time_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(t - start).count();

        // Number of sensors
        data_buffer[ID_NUMBER_OF_ACTIVE_SENSORS] = sensors; // All active sensors case
        // Timestamp
        data_buffer[ID_TIME] = time_elapsed;
        // Sample ID
        data_buffer[ID_SAMPLE] = sample_id; sample_id++;
    }

    // Join the thread here
    print_thread.join();
}