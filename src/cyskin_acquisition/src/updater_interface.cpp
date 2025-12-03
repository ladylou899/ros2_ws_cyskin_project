
#include "updater_interface.h"

UpdaterInterface::UpdaterInterface(double _T)
{ 
    T = _T;
    waiting_timer = std::chrono::milliseconds( 10*(int)(T*1000) );
}

const uint32_t UpdaterInterface::getNumberOfSensors()
{
    return n_sensors;
}

const double UpdaterInterface::getSamplingTime()
{
    return T;
}

const std::vector<skin_data> UpdaterInterface::getDataBuffer()
{
    return buffer_data[bounded_buffer];
}

void UpdaterInterface::update()
{
    is_running = true;
    std::thread t([&]{
        auto start = std::chrono::high_resolution_clock::now();
        std::chrono::high_resolution_clock::time_point t;
        t = std::chrono::high_resolution_clock::now();
        uint64_t time_elapsed_ns;
        
        while (is_running) 
        {
            start = std::chrono::high_resolution_clock::now();
            updateOnce();
            swapBuffer();
            time_elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start).count();
            std::this_thread::sleep_for(std::chrono::nanoseconds( (uint64_t)(T*1000000000) - time_elapsed_ns ));
            //std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count() << "\n";
        }
    });
    t.detach();
}

void UpdaterInterface::stopUpdater()
{
    waiting_timer = std::chrono::milliseconds(10);
    std::this_thread::sleep_for(std::chrono::microseconds( (int)(T*1000000)) );
    is_running = false;
}

bool UpdaterInterface::isRunning()
{
    return is_running;
}

void UpdaterInterface::makeThisThreadWait()
{
    std::unique_lock<std::mutex> lk(m);
    // waiting_timer was set to a large value in the constructor but then reduced when the acquisition is stopped,
    // in this way cv wait, will not lock the process while exiting
    cv.wait_for(lk, waiting_timer, [&] { return updated; });  
    updated = false;
    cv.notify_one();
}

uint8_t UpdaterInterface::getBoundedBuffer()
{
    return bounded_buffer;
}

void UpdaterInterface::swapBuffer()
{
    bounded_buffer = (bounded_buffer+1)%2;
    {
        std::unique_lock<std::mutex> lk(m);
        updated = true;
    }
    cv.notify_one();
}
