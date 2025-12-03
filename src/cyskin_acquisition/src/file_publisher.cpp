
#include "file_publisher.hpp"
#include <iomanip>
#include <fcntl.h>

FilePublisher::FilePublisher(std::shared_ptr<UpdaterInterface> _u, std::string _filename, double _print_freq, double _thresh)
{
    u = _u;
    if (_filename.compare("") == 0) filename = "skin_data.txt";
    else filename = _filename;
    print_freq = _print_freq;
    thresh = _thresh;
    gesture_mode = -1;  // Normal file mode
    sample_counter = 0;
    data_dir = "data/";
}

// Constructor
FilePublisher::FilePublisher(std::shared_ptr<UpdaterInterface> _u, std::string _filename, double _print_freq, double _thresh, int _gesture_mode)
{
    u = _u;
    filename = _filename;
    print_freq = _print_freq;
    thresh = _thresh;
    gesture_mode = _gesture_mode;
    sample_counter = 0;
    data_dir = "data/";
    
    if (gesture_mode >= 0 && gesture_mode <= 5) {
        setup_gesture_directory();
        sample_counter = get_next_sample_number();
        std::cout << "\n=== GESTURE COLLECTION MODE ===" << std::endl;
        std::cout << "Collecting data for: " << gesture_mode << " finger(s)" << std::endl;
        std::cout << "Data will be saved to: " << data_dir << gesture_mode << "_finger/" << std::endl;
        std::cout << "Next sample will be: sample_" << std::setfill('0') << std::setw(2) << sample_counter << ".txt" << std::endl;
        std::cout << "Press SPACEBAR to start 3-second data collection" << std::endl;
        std::cout << "Press Ctrl+C to exit" << std::endl;
        std::cout << "==============================\n" << std::endl;
    }
}
// Destructor
FilePublisher::~FilePublisher()
{
    if (gesture_mode == -1) {  // Only for normal file mode
        while(!Q.empty())
        {
            out << Q.front() << std::endl << std::flush; Q.pop();
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        if (queue_manager_thread) {
            queue_manager_thread->join();
        }
        out.close();
    }
    while(!Q.empty())
    {
        out << Q.front() << std::endl << std::flush; Q.pop();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    queue_manager_thread->join();
    out.close();
}

// Non-blocking method to check if a key id being pressed, returns true of pressed
bool FilePublisher::kbhit()
{
    struct termios oldt, newt;
    int ch;
    int oldf;
    
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    
    ch = getchar();
    
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    
    if(ch != EOF) {
        ungetc(ch, stdin);
        return true;
    }
    
    return false;
}

void FilePublisher::setup_gesture_directory()
{
    // Create main data directory if it doesn't exist
    if (!std::filesystem::exists(data_dir)) {
        std::filesystem::create_directories(data_dir);
        std::cout << "Created main data directory: " << data_dir << std::endl;
    }
    
    // Create specific gesture directory
    std::string gesture_dir = data_dir + std::to_string(gesture_mode) + "_finger/";
    if (!std::filesystem::exists(gesture_dir)) {
        std::filesystem::create_directories(gesture_dir);
        std::cout << "Created gesture directory: " << gesture_dir << std::endl;
    }
}

int FilePublisher::get_next_sample_number()
{
    std::string gesture_dir = data_dir + std::to_string(gesture_mode) + "_finger/";
    int max_sample = 0;
    
    // If directory exists, find the highest existing sample number
    if (std::filesystem::exists(gesture_dir)) {
        try {
            for (const auto& entry : std::filesystem::directory_iterator(gesture_dir)) {
                if (entry.is_regular_file()) {
                    std::string filename = entry.path().filename().string();
                    if (filename.find("sample_") == 0 && filename.find(".txt") != std::string::npos) {
                        // Extract number from "sample_XX.txt" format
                        std::string number_str = filename.substr(7);  // Get everything after "sample_"
                        number_str = number_str.substr(0, number_str.find(".txt"));  // Remove .txt
                        try {
                            int sample_num = std::stoi(number_str);
                            max_sample = std::max(max_sample, sample_num);
                        } catch (const std::exception& e) {
                            // Skip files with invalid number format
                            continue;
                        }
                    }
                }
            }
        } catch (const std::exception& e) {
            std::cout << "Warning: Error reading directory " << gesture_dir << ": " << e.what() << std::endl;
        }
        
        if (max_sample > 0) {
            std::cout << "Found existing samples up to sample_" << std::setfill('0') << std::setw(2) 
                      << max_sample << ".txt" << std::endl;
        }
    } else {
        std::cout << "No existing samples found - starting fresh!" << std::endl;
    }
    
    return max_sample + 1;
}

void FilePublisher::collect_gesture_sample()
{
    std::cout << "\n\n RECORDING " << gesture_mode << " FINGER(S) - SAMPLE " 
              << std::setfill('0') << std::setw(2) << sample_counter << " - 3 SECONDS..." << std::endl;
    
    // Prepare filename
    std::string gesture_dir = data_dir + std::to_string(gesture_mode) + "_finger/";
    std::string sample_filename = gesture_dir + "sample_" + 
                                  std::string(2 - std::to_string(sample_counter).length(), '0') + 
                                  std::to_string(sample_counter) + ".txt";
    
    std::ofstream sample_file(sample_filename);
    if (!sample_file.is_open()) {
        std::cout << " ERROR: Cannot create file!" << std::endl;
        return;
    }
    
    // Wait for valid sensor data
    std::vector<skin_data> data;
    while (u->isRunning()) {
        data = u->getDataBuffer();
        if (data.size() >= 2 * u->getNumberOfSensors() && data[1] > 0) {
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    
    // Write sensor IDs header
    for (unsigned int i = 0; i < u->getNumberOfSensors(); i++) {
        sample_file << data[i] << " ";
    }
    sample_file << std::endl; // Move to next line 
    
    // Collect 30 timesteps over 3 seconds (10Hz)
    auto start_time = std::chrono::high_resolution_clock::now();
    
    for (int timestep = 0; timestep < 30; timestep++) {
        auto timestep_start = std::chrono::high_resolution_clock::now();
        
        // Get current sensor data
        data = u->getDataBuffer();
        if (data.size() < 2 * u->getNumberOfSensors()) continue;
        
        // Calculate elapsed time in seconds
        auto elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(
            timestep_start - start_time).count();
        
        // Write timestep data: timestep_id elapsed_time sensor_values...
        sample_file << timestep << " " << std::fixed << std::setprecision(6) << elapsed;
        for (unsigned int i = 0; i < u->getNumberOfSensors(); i++) {
            sample_file << " " << data[i + u->getNumberOfSensors()];
        }
        sample_file << std::endl;
        
        // Wait for next timestep (100ms intervals)
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    
    sample_file.close();
    
    std::cout << " SAVED AS: sample_" << std::setfill('0') << std::setw(2) << sample_counter << ".txt" << std::endl;
    sample_counter++;
    
    std::cout << "Next sample will be: sample_" << std::setfill('0') << std::setw(2) 
              << sample_counter << ".txt" << std::endl;
    std::cout << "Press SPACEBAR for next recording...\n" << std::endl;
}

void FilePublisher::publish_gesture_collection()
{
    if (gesture_mode < 0 ) {
        std::cout << "Invalid gesture mode: " << gesture_mode << std::endl;
        return;
    }
    
    // Wait for sensor system to be ready
    while (u->isRunning()) {
        auto data = u->getDataBuffer();
        if (data.size() >= 2 * u->getNumberOfSensors() && data[1] > 0) {
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    
    std::cout << " Sensor system ready!" << std::endl;
    std::cout << "Press SPACEBAR during the sensor display to record a sample" << std::endl;
    
    // Start the bash display in a separate thread (same as bash mode - shows all sensors)
    std::thread print_thread([&]{
        auto start = std::chrono::high_resolution_clock::now();
        uint64_t time_elapsed_ns;
        int n_print = 0;
        if (print_freq > 0)
        {
            std::vector<skin_data> data;
            while (u->isRunning())
            {
                start = std::chrono::high_resolution_clock::now();

                n_print = 0;

                data = u->getDataBuffer();

                std::cout << "\n";
                std::cout << "\033[0;33mID    | Data\033[0m\n";
                std::cout << "--------------\n";
                for (unsigned int i = 0; i < data.size() / 2; i++)
                {
                    // Show all sensors like bash mode - only skip sensor errors
                    if (data[i + data.size() / 2] >= 43000) continue;
                    
                    if (n_print % 2 == 0)
                        std::cout << "\033[0;33m" << data[i] << " | " << data[i + data.size() / 2] << "\033[0m\n";
                    else
                        std::cout << data[i] << " | " << data[i + data.size() / 2] << "\n";
                    n_print++;
                }
                std::cout << "\n";

                time_elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start).count();
                std::this_thread::sleep_for(std::chrono::nanoseconds((uint64_t)(print_freq * 1000000000) - time_elapsed_ns));
            }
        }
    });
    
    // Main collection loop - just listen for keypress
    while (u->isRunning()) {
        if (kbhit()) {
            char key = getchar();
            if (key == ' ') {  // Spacebar pressed
                collect_gesture_sample();
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    
    print_thread.join();
}

void FilePublisher::publish()
{
    if (gesture_mode >= 0) {
        publish_gesture_collection();
        return;
    }
    
    // Original file publisher code
    std::thread print_thread([&]{
        auto start = std::chrono::high_resolution_clock::now();
        uint64_t time_elapsed_ns;
        int n_print = 0;
        if (print_freq > 0)
        {
            std::vector<skin_data> data;
            while (u->isRunning())
            {
                start = std::chrono::high_resolution_clock::now();

                n_print = 0;

                data = u->getDataBuffer();

                std::cout << "\n";
                std::cout << "\033[0;33mID    | Data\033[0m\n";
                std::cout << "--------------\n";
                for (unsigned int i = 0; i < data.size() / 2; i++)
                {
                    if (!(data[i + data.size() / 2] > thresh && data[i + data.size() / 2] < 43000))
                        continue;
                    if (n_print % 2 == 0)
                        std::cout << "\033[0;33m" << data[i] << " | " << data[i + data.size() / 2] << "\033[0m\n";
                    else
                        std::cout << data[i] << " | " << data[i + data.size() / 2] << "\n";
                    n_print++;
                }
                std::cout << "\n";

                time_elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start).count();
                std::this_thread::sleep_for(std::chrono::nanoseconds((uint64_t)(print_freq * 1000000000) - time_elapsed_ns));
            }
        }
    });

    queue_manager_thread.reset(
        new std::thread([&](){
            while (u->isRunning())
            {
                if (!Q.empty())
                {
                    out << Q.front() << std::endl << std::flush;
                    Q.pop();
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        })
    );

    auto start = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point t;
    uint32_t time_elapsed;
    std::string line = "";
    uint32_t sample_id = 0;

    // Open the file and write sensors UIDs
    out.open(filename, std::ios::binary);
    std::vector<skin_data> data;
    while (u->isRunning())
    {
        u->makeThisThreadWait();
        data = u->getDataBuffer();
        if(data[1] > 0) goto file_writing;
    }
    file_writing:
    for (unsigned int i = 0; i < u->getNumberOfSensors(); i++)
    {
        out << std::to_string(data[i]) <<  " ";
    }
    out << "\n" << std::flush;

    while (u->isRunning())
    {
        t = std::chrono::high_resolution_clock::now();
        time_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(t - start).count();
        line += std::to_string(sample_id++) + " " + std::to_string((float)time_elapsed/1000);
        for (unsigned int i = 0; i < u->getNumberOfSensors(); i++)
        {
            line += " " + std::to_string(data[i + data.size() / 2]);
        }
        Q.push(line);
        line = "";

        u->makeThisThreadWait();
        data = u->getDataBuffer();
    }

    print_thread.join();
}