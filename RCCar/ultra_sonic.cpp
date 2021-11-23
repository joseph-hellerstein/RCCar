#include "Arduino.h"
#include "ultra_sonic.h"
#include <stdlib.h>
#include <time.h>
#include "SR04.h"

#define CM_PER_INCH 2.54
#define DISTANCE_MIN 6


// Constructor
UltraSonic::UltraSonic(int echo_pin, int trig_pin) {
  this->echo_pin = echo_pin;
  this->trig_pin = trig_pin;
}   

// Initialize the sensor
void UltraSonic::init() {
  // Initialize the object
  pinMode(this->echo_pin, INPUT);
  pinMode(this->trig_pin, OUTPUT);
  this->sr04 = new SR04(echo_pin, trig_pin);
  delay(100);
  this->last_distance = this->getCurrentDistance();
  this->last_time = millis();
}

long UltraSonic::getCurrentDistance() {
  return this->sr04->Distance() / CM_PER_INCH;
}

// Update the sensor
void UltraSonic::update() {
  long cur_time = millis() - this->last_time;
  long cur_distance = this->getCurrentDistance();
  this->speed = (cur_distance - this->last_distance) / (cur_time - this->last_time);
  this->last_distance = cur_distance;
  this->last_time = cur_time;
}
   
// Determine if too close
bool UltraSonic::isTooClose() {
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
float getSpeed() {

}   
