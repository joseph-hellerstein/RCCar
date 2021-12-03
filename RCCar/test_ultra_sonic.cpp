/*
Tests for UltraSonic.
*/

#include "Arduino.h"
#include "common.h"
#include "ultra_sonic.h"
#include "test_ultra_sonic.h"
#include <iostream>
using namespace std;

#define DEFAULT_ECHO_PIN 1
#define DEFAULT_TRIG_PIN 2

class TestUltraSonic{
    public:
        int echo_pin = DEFAULT_ECHO_PIN;
        int trig_pin = DEFAULT_TRIG_PIN;
        UltraSonic ultra_sonic = UltraSonic(NULL_INT, NULL_INT);
        TestUltraSonic(int echo_pin, int trig_pin){
            if (echo_pin != NULL_INT) {
                this->echo_pin = echo_pin;
            }
            if (trig_pin != NULL_INT) {
                this->trig_pin = trig_pin;
            }
            this->ultra_sonic = UltraSonic(this->echo_pin, this->trig_pin);
            this->ultra_sonic.init();
        }

};

void testUltraSonic() {
    /* Get test object */
    TestUltraSonic test_ultra_sonic = TestUltraSonic(
        DEFAULT_ECHO_PIN, DEFAULT_TRIG_PIN);
    UltraSonic ultra_sonic = test_ultra_sonic.ultra_sonic;
    
    /* Constructor */
    assert(ultra_sonic.echo_pin == DEFAULT_ECHO_PIN);
    assert(ultra_sonic.trig_pin == DEFAULT_TRIG_PIN);

    /* getCurrentDistance */
    assert(ultra_sonic.getCurrentDistance() > 0);

    /* getDistance */
    ultra_sonic.update();
    assert(ultra_sonic.getDistance() > 0);
};
