#include "Keyboard.h"
const int AdminBTN1 = 2;
const int DoorCode = 3;
const int VoiceRecogn = 4;
const int Yes = 5;
const int No = 6;
const int AdminBTN2 = 7;
const int LaserOn = 8;
const int gun = 9;
int i1 = 0, i2 = 0, i3 = 0, i4 = 0, i5 = 0, i6 = 0, i7 = 0, i8 = 0;
void setup() {
  pinMode(AdminBTN1, INPUT_PULLUP);
  pinMode(DoorCode, INPUT_PULLUP);
  pinMode(VoiceRecogn, INPUT_PULLUP);
  pinMode(Yes, INPUT_PULLUP);
  pinMode(No, INPUT_PULLUP);
  pinMode(AdminBTN2, INPUT_PULLUP);
  pinMode(LaserOn, INPUT_PULLUP);
  pinMode(gun, INPUT_PULLUP);  
  Keyboard.begin();
}

void loop() {
 // while(digitalRead(AdminBTN1) == HIGH && digitalRead(DoorCode) == HIGH && digitalRead(VoiceRecogn) == HIGH && digitalRead(Yes) == HIGH && digitalRead(No) == HIGH && digitalRead(AdminBTN2) == HIGH && digitalRead(LaserOn) == HIGH);
  
  if(digitalRead(AdminBTN1) == LOW && i1 == 0){
    Keyboard.write(KEY_F8);
    i1 = 1;
    delay(500);
  }
  if(digitalRead(DoorCode) == LOW && i2 == 0){
    Keyboard.write(KEY_F3);
    i2 = 1;
    delay(500);
  }
  if(digitalRead(VoiceRecogn) == LOW && i3 == 0){
    Keyboard.write(KEY_F9);
    i3 = 1;
    delay(500);
  }
  if(digitalRead(Yes) == LOW && i4 == 0){
    Keyboard.write(KEY_INSERT);
    i4 = 1;
    delay(500);
  }
  if(digitalRead(No) == LOW && i5 == 0){
    Keyboard.write(KEY_HOME);
    i5 = 1;
    delay(500);
  }
  if(digitalRead(AdminBTN2) == LOW && i6 == 0){
    Keyboard.write(KEY_F7);
    i6 = 1;
    delay(500);
  }
  if(digitalRead(LaserOn) == LOW && i7 == 0){
    Keyboard.write(KEY_F12);
    i7 = 1;
    delay(500);
  }
  if(digitalRead(gun) == LOW && i8 == 0){
    Keyboard.write(KEY_PAGE_UP);
    i8 = 1;
    delay(500);
  }

  if(digitalRead(AdminBTN1) == HIGH && i1 == 1) i1 = 0;
  else if(digitalRead(DoorCode) == HIGH && i2 == 1) i2 = 0;
  else if(digitalRead(VoiceRecogn) == HIGH && i3 == 1) i3 = 0;
  else if(digitalRead(Yes) == HIGH && i4 == 1) i4 = 0;
  else if(digitalRead(No) == HIGH && i5 == 1) i5 = 0;
  else if(digitalRead(AdminBTN2) == HIGH && i6 == 1) i6 = 0;
  else if(digitalRead(LaserOn) == HIGH && i7 == 1) i7 = 0;
  else if(digitalRead(gun) == HIGH && i8 == 1) i8 = 0;
}

