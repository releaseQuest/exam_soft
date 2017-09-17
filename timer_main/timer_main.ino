#include "MsTimer2.h"
#include "SevSeg.h"
#include "TimerOne.h"
#include "Servo.h"

#define btnInt 3
#define btn0 8
#define btn1 11
#define btn2 10

#define srv 2

#define dig1 7
#define dig2 6
#define dig3 5
#define dig4 4

#define a A0
#define b A1
#define c A2
#define d A3
#define e A4
#define f A5
#define g 13

#define LEDs 9

SevSeg sevseg;
Servo servo1;
String inputString = "";
boolean stringComplete = false;

int minutesCounter = 0;
int displayTime = 8000;
int timeBuf = 0;
int pressCounter = 0;
bool downFlag = false;
bool btnPressedFlag = false;

bool prevState = LOW;
bool started = false;
bool isPaused = true;
void setup() {
  pinMode(btnInt, INPUT_PULLUP);
  pinMode(btn0, INPUT_PULLUP);
  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);

  pinMode(btn2, INPUT_PULLUP);

  byte numDigits = 4;
  byte digitPins[] = {dig1, dig2, dig3, dig4};
  byte segmentPins[] = {a, b, c, d, e, f, g};

  sevseg.begin(N_TRANSISTORS, numDigits, digitPins, segmentPins);
  
  MsTimer2::set(10, refreshDisp);
  MsTimer2::start();
  
  delay(100);
  servo1.attach(srv);
  servo1.write(100);
  delay(2000);
  servo1.detach();

  Serial.begin(1200);
  inputString.reserve(10);

  sevseg.setNumber(8000, 3);

  attachInterrupt(1, btnServe, LOW);

  Serial.println("8000");
}

void loop() {
  if (btnPressedFlag) {
    delay(30);
    
    if (!digitalRead(btn0) && digitalRead(btn1) && digitalRead(btn2) && pressCounter <= 1) {
      pressCounter++;
      while (!digitalRead(btn0));
    } else if (!digitalRead(btn1) && digitalRead(btn0) && digitalRead(btn2) && pressCounter >= 2 && pressCounter <= 5) {
      pressCounter++;
      while (!digitalRead(btn1));
    } else if (!digitalRead(btn2) && digitalRead(btn0) && digitalRead(btn1) && pressCounter > 5) {
      Timer1.detachInterrupt();
      
      servo1.attach(srv);
      servo1.write(0);
      delay(1000);
      servo1.write(100);
      delay(1000);
      servo1.detach();
      
      pressCounter = 0;
      
      if(started){
          Timer1.initialize(1000000);
          Timer1.attachInterrupt(Timer1_action);
      }
      
    } else if(!digitalRead(btn0) || !digitalRead(btn1) || !digitalRead(btn2)) {
      pressCounter = 0;
      timeBuf = displayTime - 100;
      downFlag = true;
      Timer1.initialize(100000);
      Timer1.attachInterrupt(Timer1_action);
    }
    delay(20);
    btnPressedFlag = false;
    attachInterrupt(1, btnServe, LOW);
  }
  
  if (stringComplete) {

    if (inputString == "start\r\n") {
      if(isPaused){
        Timer1.initialize(1000000);
        sevseg.setNumber(displayTime, 3);
        Serial.println( String(displayTime) );
        Timer1.attachInterrupt(Timer1_action);
        started = true;
        isPaused = false;
      } else{
        Timer1.detachInterrupt();
        sevseg.setNumber(displayTime, 3);
        Serial.println( String(displayTime) );
        isPaused = true;        
      }
    }
    if (inputString == "clr\r\n") {
      Timer1.detachInterrupt();
      displayTime = 8000;
      minutesCounter = 0;
      sevseg.setNumber(displayTime, 3);
      Serial.println( String(displayTime) );
      started = false;
    }
    if (inputString == "up\r\n") {
      displayTime += 100;
      sevseg.setNumber(displayTime, 3);
      Serial.println(String(displayTime));
    }
    if (inputString == "down\r\n") {
      displayTime -= 100;
      sevseg.setNumber(displayTime, 3);
      Serial.println(String(displayTime));

    }
    inputString = "";
    stringComplete = false;
  }
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

void Timer1_action() {
  digitalWrite(LEDs, prevState);
  prevState = !prevState;

  if (minutesCounter == 0) {
    displayTime = displayTime - 40;
    minutesCounter = 60;
  }
  
  if (displayTime == timeBuf && downFlag) {
    downFlag = false;
    timeBuf = 0;
    Timer1.initialize(1000000);
  }
  
  if (displayTime <= 0) {
    sevseg.setNumber(0, 3);
    Serial.println(String(0));
    Timer1.detachInterrupt();
    return;
  }
  displayTime--;
  minutesCounter--;
  
  sevseg.setNumber(displayTime, 3);
  Serial.println(String(displayTime));
}

void btnServe() {
  btnPressedFlag = true;
  detachInterrupt(1);
}

void refreshDisp() {
  sevseg.refreshDisplay();
}

