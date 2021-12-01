#ifndef sensor_manager_h
#define sensor_manager_h

#include "ultra_sonic.h"
using namespace std;

#define NUM_SENSOR 4

class SensorManager {
    public:
        UltraSonic * p_sensors[NUM_SENSOR];
        UltraSonic * p_front_sensor;
        UltraSonic * p_rear_sensor;
        UltraSonic * p_left_sensor;
        UltraSonic * p_right_sensor;

        SensorManager(UltraSonic *p_front_sensor, UltraSonic *p_rear_sensor,
            UltraSonic *p_left_sensor, UltraSonic *right_sensor);
        void init();
        void update();
        bool isTooClose(bool direction);

};
#endif
