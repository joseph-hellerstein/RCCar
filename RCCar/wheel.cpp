/*
Abstraction for a wheel with a motor.
*/

#include "common.h"
#include "Arduino.h"
#include "wheel.h"

Wheel::Wheel(int arg_dira_pin, int arg_dirb_pin,
      int arg_enable_pin) {
    this->dira_pin = arg_dira_pin;
    this->dirb_pin = arg_dirb_pin;
    this->enable_pin = arg_enable_pin;
    this->speed = SPEED_HIGH;
    this->isForward = TRUE;
}

void Wheel::goForward() {
   digitalWrite(this->enable_pin, this->speed);
   digitalWrite(this->dira_pin, HIGH);
   digitalWrite(this->dirb_pin, LOW);
   this->isForward = TRUE;
}

void Wheel::init() {
  pinMode(this->dira_pin, OUTPUT);
  pinMode(this->dirb_pin, OUTPUT);
  pinMode(this->enable_pin, OUTPUT);
  analogWrite(this->enable_pin, HIGH);
}

void Wheel::goBackwards() {
   digitalWrite(this->enable_pin, this->speed);
   digitalWrite(this->dira_pin, LOW);
   digitalWrite(this->dirb_pin, HIGH);
   this->isForward = FALSE;
}

void Wheel::setSpeed(int arg_speed) {
    this->speed = arg_speed;
}

void Wheel::stop() {
    digitalWrite(this->enable_pin, SPEED_STOP);
}

int Wheel::getSpeed() {
    return this->speed;
}