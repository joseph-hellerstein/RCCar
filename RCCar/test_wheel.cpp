/*
Tests for Wheel.
*/

#include "Arduino.h"
#include "common.h"
#include "wheel.h"
#include "test_wheel.h"
#include <iostream>
using namespace std;

#define DEFAULT_DIRA_PIN 1
#define DEFAULT_DIRB_PIN 2
#define DEFAULT_ENABLE_PIN 3


void testWheel() {
    Wheel wheel = Wheel(DEFAULT_DIRA_PIN,
          DEFAULT_DIRB_PIN, DEFAULT_ENABLE_PIN);
    /* Get test object */
    
    /* Constructor */
    assert(wheel.dira_pin == DEFAULT_DIRA_PIN);
    assert(wheel.dirb_pin == DEFAULT_DIRB_PIN);
    assert(wheel.enable_pin == DEFAULT_ENABLE_PIN);
    
    /* goForward */
    wheel.goForward();
    assert(wheel.isForward);

    /* goBackwards */
    wheel.goBackwards();
    assert(!wheel.isForward);

    /* setSpeed & getSpeed */
    int new_speed = 25;
    wheel.setSpeed(new_speed);
    assert(wheel.speed == new_speed);
    assert(wheel.getSpeed() == new_speed);

    /* stop */
    wheel.stop();
    assert(wheel.speed == 0);
};