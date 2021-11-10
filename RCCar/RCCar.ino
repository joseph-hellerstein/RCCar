//www.elegoo.com
//2016.12.12

/************************
Exercise the motor using
the L293D chip
************************/
#include <SoftwareSerial.h>
#include <time.h>
#include "SR04.h"


// Bluetooth pins
#define rxPin 11
#define txPin 18
// Ultra sonic pins
#define TRIG_PIN 12
#define ECHO_PIN 13

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
#define CM_PER_INCH 2.54

char inputByte;
long distance;
long last_report_time;

SoftwareSerial mySerial(rxPin, txPin); // RX, TX
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);


int i;
int direction = 0;  // -1 backwards; +1 forwards

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
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  delay(100);
}

void loop() {
  distance=sr04.Distance() / CM_PER_INCH;
  if ((millis() - last_report_time) > REPORT_MILLIS) {
          last_report_time = millis();
          mySerial.print(distance);
          mySerial.println(" in");
      }
  if (distance < 6) {
    if (direction < 0) {
      forward();
    }
    else {
      backward();
    }
    delay(1000);  // Wait for things to change
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
         digitalWrite(L_ENABLE,LOW); // enable off
         digitalWrite(R_ENABLE,LOW); // enable off
         direction = 0;
      }
      if (inputByte==CMD_BACK){
        backward();
      }
    }
}
