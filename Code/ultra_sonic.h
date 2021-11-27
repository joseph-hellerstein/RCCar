/*
  ultra_sonic.h - Library for UltraSonic sensor to calculae velocities, etc.
  Created by Joseph L. Hellerstein, November 18, 2021
  Released into the public domain.
*/
#ifndef ultra_sonic_h
#define ultra_sonic_h

#include "Arduino.h"
#ifndef arduino_mocks_h
#include "SR04.h"
#endif

class UltraSonic {
  private:
      long last_distance;  // inches
      long last_time;  // Time in ms
      float speed;  // inches / ms
      SR04 *sr04;
      int echo_pin;
      int trig_pin;
      long getCurrentDistance();
  public:
      UltraSonic(int echo_pin, int trig_pin);
      void init();
      void update();
      bool isTooClose();
      float getSpeed();
      long getDistance();
};

#endif
