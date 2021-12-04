//www.elegoo.com
//2016.12.12

/************************
Exercise the motor using
the L293D chip
************************/
#include "common.h"
#include "SoftwareSerial.h"
#include "SR04.h"
#include "ultra_sonic.h"
#include "sensor_manager.h"
#include "wheel_manager.h"
#include "wheel.h"


// Bluetooth pins
#define RX_PIN 11
#define TX_PIN 18
// Ultra sonic pins. Front and back sensors.
// Back
#define TRIG_BK_PIN 12
#define ECHO_BK_PIN 13
// Front
#define TRIG_FT_PIN 22
#define ECHO_FT_PIN 23
// Left
#define TRIG_LT_PIN 34
#define ECHO_LT_PIN 35
// Right
#define TRIG_RT_PIN 36
#define ECHO_RT_PIN 37

#define FL_DIRA_PIN 3
#define FL_DIRB_PIN 4
#define FL_ENABLE_PIN 5

#define FR_DIRA_PIN 8
#define FR_DIRB_PIN 9
#define FR_ENABLE_PIN 10

#define BL_DIRA_PIN 29
#define BL_DIRB_PIN 26
#define BL_ENABLE_PIN 27

#define BR_DIRA_PIN 31
#define BR_DIRB_PIN 30
#define BR_ENABLE_PIN 33

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

SoftwareSerial mySerial(RX_PIN, TX_PIN); // RX, TX
Wheel fl_wheel = Wheel(FL_DIRA_PIN, FL_DIRB_PIN, FL_ENABLE_PIN);
Wheel fr_wheel = Wheel(FR_DIRA_PIN, FR_DIRB_PIN, FR_ENABLE_PIN);
Wheel bl_wheel = Wheel(BL_DIRA_PIN, BL_DIRB_PIN, BL_ENABLE_PIN);
Wheel br_wheel = Wheel(BR_DIRA_PIN, BR_DIRB_PIN, BR_ENABLE_PIN);
WheelManager wheel_manager = WheelManager(&fl_wheel,
    &fr_wheel, &bl_wheel, &br_wheel);


int i;
bool isForward = TRUE;  //  False: backwards; True: forwards

UltraSonic back_sensor = UltraSonic(ECHO_BK_PIN, TRIG_BK_PIN);
UltraSonic front_sensor = UltraSonic(ECHO_FT_PIN, TRIG_FT_PIN);
UltraSonic left_sensor = UltraSonic(ECHO_LT_PIN, TRIG_LT_PIN);
UltraSonic right_sensor = UltraSonic(ECHO_RT_PIN, TRIG_RT_PIN);
SensorManager sensor_manager = SensorManager(
  &front_sensor, &back_sensor, &left_sensor, &right_sensor);

void forward() {
   Serial.println("Forward!");
   isForward  = TRUE;
   wheel_manager.goForward();
}

void backward() {
  isForward = FALSE;
  Serial.println("Backwards!");
  wheel_manager.goBackwards();
}

void stop() {
  Serial.println("Stopped!");
  wheel_manager.stop();
}

void reverse() {
  if (isForward) {
      backward();
    }
    else {
      forward();
    }
    delay(1000);  // Wait for things to change
}
 
void setup() {
  //---set pin isForward
  wheel_manager.init();
  Serial.begin(9600);
  mySerial.begin(9600);
  mySerial.println("\n\nStarting...");
  last_report_time = millis();
  sensor_manager.init();
  delay(100);
}

void loop() {
  Serial.println("loop start");
  sensor_manager.update();
  Serial.println(left_sensor.getDistance());
  Serial.println(right_sensor.getDistance());
  if ((millis() - last_report_time) > REPORT_MILLIS) {
          last_report_time = millis();
          mySerial.print(distance_fr);
          mySerial.print(" in, ");
          mySerial.print(distance_bk);
          mySerial.println(" in");
      }
  if (sensor_manager.isTooClose(isForward)) {
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
        isForward = 0;
    }
    if (inputByte==CMD_BACK){
      backward();
    }
  }
}