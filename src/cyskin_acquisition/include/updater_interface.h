
#pragma once

#include <iostream>
#include <array>
#include <vector>
#include <atomic>
#include <condition_variable>
#include <thread>

typedef uint32_t skin_data;

class UpdaterInterface
{
    protected:

    double T;
    bool is_running = false;
    std::array<std::vector<skin_data>,2> buffer_data;
    std::atomic<uint8_t> bounded_buffer;
    uint32_t n_sensors;
        
    std::condition_variable cv;
    std::mutex m;
    bool updated = false;
    std::chrono::duration<uint64_t,std::micro> waiting_timer;
    //std::chrono::_V2::system_clock::time_point waiting_timer;
    
    public:

    UpdaterInterface(double T);

    virtual void init() = 0;
    virtual void updateOnce() = 0;
    void update();
    void stopUpdater();
    bool isRunning();
    void makeThisThreadWait();
    const uint32_t getNumberOfSensors();
    const std::vector<skin_data> getDataBuffer();
    const double getSamplingTime();
    uint8_t getBoundedBuffer();
    void swapBuffer();
};