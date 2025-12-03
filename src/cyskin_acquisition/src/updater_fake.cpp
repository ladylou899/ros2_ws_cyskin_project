
#include "updater_fake.h"

UpdaterFake::UpdaterFake(double _T) : UpdaterInterface(_T)
{
    n_sensors = 61;
    bounded_buffer = 0;
    init();
}

void UpdaterFake::init()
{
    buffer_data[0].resize(n_sensors*2);
    buffer_data[1].resize(n_sensors*2);
    // Fill with fake ids
    for (unsigned int i = 0; i < n_sensors; i++)
    {
        buffer_data[0][i] = i+1;
        buffer_data[1][i] = i+1;
    }
}

void UpdaterFake::updateOnce()
{
    for (unsigned int i = 0; i < n_sensors; i++)
    {
        buffer_data[bounded_buffer][i+n_sensors] = 10000 + rand()%1000;
    }
}
