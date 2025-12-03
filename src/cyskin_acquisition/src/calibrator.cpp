
#include "calibrator.hpp"

SkinCalibrator::SkinCalibrator(std::shared_ptr<UpdaterInterface> _u , double _thresh, std::string _filename)
{
    u = _u;
    print_freq = 0.1;
    if(_thresh == 0.0)
    {
        std::cout << "The threshold value cannot be 0 when calibrating the skin. Insert a threshold value appropriate to your system\n";
        exit(0);
    }
    thresh = _thresh;
    if (filename.compare("") == 0) filename = "uids.txt";
    else filename = _filename;

    activated = std::vector<bool>(u->getNumberOfSensors(),0);
    
    std::ifstream uids_file;
    uids_file.open(filename);
    if(uids_file)
    {
        start_with_newline = true;
        skin_data ids;
        while (!uids_file.eof())
        {
            uids_file >> cnt_index; 
            uids_file >> ids;
            activated[ids] = true;
            uids_file >> ids; // not needed here, just throw it away
        }
        uids_file.close();
    }
    std::cout << "\nSimple tool to associate the UID of a particular taxel to a position. It is assumed you already have calibrated the position of the sensors. Touch the sensors one by one in the correct order\n\n";
}

SkinCalibrator::~SkinCalibrator()
{
    ;
}

void SkinCalibrator::publish()
{
    std::vector<skin_data> data;
    uint64_t time_elapsed_ns;
    auto start = std::chrono::high_resolution_clock::now();

    std::ofstream uids_file;
    uids_file.open(filename, std::ios_base::app);

    while (u->isRunning())
    {
        start = std::chrono::high_resolution_clock::now();
        data = u->getDataBuffer();
        
        skin_data index; 
        uint16_t cnt = 0;
        for(unsigned int i = 0; i < data.size()/2; i++)
        {
            if ( data[i+data.size()/2] > thresh && data[i+data.size()/2] < 43000 ) 
            {
                cnt++;
                index = i;
            }
        }

        if(cnt == 0) continue;
        
        if(cnt > 1)
        {
            std::cout << "\033[0;33m" << "Warning "<< "\033[0m - More than one taxel activated. Increase the threshold value if necessary\n";
            continue; // Taxel must pressed one by one
        } 
        if(!activated[index]) // If taxel was not already pressed
        {
            activated[index] = true;
            std::cout << "Touched taxel with UID \033[0;33m" << data[index] << "\033[0m - Data saved\n";
            if(start_with_newline)  
                uids_file << "\n" << ++cnt_index << " " << index << " " << data[index];
            else
            {
                uids_file << ++cnt_index << " " << index << " " << data[index];
                start_with_newline = true;
            }
            uids_file.flush();
            #ifdef _WIN32
            Beep(440.0, 4096);
            #else
            // TODO: Implement
            #endif
        }
        time_elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start).count();
        std::this_thread::sleep_for(std::chrono::nanoseconds( (uint64_t)(print_freq*1000000000) - time_elapsed_ns ));
    }

    uids_file.close();
}