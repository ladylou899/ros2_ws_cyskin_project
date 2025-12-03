
#include "updater.h"

Updater::Updater(std::vector<CyIhb *> *_ihbs, double _T, bool _remove_baseline) : UpdaterInterface(_T)
{
    ihbs = _ihbs;
    n_sensors = 0;
    bounded_buffer = 0;
    remove_baseline = _remove_baseline;
    steps_baseline = 0;
    init();
}

void Updater::init()
{
    for (auto ihb : *ihbs)
    {
        for (auto &module : ihb->get_ihb_devs().get_modules())
        {
            for (uint32_t s = 0; s < module.get_sensors().size(); s++)
            {
                n_sensors++;
            }
        }
    }
    buffer_data[0].resize(n_sensors*2);
    buffer_data[1].resize(n_sensors*2);
    baseline = std::vector<uint32_t>(n_sensors,0);
    if(remove_baseline) steps_baseline = 5;  // Increased from 5 to 20 (2 seconds stabilization)
}

void Updater::updateOnce()
{
    uint16_t sensor_id;
    uint16_t module_uid;
    skin_data response;
    skin_data sensor_uid;

    int k = 0;
    for (auto ihb : *ihbs)
    {
        for (auto &module : ihb->get_ihb_devs().get_modules())
        {
            for (uint32_t s = 0; s < module.get_sensors().size(); s++)
            {  
                module_uid = module.get_sui();
                sensor_id = module.get_sensors()[s].get_name();
                sensor_uid = COMPUTE_UID(module_uid,sensor_id);
                response = module.get_sensors()[s].get_measurement();

                if(steps_baseline > 0)
                {
                    baseline[k] = response;
                }
                else
                {
                    buffer_data[bounded_buffer][k] = sensor_uid;
                    buffer_data[bounded_buffer][k+n_sensors] = (int)(response - baseline[k]) > 0 ? (response - baseline[k]) : 0;
                }
                k++;
            }
        }
    }
    if(steps_baseline > 0) steps_baseline--;
}
