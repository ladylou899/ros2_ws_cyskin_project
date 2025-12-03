
#include "skin_publisher.hpp"
#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <chrono>
#include <thread>
#include <termios.h>
#include <unistd.h>
#include <filesystem>

class FilePublisher : public SkinPublisher
{
private:
    /* data */
    std::string filename;
    std::ofstream out;
    std::queue<std::string> Q;
    std::shared_ptr<std::thread> queue_manager_thread;
    
    // Gesture collection members
    int gesture_mode;  // -1 = normal mode, 0-5 = gesture collection mode
    int sample_counter;
    std::string data_dir;
    
    // Helper methods for gesture collection
    bool kbhit();
    void collect_gesture_sample();
    int get_next_sample_number();
    void setup_gesture_directory();
    
public:
    FilePublisher( std::shared_ptr<UpdaterInterface> _u , std::string _filename, double _print_freq, double _thresh );
    FilePublisher( std::shared_ptr<UpdaterInterface> _u , std::string _filename, double _print_freq, double _thresh, int _gesture_mode );
    ~FilePublisher();
    void publish();
    void publish_gesture_collection();
};

