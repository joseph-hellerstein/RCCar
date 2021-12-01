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



int i;
int direction = 0;  // -1 backwards; +1 forwards

UltraSonic back_sensor = UltraSonic(ECHO_BK_PIN, TRIG_BK_PIN);
UltraSonic front_sensor = UltraSonic(ECHO_FT_PIN, TRIG_FT_PIN);
UltraSonic left_sensor = UltraSonic(ECHO_LT_PIN, TRIG_LT_PIN);
UltraSonic right_sensor = UltraSonic(ECHO_RT_PIN, TRIG_RT_PIN);
SensorManager sensor_manager = SensorManager(&front_sensor, &back_sensor, &left_sensor, &right_sensor);

void forward() {
   Serial.println("Forward!");
   direction  = 1;
   digitalWrite(FL_ENABLE_PIN,HIGH); // enable on
   digitalWrite(FL_DIRA_PIN,HIGH); //one way
   digitalWrite(FL_DIRB_PIN,LOW);
   digitalWrite(FR_ENABLE_PIN,HIGH); // enable on
   digitalWrite(FR_DIRA_PIN,HIGH); //one way
   digitalWrite(FR_DIRB_PIN,LOW);
   digitalWrite(BL_ENABLE_PIN,HIGH); // enable on
   digitalWrite(BL_DIRA_PIN,HIGH); //one way
   digitalWrite(BL_DIRB_PIN,LOW);
   digitalWrite(BR_ENABLE_PIN,HIGH); // enable on
   digitalWrite(BR_DIRA_PIN,HIGH); //one way
   digitalWrite(BR_DIRB_PIN,LOW);
}

void backward() {
  direction = -1;
  Serial.println("Backwards!");
  digitalWrite(FL_ENABLE_PIN,HIGH); // enable on
  digitalWrite(FL_DIRA_PIN,LOW); //one way
  digitalWrite(FL_DIRB_PIN,HIGH);
  digitalWrite(FR_ENABLE_PIN,HIGH); // enable on
  digitalWrite(FR_DIRA_PIN,LOW); //one way
  digitalWrite(FR_DIRB_PIN,HIGH);
  digitalWrite(BL_ENABLE_PIN,HIGH); // enable on
  digitalWrite(BL_DIRA_PIN,LOW); //one way
  digitalWrite(BL_DIRB_PIN,HIGH);
  digitalWrite(BR_ENABLE_PIN,HIGH); // enable on
  digitalWrite(BR_DIRA_PIN,LOW); //one way
  digitalWrite(BR_DIRB_PIN,HIGH);
}

void stop() {
  digitalWrite(FL_ENABLE_PIN,LOW); // enable off
  digitalWrite(FR_ENABLE_PIN,LOW); // enable off
  digitalWrite(BL_ENABLE_PIN,LOW); // enable off
  digitalWrite(BR_ENABLE_PIN,LOW); // enable off
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
  pinMode(FL_DIRA_PIN,OUTPUT);
  pinMode(FL_DIRB_PIN,OUTPUT);
  pinMode(FL_ENABLE_PIN,OUTPUT);
  analogWrite(FL_ENABLE_PIN,255);
  pinMode(FR_DIRA_PIN,OUTPUT);
  pinMode(FR_DIRB_PIN,OUTPUT);
  pinMode(FR_ENABLE_PIN,OUTPUT);
  analogWrite(FR_ENABLE_PIN,255);
  pinMode(BL_DIRA_PIN,OUTPUT);
  pinMode(BL_DIRB_PIN,OUTPUT);
  pinMode(BL_ENABLE_PIN,OUTPUT);
  analogWrite(BL_ENABLE_PIN,255);
  pinMode(BR_DIRA_PIN,OUTPUT);
  pinMode(BR_DIRB_PIN,OUTPUT);
  pinMode(BR_ENABLE_PIN,OUTPUT);
  analogWrite(BR_ENABLE_PIN,255);
  Serial.begin(9600);
  mySerial.begin(9600);
  mySerial.println("Starting...");
  last_report_time = millis();
  back_sensor.init();
  front_sensor.init();
  left_sensor.init();
  right_sensor.init();
  delay(100);
}

void loop() {
  Serial.println("loop start");
  front_sensor.update();
  back_sensor.update();
  left_sensor.update();
  right_sensor.update();
  Serial.println(left_sensor.getDistance());
  Serial.println(right_sensor.getDistance());
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

