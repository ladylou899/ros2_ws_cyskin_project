#include "skin_publisher.hpp"
#include <fstream>
#ifdef _WIN32
    #include <Windows.h>
#else
    #include <unistd.h>
    #include <math.h>
#endif

class SkinCalibrator : public SkinPublisher
{
private:
    std::string filename;
    uint32_t cnt_index = 0;
    std::vector<bool> activated;
    bool start_with_newline = false;
public:
    SkinCalibrator( std::shared_ptr<UpdaterInterface> _u , double _thresh, std::string _filename );
    ~SkinCalibrator();
    void publish();
};

