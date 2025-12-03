

// Communication types
#define CT_SHARED_MEM 0
#define CT_ROS 1
#define CT_ROS2 4
#define CT_PRINT 2
#define CT_FILE 3
// Acquisition types
#define AT_STREAM 0
#define AT_EVENTS 1

#include "skin_publisher.hpp"
#include "ros_publisher.hpp"
#include "bash_publisher.hpp"
#include "file_publisher.hpp"
#include "calibrator.hpp"
#include "shared_memory_publisher.hpp"
#include <csignal>
#include <cynetwork.h>
#include <updater.h>
#include <updater_fake.h>

std::shared_ptr<UpdaterInterface> u;
std::shared_ptr<SkinPublisher> sp;
uint16_t communication_type = CT_PRINT;
uint16_t acquisition_type = AT_STREAM;
bool fake = false;
double sampling_time = 0.1;
double print_freq = 1;
double thresh = 0.0;
std::string filename = "";
bool remove_baseline = false;
int16_t bus_num = -1;
bool calibration = false;
int gesture_mode = -1;  // -1 = normal mode, 0-... = gesture collection mode
#if HARDWARE_SUPPORT
CyNetwork *net;
#endif


void signalHandler( int signum ) 
{
    u->stopUpdater();
    net->stop_skin_acquisition();
}

void print_help() 
{
    std::cout << "Helper:\n";
    std::cout << "  -h; --help: display this message and exit\n";
    std::cout << "  --sampling_time: sampling time in seconds. Default: 0.1\n";
    std::cout << "  --bus: bus number.\n";
    std::cout << "  --buffer: options = [ bash ";  
        std::cout << "| shared_memory ";
        std::cout << "| file ";
        #if ROS_SUPPORT 
        std::cout << "| ros "; 
        #endif // ROS_SUPPORT
        #if ROS_SUPPORT 
        std::cout << "| ros2 "; 
        #endif // ROS_SUPPORT
        std::cout << "]. Default: bash\n";
    std::cout << "            bash: print skin data on bash\n";
    std::cout << "            shared_memory: write skin data on a shared area\n";
    std::cout << "            file: write data into a .txt file\n";
    #if ROS_SUPPORT
    std::cout << "            ros: write skin data on a ros topic\n";
    #endif // ROS_SUPPORT

    //std::cout << "  --stream: consider all the skin data \n";
    //std::cout << "  --events: only consider activated sensors \n";
    std::cout << "  --thresh: available only when buffer=bash. Print robot skin data > thresh. Default:0\n";
    std::cout << "  --remove_baseline: remove the baseline from the taxel responses. \n";
    std::cout << "  --calibration: allow for pressing on the taxels one by one and save their UID on a file with default name ids.txt. When this option is enable, the buffer cannot be selected\n";
    std::cout << "  --gesture: gesture collection mode. Usage: --gesture <0-5> (number of fingers). Collects 3-second samples on keypress.\n";
    std::cout << "  --fake: publish fake data instead of reading them from the hardware. Useful for testing\n";
    std::cout << "  --print_freq: value in seconds. Put 0 to disable (not possible if buffer=bash).  Default:1.0\n";
    std::cout << "  --filename: available only when buffer=file or the calibration option is enabled. Write data on a file with a specific filename.\n";
}

#if HARDWARE_SUPPORT
CyComm *GetCySkinComm()
{
    #if __linux__
        return new CyCommPCan();
    #endif // __linux__
    #if defined(_WIN32)
        return new CyCommEsdCan();
    #endif // WIN32
}

void start_skin_loop(CyNetwork *net, CyBuffer<CyCommRxData> *recv_buf)
{
    net->skin_loop(*recv_buf);
}
#endif // HARDWARE_SUPPORT

void publish_skin_data()
{
    if(calibration){
        sp = std::make_unique<SkinCalibrator>(u, thresh, filename);    
        sp->publish();
        return;
    }
    switch (communication_type)
    {
        case CT_PRINT:
            sp = std::make_unique<BashPublisher>(u, print_freq, thresh);    
            sp->publish();
            break;
        case CT_SHARED_MEM:
            sp = std::make_unique<SharedMemoryPublisher>(u, print_freq, thresh);  
            sp->publish();
            break;
        case CT_FILE:
            if (gesture_mode >= 0) {
                sp = std::make_unique<FilePublisher>(u, filename, print_freq, thresh, gesture_mode);
            } else {
                sp = std::make_unique<FilePublisher>(u, filename, print_freq, thresh);
            }
            sp->publish();
            break;
        #if ROS_SUPPORT
            case CT_ROS:
            ros::init(argc, argv, "skin_ros_publisher");
            ros::NodeHandle n;
            ros::Publisher skin_pub = n.advertise<skin_ros_support::skin_raw_msg>("/skin/raw_data", 1000);
            sp = std::make_unique<RosPublisher>(u, skin_pub, thresh, print_freq);
            break;
        #endif // ROS_SUPPORT
        #if ROS2_SUPPORT
        case CT_ROS2:
            // Initialize ROS 2 without relying on main's argc/argv here
            rclcpp::init(0, nullptr);
            sp = std::make_unique<ROS2Publisher>(u, thresh, print_freq);
            sp->publish();
            rclcpp::shutdown();
            break;
        #endif // ROS2_SUPPORT
                    
    }
}

#if HARDWARE_SUPPORT
void real_data_loop()
{
    CyComm *comm;

    comm = GetCySkinComm();
    if (!comm)
    {
        return;
    }

    // Initialize the network
    net = new CyNetwork(comm);

    // Define a buffer for receiving data
    CyBuffer<CyCommRxData> recv_buf;

    // Define a vector of ihbs
    std::vector<CyIhb *> ihbs;

    if(bus_num >= 0)
        net->get_comm()->add_bus(bus_num);
    else
    {
        // Search on every buses
        for (int i = 0; i < 256; i++)
            net->get_comm()->add_bus(i);
    }

    // If at lest one bus is open
    if (net->get_comm()->get_open_buses().size())
    {

        if (net->get_comm()->get_open_buses().size() == 1)
            std::cout << "1 Bus Opened\n";
        else
            std::cout << net->get_comm()->get_open_buses().size() << " Buses Opened\n";

        // Switching to Application phase
        net->switch_phase(CY_PHASE_APPLICATION);

        // Getting network structure
        std::cout << "Getting network structure\n";
        ihbs = net->get_network_structure(true);

        // If IHBs are detected
        if (ihbs.size())
        {
            std::cout << "Found " << ihbs.size() << " IHBs\n" ;

            // Switching skin to application phase
            net->switch_skin_phase(CY_PHASE_APPLICATION);

            ihbs = net->get_network_structure(true);

            // Initalize the acquisition procedure
            net->get_comm()->get_dispatcher()->subscribe(CyBroadcast, &recv_buf);
            net->start_skin_acquisition();

            // Run the acquisition in background
            std::thread tr(start_skin_loop, net, &recv_buf);
            std::cout << "Acquisition Started\n";

            u = std::make_unique<Updater>(&ihbs,sampling_time, remove_baseline);            

            u->update();
            
            // write the skin responses
            publish_skin_data();

            tr.join();
            net->stop_skin_acquisition();
        }
        else
        {
            std::cout << "No IHBs Found\n";
            return;
        }
    }
    else
    {
        std::cout << "No Bus Opened\n";
        return;
    }
}
#endif // HARDWARE_SUPPORT

void fake_data_loop()
{
    std::cout << "Generating fake data from skin patch composed of 61 sensors\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    u = std::make_unique<UpdaterFake>(sampling_time);            
    u->update();
    publish_skin_data();
}

int main(int argc, char **argv)
{   
    // -- ARG PARSE -- //

    for (int i = 1; i < argc; i++)
    {
        // Help
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
        {
            print_help();
            return -1;
        }
        // Sampling time
        else if (strcmp(argv[i], "--sampling_time") == 0)
        {
            sampling_time = std::atof(argv[i+1]);
        }
        // Communication type
        else if (strcmp(argv[i], "--buffer") == 0)
        {
            if (strcmp(argv[i+1], "bash") == 0) communication_type = CT_PRINT;
            else if (strcmp(argv[i+1], "shared_memory") == 0)
            {
                communication_type = CT_SHARED_MEM;
            }
            else if (strcmp(argv[i+1], "file") == 0)
            {
                communication_type = CT_FILE;
            }
            else if (strcmp(argv[i+1], "ros") == 0)
            {
                #if ROS_SUPPORT
                communication_type = CT_ROS;
                #else
                std::cout << "ROS support is not enabled\n"; 
                exit(EXIT_SUCCESS);
                #endif // ROS_SUPPORT
            }
            else if (strcmp(argv[i+1], "ros2") == 0)
            {
                #if ROS2_SUPPORT
                communication_type = CT_ROS2;
                #else
                std::cout << "ROS2 support is not enabled\n"; 
                exit(EXIT_SUCCESS);
                #endif // ROS2_SUPPORT
            }
            else 
            {
                std::cout << "Buffer option " << argv[i+1] << " not recognized\n"; 
                exit(EXIT_FAILURE);
            }
        }
        // Acquisition types
        else if (strcmp(argv[i], "--stream") == 0)
        {
            acquisition_type = AT_STREAM;
        }
        else if (strcmp(argv[i], "--events") == 0)
        {
            std::cout << "Event transmission is not supported yet\n"; exit(EXIT_SUCCESS);
            acquisition_type = AT_EVENTS;
        }
        // Bus
        else if (strcmp(argv[i], "--bus") == 0)
        {
            bus_num = std::atoi(argv[i+1]);;
        }
        // Other options
        else if (strcmp(argv[i], "--print_freq") == 0)
        {
            print_freq = std::atof(argv[i+1]);
        }
        else if (strcmp(argv[i], "--remove_baseline") == 0)
        {
            remove_baseline = true;
        }
        else if (strcmp(argv[i], "--thresh") == 0)
        {
            thresh = std::atof(argv[i+1]);
        }
        else if (strcmp(argv[i], "--calibration") == 0)
        {
            calibration = true;
        }
        else if (strcmp(argv[i], "--fake") == 0)
        {
            fake = true;
        }
        else if (strcmp(argv[i], "--filename") == 0)
        {
                filename = argv[i+1];
        }
        else if (strcmp(argv[i], "--gesture") == 0)
        {
            gesture_mode = std::atoi(argv[i+1]);
            if (gesture_mode < 0 ) {
                std::cout << "Error: --gesture must be followed by a number 0-5 (number of fingers)\n";
                return -1;
            }
            communication_type = CT_FILE;  // Force file mode for gesture collection
        }
        // Error
        else
        {
            std::string s = argv[i];
            if ( (s.substr(0,2) == "--") || (s.substr(0,1) == "-") ) 
            {
                std::cout << "Error: Invalid argument:  " << argv[i] << "\n" ;
                return -1;
            }
            continue;
        }
    }

    // -- END OF ARG PARSE -- //
    
    signal(SIGINT, signalHandler);

    if (!fake)
    {
        #if HARDWARE_SUPPORT
        real_data_loop(); // better to implement a child class rather than this 
        #else
        std::cout << "Hardware support not enabled. Please run with the option --fake or compile with the hardware support\n"; 
        #endif // HARDWARE_SUPPORT
    }
    else fake_data_loop();
}
