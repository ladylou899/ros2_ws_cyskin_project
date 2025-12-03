#ifndef CYNET_STATS_H
#define CYNET_STATS_H

#include <stdint.h>
#include <deque>
#include "cynet_sensor.h"

#define DEF_STATS_WINDOW 150

class CyStats : public CySensorMeasurementProcessor
{

    uint32_t stat_size;
    uint32_t start;
    uint32_t count;
    uint16_t *responses;

    std::deque< std::pair<uint32_t,uint16_t> > min_deq;
    std::deque< std::pair<uint32_t,uint16_t> > max_deq;
    uint32_t min_deq_inc;
    uint32_t max_deq_inc;

    uint32_t avg_sum;
    uint32_t avg_samples;

    uint16_t sliding_window_minmax(uint16_t in,
                                   std::deque< std::pair<uint32_t,uint16_t> > *q,
                                   uint32_t *idx,
                                   uint8_t (*comp)(uint16_t,uint16_t));

    void sliding_window_minimum(uint16_t in);
    void sliding_window_maximum(uint16_t in);
    void sliding_window_average(uint16_t out, uint16_t in);

public:

    uint16_t max;
    uint32_t max_idx;
    uint16_t min;
    uint32_t min_idx;
    uint16_t avg;
    uint16_t std;

    CyStats(CySensor *sensor=0, uint32_t size = DEF_STATS_WINDOW);
    ~CyStats();

    virtual void add_measurement(uint16_t in);
    uint16_t operator[](int i) const;
    void clear();
};

#endif
