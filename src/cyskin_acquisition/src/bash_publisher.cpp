
#include "bash_publisher.hpp"

BashPublisher::BashPublisher(std::shared_ptr<UpdaterInterface> _u , double _print_freq, double _thresh)
{
    u = _u;
    print_freq = _print_freq;
    thresh = _thresh;
    if(print_freq <= 0)
    {
        std::cout << "Insert a value for print_freq > 0 to write data on bash\n";
        exit(0);
    }
}

BashPublisher::~BashPublisher()
{
    ;
}

void BashPublisher::publish()
{
    std::vector<skin_data> data;
    int n_print = 0;

    std::cout << "Writing skin data on bash" << std::endl;

    uint64_t time_elapsed_ns;
    auto start = std::chrono::high_resolution_clock::now();

    while (u->isRunning())
    {
        start = std::chrono::high_resolution_clock::now();

        n_print = 0;
            
        data = u->getDataBuffer();
        
        std::cout << "\n";
        std::cout << "\033[0;33mID    | Data\033[0m\n";
        std::cout << "--------------\n";
        for(unsigned int i = 0; i < data.size()/2; i++)
        {
            // Show ALL sensors when thresh=0, otherwise apply filtering
            bool show_sensor = (thresh == 0.0) || (data[i+data.size()/2] > thresh && data[i+data.size()/2] < 43000);
            
            if (!show_sensor) continue;
            
            if (n_print%2 == 0)
                std::cout << "\033[0;33m" << data[i] << " | " << data[i+data.size()/2] << "\033[0m\n";
                        //std::cout << "\033[1;31mbold red text\033[0m\n";
            else
                std::cout << data[i] << " | " << data[i+data.size()/2] << "\n";
            n_print++;
        }
        std::cout << "\n";

        time_elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start).count();
        std::this_thread::sleep_for(std::chrono::nanoseconds( (uint64_t)(print_freq*1000000000) - time_elapsed_ns ));
    }
}