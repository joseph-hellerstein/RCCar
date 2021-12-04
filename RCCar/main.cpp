#include "RCCar.h"
#include "Arduino.h"
#include "sensor_manager.h"
#include "test_ultra_sonic.h"
#include "test_wheel.h"
#include "test_sensor_manager.h"
#include "test_wheel_manager.h"
#include <iostream>
using namespace std;

#define NULL_VALUE -1 // Indicates a null value

int main() {
    testUltraSonic();
    testWheel();
    testSensorManager();
    testWheelManager();
    /* Test the RCCar */
    setup();
    for (int i=0; i < 10; i++) {
        loop();
        string line = "\nTime: " + std::to_string(arduino_mock.getTime()) + " Iteration: " + std::to_string(i) + "\n";
        cout << line;
    }
    return 0;
};