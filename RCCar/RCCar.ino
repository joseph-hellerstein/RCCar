//www.elegoo.com
//2016.12.12

/************************
Exercise the motor using
the L293D chip
************************/
#include <SoftwareSerial.h>
#include <stdlib.h>
#include <time.h>
#include "SR04.h"
#include "ultra_sonic.h"


// Bluetooth pins
#define rxPin 11
#define txPin 18
// Ultra sonic pins. Front and back sensors.
#define TRIG_BK_PIN 12
#define ECHO_BK_PIN 13
#define TRIG_FFR_PIN 22
#define ECHO_FFR_PIN 23

#define FL_DIRA 3
#define FL_DIRB 4
#define FL_ENABLE 5

#define FR_DIRA 8
#define FR_DIRB 9
#define FR_ENABLE 10

#define BL_DIRA 29
#define BL_DIRB 26
#define BL_ENABLE 27

#define BR_DIRA 31
#define BR_DIRB 30
#define BR_ENABLE 33

#define CMD_FORWARD 'f'
#define CMD_BACK 'b'
#define CMD_STOP 's'

#define REPORT_MILLIS 1000
// #define CM_PEFR_INCH 2.54

// #define DISTANCE_MIN 6  // Minimum distance from obstacle

char inputByte;
long distance_fr;
long distance_bk;
long last_report_time;

SoftwareSerial mySerial(rxPin, txPin); // RX, TX
SR04 sr04_bk = SR04(ECHO_BK_PIN,TRIG_BK_PIN);
SR04 sr04_fr = SR04(ECHO_FFR_PIN,TRIG_FFR_PIN);



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
        this->last_distance = this->sr04.Distance() / CM_PEFR_INCH;
        this->last_time = millis();
      }
      // Update the sensor
      void update() {
        long cuFR_time = millis() - this->last_time;
        long cuFR_distance = this->sr04.Distance() / CM_PEFR_INCH;
        this->speed = (cuFR_distance - this->last_distance) / (cuFR_time - this->last_time);
        this->last_distance = cuFR_distance;
        this->last_time = cuFR_time;
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
UltraSonic front_sensor = UltraSonic(ECHO_FFR_PIN, TRIG_FFR_PIN);

void forward() {
   Serial.println("Forward!");
   direction  = 1;
   digitalWrite(FL_ENABLE,HIGH); // enable on
   digitalWrite(FL_DIRA,HIGH); //one way
   digitalWrite(FL_DIRB,LOW);
   digitalWrite(FR_ENABLE,HIGH); // enable on
   digitalWrite(FR_DIRA,HIGH); //one way
   digitalWrite(FR_DIRB,LOW);
   digitalWrite(BL_ENABLE,HIGH); // enable on
   digitalWrite(BL_DIRA,HIGH); //one way
   digitalWrite(BL_DIRB,LOW);
   digitalWrite(BR_ENABLE,HIGH); // enable on
   digitalWrite(BR_DIRA,HIGH); //one way
   digitalWrite(BR_DIRB,LOW);
}

void backward() {
  direction = -1;
  Serial.println("Backwards!");
  digitalWrite(FL_ENABLE,HIGH); // enable on
  digitalWrite(FL_DIRA,LOW); //one way
  digitalWrite(FL_DIRB,HIGH);
  digitalWrite(FR_ENABLE,HIGH); // enable on
  digitalWrite(FR_DIRA,LOW); //one way
  digitalWrite(FR_DIRB,HIGH);
  digitalWrite(BL_ENABLE,HIGH); // enable on
  digitalWrite(BL_DIRA,LOW); //one way
  digitalWrite(BL_DIRB,HIGH);
  digitalWrite(BR_ENABLE,HIGH); // enable on
  digitalWrite(BR_DIRA,LOW); //one way
  digitalWrite(BR_DIRB,HIGH);
}

void stop() {
  digitalWrite(FL_ENABLE,LOW); // enable off
  digitalWrite(FR_ENABLE,LOW); // enable off
  digitalWrite(BL_ENABLE,LOW); // enable off
  digitalWrite(BR_ENABLE,LOW); // enable off
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
  pinMode(FL_DIRA,OUTPUT);
  pinMode(FL_DIRB,OUTPUT);
  pinMode(FL_ENABLE,OUTPUT);
  analogWrite(FL_ENABLE,255);
  pinMode(FR_DIRA,OUTPUT);
  pinMode(FR_DIRB,OUTPUT);
  pinMode(FR_ENABLE,OUTPUT);
  analogWrite(FR_ENABLE,255);
  pinMode(BL_DIRA,OUTPUT);
  pinMode(BL_DIRB,OUTPUT);
  pinMode(BL_ENABLE,OUTPUT);
  analogWrite(BL_ENABLE,255);
  pinMode(BR_DIRA,OUTPUT);
  pinMode(BR_DIRB,OUTPUT);
  pinMode(BR_ENABLE,OUTPUT);
  analogWrite(BR_ENABLE,255);
  Serial.begin(9600);
  mySerial.begin(9600);
  mySerial.println("Starting...");
  last_report_time = millis();
  back_sensor.init();
  front_sensor.init();
  delay(100);
}

void loop() {
  Serial.println("loop start");
  front_sensor.update();
  back_sensor.update();
  if ((millis() - last_report_time) > REPORT_MILLIS) {
          last_report_time = millis();
          mySerial.print(distance_fr);
          mySerial.print(" in, ");
          mySerial.print(distance_bk);
          mySerial.println(" in");
      }
  //if (distance_fr < DISTANCE_MIN || distance_bk < DISTANCE_MIN) {
  if (front_sensor.isTooClose() || back_sensor.isTooClose()) {
    reverse();
  }
  // Wait for command
  while(mySerial.available()>0){
      inputByte = mySerial.read();
      Serial.println(inputByte);
      if (inputByte==CMD_FORWARD){
         forward();
      }
      if (inputByte==CMD_STOP){
         Serial.println("Stop!");
         stop();
         direction = 0;
      }
      if (inputByte==CMD_BACK){
        backward();
      }
    }
}
