#include "RCCar.h"
#include "Arduino.h"
#include <iostream>
using namespace std;

int main() {
    setup();
    for (int i=0; i < 10; i++) {
        setup();
        string line = "Time: " + std::to_string(arduino_mock.getTime()) + "\n";
        cout << line;
    }
        
}