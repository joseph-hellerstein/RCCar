#include "RCCar.h"
#include "Arduino.h"
#include "sensor_manager.h"
#include "test_ultra_sonic.h"
#include <iostream>
using namespace std;

#define NULL_VALUE -1 // Indicates a null value

int main() {
    testUltraSonic();

    /* Test the RCCar */
    for (int i=0; i < 10; i++) {
        setup();
        string line = "Time: " + std::to_string(arduino_mock.getTime()) + " Iteration: " + std::to_string(i) + "\n";
        cout << line;
    }
    return 0;
};