//www.elegoo.com
//2016.12.12

/************************
Exercise the motor using
the L293D chip
************************/
#include <stdlib.h>
#include <time.h>
#include "ultra_sonic.h"
#include "Arduino.h"
#include "SoftwareSerial.h"


// Bluetooth pins
#define rxPin 11
#define txPin 18
// Ultra sonic pins. Front and back sensors.
#define TRIG_BK_PIN 12
#define ECHO_BK_PIN 13
#define TRIG_FR_PIN 22
#define ECHO_FR_PIN 23

#define L_DIRA 3
#define L_DIRB 4
#define L_ENABLE 5

#define R_DIRA 8
#define R_DIRB 9
#define R_ENABLE 10

#define CMD_FORWARD 'f'
#define CMD_BACK 'b'
#define CMD_STOP 's'

#define REPORT_MILLIS 1000
// #define CM_PER_INCH 2.54

// #define DISTANCE_MIN 6  // Minimum distance from obstacle

char inputByte;
long distance_fr;
long distance_bk;
long last_report_time;

SoftwareSerial mySerial(rxPin, txPin); // RX, TX
SR04 sr04_bk = SR04(ECHO_BK_PIN,TRIG_BK_PIN);
SR04 sr04_fr = SR04(ECHO_FR_PIN,TRIG_FR_PIN);



int i;
int direction = 0;  // -1 backwards; +1 forwards

/*
// Encapsulates the UltraSonic sensor
class UltraSonic {
  
  private:
      long last_distance;  // inches
      long last_time;  // Time in ms
      float speed;  // inches / ms
      SR04 sr04 = SR04(0, 0);  // Dummy values
      int echo_pin;
      int trig_pin;

  public:
      // Constructor
      UltraSonic(int echo_pin, int trig_pin) {
        this->echo_pin = echo_pin;
        this->trig_pin = trig_pin;
      }
      // Initialize the sensor
      void init() {
        // Initialize the object
        pinMode(this->echo_pin, INPUT);
        pinMode(this->trig_pin, OUTPUT);
        this->sr04 = SR04(echo_pin, trig_pin);
        delay(100);  // Wait for SR04 setup
        this->last_distance = this->sr04.Distance() / CM_PER_INCH;
        this->last_time = millis();
      }
      // Update the sensor
      void update() {
        long cur_time = millis() - this->last_time;
        long cur_distance = this->sr04.Distance() / CM_PER_INCH;
        this->speed = (cur_distance - this->last_distance) / (cur_time - this->last_time);
        this->last_distance = cur_distance;
        this->last_time = cur_time;
      }
      // Determine if too close
      bool isTooClose() {
        if (last_distance < DISTANCE_MIN) {
          return 1 == 1;
        }
        return 1 == 0;
      }
      // Get distance from closest obstacle
      long getDistance() {
        return this->last_distance;
      }
      // Get speed
      float getSpeed() {
        
      }
};
*/

UltraSonic back_sensor = UltraSonic(ECHO_BK_PIN, TRIG_BK_PIN);
UltraSonic front_sensor = UltraSonic(ECHO_FR_PIN, TRIG_FR_PIN);

void forward() {
   Serial.println("Forward!");
   direction  = 1;
   digitalWrite(L_ENABLE,HIGH); // enable on
   digitalWrite(L_DIRA,HIGH); //one way
   digitalWrite(L_DIRB,LOW);
   digitalWrite(R_ENABLE,HIGH); // enable on
   digitalWrite(R_DIRA,HIGH); //one way
   digitalWrite(R_DIRB,LOW);
}

void backward() {
  direction = -1;
  Serial.println("Backwards!");
  digitalWrite(L_ENABLE,HIGH); // enable on
  digitalWrite(L_DIRA,LOW); //one way
  digitalWrite(L_DIRB,HIGH);
  digitalWrite(R_ENABLE,HIGH); // enable on
  digitalWrite(R_DIRA,LOW); //one way
  digitalWrite(R_DIRB,HIGH);
}

void reverse() {
  if (direction < 0) {
      forward();
    }
    else {
      backward();
    }
    delay(1000);  // Wait for things to change
}
 
void setup() {
  //---set pin direction
  pinMode(L_DIRA,OUTPUT);
  pinMode(L_DIRB,OUTPUT);
  pinMode(L_ENABLE,OUTPUT);
  analogWrite(L_ENABLE,255);
  pinMode(R_DIRA,OUTPUT);
  pinMode(R_DIRB,OUTPUT);
  pinMode(R_ENABLE,OUTPUT);
  analogWrite(R_ENABLE,255);
  Serial.begin(9600);
  mySerial.begin(9600);
  mySerial.println("Starting...");
  last_report_time = millis();
  back_sensor.init();
  front_sensor.init();
  delay(100);
}

void loop() {
  // distance_fr = sr04_fr.Distance() / CM_PER_INCH;
  //distance_bk = sr04_bk.Distance() / CM_PER_INCH;
  front_sensor.update();
  back_sensor.update();
  if ((millis() - last_report_time) > REPORT_MILLIS) {
          last_report_time = millis();
          mySerial.print(std::to_string(distance_fr));
          mySerial.print(" in, ");
          mySerial.print(std::to_string(distance_bk));
          mySerial.println(" in");
      }
  //if (distance_fr < DISTANCE_MIN || distance_bk < DISTANCE_MIN) {
  if (front_sensor.isTooClose() || back_sensor.isTooClose()) {
    reverse();
  }
  // Wait for command
  while(mySerial.available()>0){
      inputByte = mySerial.read();
      Serial.println(std::to_string(inputByte));
      if (inputByte==CMD_FORWARD){
         forward();
      }
      if (inputByte==CMD_STOP){
         Serial.println("Stop!");
         digitalWrite(L_ENABLE,LOW); // enable off
         digitalWrite(R_ENABLE,LOW); // enable off
         direction = 0;
      }
      if (inputByte==CMD_BACK){
        backward();
      }
    }
}
