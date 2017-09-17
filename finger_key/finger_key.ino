
#include <UTFT.h>

// Declare which fonts we will be using
extern uint8_t SmallFont[];

#define hall A0
UTFT myGLCD(TFT01_22SP,5,6,2,3,4);  // ElecFreaks TFT01-2.2SP

//const int analogInPin = A0;
const int buttonPin = 12;
const int RelPin =  13;

uint16_t open = 1;
int skip = 0;
void setup(){
  delay(1000);
  myGLCD.InitLCD(LANDSCAPE);
  delay(100);
  myGLCD.fillScr(VGA_WHITE);
  
  pinMode(5, OUTPUT);
  digitalWrite(5, HIGH);

delay(100);
  pinMode(RelPin, OUTPUT);
  delay(100);
  digitalWrite(RelPin,LOW);
  delay(100);
  pinMode(buttonPin, INPUT);
  pinMode(hall, INPUT);
  delay(100);
  Serial.begin(9600);
  delay(100);
 
}

void loop(){
  while(open){

    if(!digitalRead(buttonPin)){
        skip = 0;
        myGLCD.setColor(VGA_WHITE);
        myGLCD.fillCircle(30,30, 10);
        delay(20);
        myGLCD.setColor(VGA_BLACK);
        myGLCD.setBackColor(0, 0, 255);
        myGLCD.drawLine(0, 0, 0, 240);
        myGLCD.drawLine(1, 0, 1, 240);
        myGLCD.drawLine(2, 0, 2, 240);
        myGLCD.drawLine(3, 0, 3, 240);
        myGLCD.drawLine(4, 0, 4, 240);
        myGLCD.drawLine(5, 0, 5, 240);
        myGLCD.drawLine(6, 0, 6, 240);
        myGLCD.setColor(VGA_WHITE);
        delay(20);

        for (uint16_t i = 0; i < 320;i++){
            myGLCD.setColor(VGA_WHITE);
            delay(10);
            myGLCD.drawLine(i, 0, i, 240);
            delay(10);
            myGLCD.setColor(VGA_BLACK);
            delay(10);
            myGLCD.drawLine(i+7, 0, i+7, 240);
            delay(10);
            if(digitalRead(hall)){
              skip = 1;
            }
        }
        if(skip==0)open = 0;
        else{
          myGLCD.setColor(VGA_RED);
          delay(10);
          myGLCD.fillCircle(30,30, 10);
          delay(10);
        }
     }
        delay(100);
  }
  myGLCD.setColor(VGA_WHITE);
  delay(10);
  myGLCD.fillCircle(30,30, 10);
  delay(10);
  
  myGLCD.setColor(VGA_GREEN);
  delay(10);
  myGLCD.fillCircle(30,30, 10);
  delay(10);
  digitalWrite(RelPin, HIGH);

  while(1);

}
