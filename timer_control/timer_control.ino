#include "SevSeg.h"

#define strt  9 
#define down  10
#define up  11
#define clr  12

#define dig1  A1
#define dig2  A0
#define dig3  13
#define dig4  5

#define a 6
#define b 8
#define c A3
#define d A4
#define e A2
#define f 7
#define g A5

SevSeg sevseg;

String inputString = "";  
boolean stringComplete = false;
int charCounter = 0;

void setup() {
   pinMode(strt, INPUT_PULLUP);
   pinMode(down, INPUT_PULLUP);
   pinMode(up, INPUT_PULLUP);
   pinMode(clr, INPUT_PULLUP);
   
   byte numDigits = 4;
   byte digitPins[] = {dig1, dig2, dig3, dig4};
   byte segmentPins[] = {a, b, c, d, e, f, g};
   
   sevseg.begin(P_TRANSISTORS, numDigits, digitPins, segmentPins);
   sevseg.setNumber(8888,3);
   
   Serial.begin(1200);
   inputString.reserve(10);
   delay(1000);
}

void loop() {
  if( !digitalRead(strt) ){
    Serial.println("start");
    while(!digitalRead(strt));
    delay(100);
  }
  if( !digitalRead(down) ){
    Serial.println("down");
    while(!digitalRead(down));
    delay(100);
  }
  if( !digitalRead(up) ){
    Serial.println("up");
    while(!digitalRead(up));
    delay(100);
  }
  if( !digitalRead(clr) ){
    Serial.println("clr");
    while(!digitalRead(clr));
    delay(100);
  }
  if (stringComplete) {

    Serial.print(inputString);
    sevseg.setNumber(inputString.substring(0,4).toInt(),3);
    inputString = "";
    stringComplete = false;
  }
  
  sevseg.refreshDisplay();
}

void serialEvent() {

  while (Serial.available()) {
    char inChar = (char)Serial.read();
    inputString += inChar;
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
