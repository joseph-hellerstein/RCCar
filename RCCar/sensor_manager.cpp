/*
A SensorManager knows the sensors on a car. It handles sensor initialization, and any calculation
that involves multiple sensors.
*/
#include "common.h"
#include "ultra_sonic.h"
#include "sensor_manager.h"
using namespace std;


/*-------------------------------------------*/
/*                 Constructor               */
/*-------------------------------------------*/
SensorManager::SensorManager(UltraSonic *p_front_sensor, UltraSonic *p_rear_sensor, 
    UltraSonic *p_left_sensor, UltraSonic *p_right_sensor) {
        this->p_front_sensor = p_front_sensor;
        this->p_rear_sensor = p_rear_sensor;
        this->p_left_sensor = p_left_sensor;
        this->p_right_sensor = p_right_sensor;
        this->p_sensors[0] = this->p_front_sensor;
        this->p_sensors[1] = this->p_rear_sensor;
        this->p_sensors[2] = this->p_left_sensor;
        this->p_sensors[3] = this->p_right_sensor;
};

/*-------------------------------------------*/
/*                 init                      */
/*-------------------------------------------*/
void SensorManager::init() {
    for(int i=0; i < NUM_SENSOR; i++)    {
        (this->p_sensors[i])->init();
    }
};

/*-------------------------------------------*/
/*                 update                      */
/*-------------------------------------------*/
void SensorManager::update() {
    for(int i=0; i < NUM_SENSOR; i++)    {
        (this->p_sensors[i])->update();
    }
};

/*-------------------------------------------*/
/*             isTooClose                    */
/*-------------------------------------------*/
bool SensorManager::isTooClose(bool direction) {
    bool result;
    if (direction) {
        result =  this->p_front_sensor->isTooClose();
    }
    else {
        result = this->p_rear_sensor->isTooClose();
    }
    return result;
};
