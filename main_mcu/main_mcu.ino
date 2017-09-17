#include "TimerOne.h"
//outputs
// 220 v lights
#define aRoomMainLight A8
#define aRoomUVLight A9
#define bRoomMainLight A12
#define aRoomRedLight A10
#define waterValve A13
#define testRelay A14

// 12v HIGHes row

#define passesLock 46
#define underTVlock 47
#define microchipLock 48
#define betweenRoomsLock 49
#define headLock 50
#define aRoomCache 51
#define outLock 53
#define barcodePower 52

// 5v 12 v middle row
//colons 12v
#define lightColoneFR 38
#define lightColoneFL 40
#define lightColoneBR 41
#define lightColoneBL 39
//lasers 5v
#define laserFL 42
#define laserFR 44
#define laserBL 45
#define laserBR 43

//keyboard emulator
#define startBtn A7
#define doorCode A6
#define voiceRec A5
#define answerYes A4
#define answerNo A3
#define secondBtn A2
#define laserOn A1
#define gun A0
//inputs
//admin keys
#define greenKey 3
#define blueKey 5
#define whiteKey 6
#define yellowKey 4
#define redKey 7

//colons
#define keyColoneFR 27
#define keyColoneFL 23
#define keyColoneBR 25
#define keyColoneBL 24

//others
//room A up (swap?)
#define lightSensor 33
#define soundSensor 30

//head
//room B (swap?)
#define headYes 35
#define headNo 34
#define headOpen 29

//barcodes
#define barcodeReader 37

//code lock
#define codeLock 32

//pills
#define pillsRes 36

//clap manual
#define clapSelector 15
#define clapBtn 14

int interruptCounter = 0;

//------------------------flags---------------------
bool coloneIndexes[4] = {false, false, false, false};
bool permitionToMicrochip = false;
bool aRoomMainLightsFlag = true;

bool codeLockFlag = true;
bool barcodeReaderFlag = true;
bool pillSensorFlag = true;
bool soundSensorFirstRunFlag = true;
bool waterValveFlag = true;

bool headYesFlag = true;
bool headNoFlag = true;
bool headOpenFlag = true;
bool colonesOffFlag = true;
bool yellowKeyFlag = true;
bool lightSensorControllerFlag = true;

bool coloneSwitchFlag = true;
bool outBoxOpenFlag = false;
void setup() {
  //OUTPUTS INIT
  pinMode(aRoomMainLight, OUTPUT);
  pinMode(aRoomUVLight, OUTPUT);
  pinMode(bRoomMainLight, OUTPUT);
  pinMode(aRoomRedLight, OUTPUT);
  pinMode(waterValve, OUTPUT);
  pinMode(testRelay, OUTPUT);

  pinMode(passesLock, OUTPUT);
  pinMode(underTVlock, OUTPUT);
  pinMode(microchipLock, OUTPUT);
  pinMode(betweenRoomsLock, OUTPUT);
  pinMode(headLock, OUTPUT);
  pinMode(aRoomCache, OUTPUT);
  pinMode(outLock, OUTPUT);
  pinMode(barcodePower, OUTPUT);

  pinMode(lightColoneFR, OUTPUT);
  pinMode(lightColoneFL, OUTPUT);
  pinMode(lightColoneBR, OUTPUT);
  pinMode(lightColoneBL, OUTPUT);

  pinMode(laserFL, OUTPUT);
  pinMode(laserFR, OUTPUT);
  pinMode(laserBL, OUTPUT);
  pinMode(laserBR, OUTPUT);

  pinMode(startBtn, OUTPUT);
  pinMode(doorCode, OUTPUT);
  pinMode(voiceRec, OUTPUT);
  pinMode(answerYes, OUTPUT);
  pinMode(answerNo, OUTPUT);
  pinMode(secondBtn, OUTPUT);
  pinMode(laserOn, OUTPUT);
  pinMode(gun, OUTPUT);

  digitalWrite(aRoomMainLight, HIGH);
  digitalWrite(aRoomUVLight, HIGH);
  digitalWrite(bRoomMainLight, HIGH);
  digitalWrite(aRoomRedLight, HIGH);
  digitalWrite(waterValve, HIGH);
  digitalWrite(testRelay, HIGH);

  digitalWrite(passesLock, LOW);
  digitalWrite(underTVlock, LOW);
  delay(20);
  digitalWrite(microchipLock, LOW);
  delay(20);
  digitalWrite(betweenRoomsLock, LOW);
  delay(20);
  digitalWrite(headLock, LOW);
  delay(20);
  digitalWrite(aRoomCache, LOW);
  delay(20);
  digitalWrite(outLock, HIGH);
  delay(20);
  digitalWrite(barcodePower, HIGH);

  delay(20);
  digitalWrite(lightColoneFR, LOW);
  delay(20);
  digitalWrite(lightColoneFL, LOW);
  delay(20);
  digitalWrite(lightColoneBR, LOW);
  delay(20);
  digitalWrite(lightColoneBL, LOW);

  digitalWrite(laserFL, HIGH);
  digitalWrite(laserFR, HIGH);
  digitalWrite(laserBL, HIGH);
  digitalWrite(laserBR, HIGH);

  digitalWrite(startBtn, LOW);
  digitalWrite(doorCode, LOW);
  digitalWrite(voiceRec, LOW);
  digitalWrite(answerYes, LOW);
  digitalWrite(answerNo, LOW);
  digitalWrite(secondBtn, LOW);
  digitalWrite(laserOn, LOW);
  digitalWrite(gun, LOW);

  //INPUTS INIT
  pinMode(greenKey, INPUT_PULLUP);
  pinMode(blueKey, INPUT_PULLUP);
  pinMode(whiteKey, INPUT_PULLUP);
  pinMode(yellowKey, INPUT_PULLUP);
  pinMode(redKey, INPUT_PULLUP);

  pinMode(keyColoneFR, INPUT_PULLUP);
  pinMode(keyColoneFL, INPUT_PULLUP);
  pinMode(keyColoneBR, INPUT_PULLUP);
  pinMode(keyColoneBL, INPUT_PULLUP);

  pinMode(lightSensor, INPUT_PULLUP);
  pinMode(soundSensor, INPUT_PULLUP);

  pinMode(headYes, INPUT_PULLUP);
  pinMode(headNo, INPUT_PULLUP);
  pinMode(headOpen, INPUT_PULLUP);

  pinMode(barcodeReader, INPUT_PULLUP);

  pinMode(codeLock, INPUT_PULLUP);

  pinMode(pillsRes, INPUT_PULLUP);

  pinMode(clapSelector, INPUT_PULLUP);
  pinMode(clapBtn, INPUT_PULLUP);


  Serial.begin(9600);
  Serial.print("ok");
  delay (5000);
}

void loop() {

  //------------------------Admin keys------------------------
  if ( !digitalRead(greenKey) ) {
    digitalWrite(startBtn, HIGH);
    delay(100);
    digitalWrite(startBtn, LOW);
    delay(200);
  }
  if ( !digitalRead(blueKey) ) {
    digitalWrite(passesLock, HIGH);
  } else {
    digitalWrite(passesLock, LOW);
  }
  if ( !digitalRead(whiteKey) ) {
    digitalWrite(underTVlock, HIGH);
  } else {
    digitalWrite(underTVlock, LOW);
  }
  if ( !digitalRead(yellowKey) ) {
    yellowKeyFlag = false;
    digitalWrite(laserFR, LOW);
    digitalWrite(gun, HIGH);
    delay(100);
    digitalWrite(gun, LOW);

  }

  if ( !digitalRead(redKey) ) {
    digitalWrite(secondBtn, HIGH);
    delay(100);
    digitalWrite(secondBtn, LOW);
    delay(200);
  }


  //-----------------------Colons keys-------------------------
  if ( !digitalRead(keyColoneFR) ) {
    coloneSwitchController(0);
  }

  if ( !digitalRead(keyColoneFL) ) {
    coloneSwitchController(1);
  }

  if ( !digitalRead(keyColoneBR) ) {
    coloneSwitchController(2);
  }

  if ( !digitalRead(keyColoneBL) ) {
    coloneSwitchController(3);
  }


  //---------------------"A" room roof sensos-------------------
  if ( !digitalRead(lightSensor) ) {
    lightSensorController();
  }


  if ( (!digitalRead(soundSensor) && digitalRead(clapSelector) ) || (!digitalRead(clapBtn) && !digitalRead(clapSelector) ) ) {
    soundSensorController();
  }

  //--------------------Head switches---------------------------
  if ( (!digitalRead(headYes) && headYesFlag) || (!digitalRead(headNo) && headNoFlag) ) {
    //Serial.print(" head ");
    delay(50);
    if ( !digitalRead(headYes) && headYesFlag ) {
      headYesFlag  = false;
      yesController();
    }

    if ( !digitalRead(headNo) && headNoFlag) {
      headNoFlag  = false;
      noController();
    }
  }
  if ( !digitalRead(headOpen) && outBoxOpenFlag) {
    digitalWrite(outLock, LOW);
  }

  //--------------------Other stuff-----------------------------
  if ( digitalRead(barcodeReader) && permitionToMicrochip && barcodeReaderFlag) {
    barcodeReaderController();
    barcodeReaderFlag = false;
  }

  if ( !digitalRead(codeLock)) {
    digitalWrite(betweenRoomsLock, HIGH);
    if (codeLockFlag) {
      codeLockController();
      codeLockFlag = false;
    }
  } else {
    digitalWrite(betweenRoomsLock, LOW);
  }

  if ( !digitalRead(pillsRes) && pillSensorFlag) {
    pillSensorController();
    pillSensorFlag = false;
    outBoxOpenFlag = true;
  }
}

//---------------------Controllers-------------------------------

void barcodeReaderController(void) {
  digitalWrite(microchipLock, HIGH);
  delay(200);
}

void pillSensorController(void) {
  digitalWrite(headLock, HIGH);
  delay(20);
  digitalWrite(barcodePower, LOW);
  permitionToMicrochip = true;
  delay (200);
}

void lightSensorController(void) {
  digitalWrite(aRoomUVLight, HIGH);
  delay(20);
  digitalWrite(aRoomRedLight, LOW);

  delay(20);
  if (lightSensorControllerFlag) {
    lightSensorControllerFlag = false;
    digitalWrite(laserBR, LOW);
    digitalWrite(laserOn, HIGH);
    delay(100);
    digitalWrite(laserOn, LOW);
  }
  if (waterValveFlag) {
    digitalWrite(waterValve, LOW);
    delay(3000);
    digitalWrite(waterValve, HIGH);
    waterValveFlag = false;
    Timer1.initialize(6000000);
    Timer1.attachInterrupt(setWaterValveFlag, 6000000);
  }

}

void soundSensorController(void) {
  if (aRoomMainLightsFlag) {

    delay(20);
    digitalWrite(aRoomMainLight, LOW);
    aRoomMainLightsFlag = false;
    if (soundSensorFirstRunFlag) {
      soundSensorFirstRunFlag = false;
      delay(20);
      digitalWrite(laserFL, LOW);
      digitalWrite(laserOn, HIGH);
      delay(100);
      digitalWrite(laserOn, LOW);

      delay(50);
    }
  } else {
    delay(20);
    digitalWrite(aRoomMainLight, HIGH);
    aRoomMainLightsFlag = true;
    delay(50);
  }
  digitalWrite(aRoomCache, HIGH);
  delay(500);
  digitalWrite(aRoomCache, LOW);
 
}

void coloneSwitchController(int colone) {
  switch (colone) {
    case 0:
      delay(20);
      if (coloneIndexes[colone]) digitalWrite(lightColoneFR, LOW);
      else digitalWrite(lightColoneFR, HIGH);
      delay(500);
      break;
    case 1:
      delay(20);
      if (coloneIndexes[colone]) digitalWrite(lightColoneFL, LOW);
      else digitalWrite(lightColoneFL, HIGH);
      delay(500);
      break;
    case 2:
      delay(20);
      if (coloneIndexes[colone]) digitalWrite(lightColoneBR, LOW);
      else digitalWrite(lightColoneBR, HIGH);
      delay(500);
      break;
    case 3:
      delay(20);
      if (coloneIndexes[colone]) digitalWrite(lightColoneBL, LOW);
      else digitalWrite(lightColoneBL, HIGH);
      delay(500);
      break;
  }
  coloneIndexes[colone] = ! coloneIndexes[colone];
  if (coloneIndexes[0] && coloneIndexes[1] && coloneIndexes[2] && coloneIndexes[3] && coloneSwitchFlag) {
    coloneSwitchFlag = false;
    delay(20);
    digitalWrite(aRoomRedLight, HIGH);
    delay(20);
    digitalWrite(aRoomUVLight, LOW);
    delay(20);
    if (colonesOffFlag) {
      colonesOffFlag = false;
      digitalWrite(laserBL, LOW);
      digitalWrite(laserOn, HIGH);
      delay(100);
      digitalWrite(laserOn, LOW);
    }
  }
  if (!coloneIndexes[0] && !coloneIndexes[1] && !coloneIndexes[2] && !coloneIndexes[3] && !coloneSwitchFlag) {
    coloneSwitchFlag = true;
    digitalWrite(aRoomUVLight, LOW);
    digitalWrite(aRoomRedLight, HIGH);
  }
}

void codeLockController() {
  delay(20);
  digitalWrite(bRoomMainLight, LOW);
  delay(20);
  digitalWrite(doorCode, HIGH);
  delay(200);
}

void shootController() {
  delay(20);
  digitalWrite(laserFR, LOW);
  digitalWrite(laserOn, HIGH);
  delay(100);
  digitalWrite(laserOn, LOW);
}

void yesController() {
  digitalWrite(bRoomMainLight, HIGH);
  digitalWrite(answerYes, HIGH);
  delay(100);
  digitalWrite(answerYes, LOW);

}

void noController() {
  digitalWrite(bRoomMainLight, HIGH);
  digitalWrite(answerNo, HIGH);
  delay(100);
  digitalWrite(answerNo, LOW);

}
//---------------------------------Interrupts------------------------------------------

void setWaterValveFlag() {
  interruptCounter++;
  if (interruptCounter >= 50) {
    waterValveFlag = true;
    Timer1.detachInterrupt();
    interruptCounter = 0;
  }
}
