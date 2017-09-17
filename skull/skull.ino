#include "DFPlayer_Mini_Mp3.h" 

#define lock A5
#define eyes 9
#define yes_btn 5
#define no_btn 3
#define LEDs 4
#define lang_btn A0
#define yes A3
#define no A4

#define chip A2
  
int val = 0;
bool yes_flag = true;
bool no_flag = true;

void setup() {
  delay(500);
  
  pinMode(lock, OUTPUT);
  pinMode(eyes, OUTPUT);  
  pinMode(LEDs, OUTPUT);
  pinMode(no, OUTPUT);  
  pinMode(yes, OUTPUT);

  digitalWrite(lock, LOW);
  digitalWrite(eyes, LOW);  
  digitalWrite(LEDs, LOW);
  digitalWrite(no, LOW);  
  digitalWrite(yes, LOW);
    
  pinMode(yes_btn, INPUT_PULLUP);
  pinMode(no_btn, INPUT_PULLUP);   
  pinMode(lang_btn, INPUT_PULLUP); 
   
  Serial.begin(9600);
  
  delay (100);
  mp3_set_serial (Serial);
  delay (100);
  mp3_set_volume (30);
  delay (100);
  mp3_set_EQ (0);
  delay (100);
}

void loop() {

  delay(100);
  
  while(!(val > 350 && val < 650)){ // chip inserted
    val = analogRead(chip);
    delay(100);
  }
 
  digitalWrite(LEDs, HIGH);   // turn on keyboard LEDs
  digitalWrite(eyes, HIGH);

  while(yes_flag && no_flag){ // is buttons pressed
   
    if (!digitalRead(lang_btn))mp3_play (1);
    else mp3_play (2);
  
    for(int i = 0; i < 1000; i++){
      delay(10);
      if( !digitalRead(yes_btn) ){
        yes_flag = false;
        digitalWrite(yes, HIGH);
        break; 
      }
      else if ( !digitalRead(no_btn) ){
        no_flag = false;
        digitalWrite(no, HIGH);
        break;
      }
    }
  }

  digitalWrite(LEDs, LOW);

  if(no_flag == 0){
    for(int i = 255; i >= 0; i-=5){
      analogWrite(eyes, i);
      delay(30);
    }
    digitalWrite(eyes, LOW);
  }

  delay(31000);
  
  digitalWrite(lock, HIGH);
 
  while(1);
}
