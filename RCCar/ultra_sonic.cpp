#include "Arduino.h"
#include "ultra_sonic.h"
#include <stdlib.h>
#include <time.h>
#include "SR04.h"
#include <assert.h>
#include "common.h"

#define CM_PER_INCH 2.54
#define DISTANCE_MIN 6
#define MIN_ELAPSED_TIME_FOR_UPDATE 50  // ms


// Constructor
UltraSonic::UltraSonic(int echo_pin, int trig_pin) {
  this->echo_pin = echo_pin;
  this->trig_pin = trig_pin;
};

// Initialize the sensor
void UltraSonic::init() {
  // Initialize the object
  pinMode(this->echo_pin, INPUT);
  pinMode(this->trig_pin, OUTPUT);
  this->sr04 = new SR04(this->echo_pin, this->trig_pin);
  delay(100);
  this->last_time = millis();
  this->speed = 0.0;
  this->isInit = TRUE;
  this->last_distance = this->getCurrentDistance();
}

long UltraSonic::getCurrentDistance() {
  assert(this->isInit);  // Must initialize first
  return this->sr04->Distance() / CM_PER_INCH;
}

// Update the sensor
void UltraSonic::update() {
  assert(this->isInit);  // Must initialize first
  long cur_time = millis() - this->last_time;
  long cur_distance = this->getCurrentDistance();
  long time_difference = cur_time - this->last_time;
  if (time_difference > 0) {
      this->speed = (cur_distance - this->last_distance) / time_difference;
  }
  this->last_distance = cur_distance;
  this->last_time = cur_time;
}
   
// Determine if too close
bool UltraSonic::isTooClose() {
  assert(this->isInit);  // Must initialize first
  if (last_distance < DISTANCE_MIN) {
    return 1 == 1;
  }   
  return 1 == 0;
}

// Get distance from closest obstacle
long UltraSonic::getDistance() {
  return this->last_distance;
}   
// Get speed
float UltraSonic::getSpeed() {
    return this->speed;
}   
