#ifndef wheel_manager_h
#define wheel_manager_h

#include "wheel.h"
using namespace std;

#define NUM_WHEEL 4

class SensorManager {
    public:
        Wheel * p_wheels[NUM_WHEEL];
        Wheel * p_fl_wheel; // front left
        Wheel * p_fr_wheel; // front right
        Wheel * p_bl_wheel; // back left
        Wheel * p_br_wheel; // back right

        SensorManager(Wheel *p_fl_wheel, Wheel *p_fr_wheel,
            Wheel *p_bl_wheel, Wheel *br_wheel);
        void init();
        void goForwards();
        void goBackwards();

};
#endif
