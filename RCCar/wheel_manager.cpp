/*
A WheelManager knows the wheels on a car. It handles wheel initialization, and any calculation
that involves multiple wheels.
*/
#include "common.h"
#include "wheel.h"
#include "wheel_manager.h"
using namespace std;


/*-------------------------------------------*/
/*                 Constructor               */
/*-------------------------------------------*/
WheelManager::WheelManager(Wheel *p_fl_wheel, 
    Wheel *p_fr_wheel, 
    Wheel *p_bl_wheel, Wheel *p_br_wheel) {
        this->p_fl_wheel = p_fl_wheel;
        this->p_fr_wheel = p_fr_wheel;
        this->p_bl_wheel = p_bl_wheel;
        this->p_br_wheel = p_br_wheel;
        this->p_wheels[0] = this->p_fl_wheel;
        this->p_wheels[1] = this->p_fr_wheel;
        this->p_wheels[2] = this->p_bl_wheel;
        this->p_wheels[3] = this->p_br_wheel;
};

/*-------------------------------------------*/
/*                 init                      */
/*-------------------------------------------*/
void WheelManager::init() {
    for(int i=0; i < NUM_WHEEL; i++)    {
        (this->p_wheels[i])->init();
    }
};

/*-------------------------------------------*/
/*                 goForward                 */
/*-------------------------------------------*/
void WheelManager::goForward() {
    for(int i=0; i < NUM_WHEEL; i++)    {
        (this->p_wheels[i])->goForward();
    }
};

/*-------------------------------------------*/
/*                goBackwards                */
/*-------------------------------------------*/
void WheelManager::goBackwards() {
    for(int i=0; i < NUM_WHEEL; i++)    {
        (this->p_wheels[i])->goBackwards();
    }
};

/*-------------------------------------------*/
/*                stop                       */
/*-------------------------------------------*/
void WheelManager::stop() {
    for(int i=0; i < NUM_WHEEL; i++)    {
        (this->p_wheels[i])->stop();
    }
};