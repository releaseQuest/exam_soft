#include <LiquidCrystal.h>
#include <Keypad.h>

#define out 13
#define beep 2

const byte ROWS = 4;
const byte COLS = 3;

char keys[ROWS][COLS] = {
  {'9', '5', '1'},
  {'0', '6', '2'},
  {'*', '7', '3'},
  {'#', '8', '4'},
};

byte rowPins[ROWS] = {11, 6, 7, 9};
byte colPins[COLS] = {10, 12, 8};
int count = 0;
char password[4] = {0, 0, 0, 0};
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

LiquidCrystal lcd(A4, A5, A0, A1, A2, A3);

void setup() {
  pinMode(out, OUTPUT);
  pinMode(beep, OUTPUT);

  digitalWrite(out, LOW);
  digitalWrite(beep, LOW);

  lcd.begin(16, 2);
  lcd.setCursor(4, 0);
  lcd.print("Password");
  lcd.setCursor(6, 1);
  lcd.print("----");
  lcd.setCursor(6, 1);
  Serial.begin(9600);
}

void loop() {
  char key = kpd.getKey();
  if (key == '0' || key == '1' || key == '2' || key == '3' || key == '4' || key == '5' || key == '6' || key == '7' || key == '8' || key == '9') {
    beeps(100);
    password[count] = key;
    count++;
    lcd.print(key);
    if (password[0] == '7' && password[1] == '2' && password[2] == '5' && password[3] == '1') {
      lcd.setCursor(4, 0);
      lcd.print("Correct!");
      delay(500);
      beeps(100);
      delay(200);
      beeps(100);
      digitalWrite(out, HIGH);
      delay(10000);
      password[0] = 0;
      password[1] = 0;
      password[2] = 0;
      password[3] = 0;
      count = 0;
      lcd.setCursor(4, 0);
      lcd.print("Password");
      lcd.setCursor(6, 1);
      lcd.print("----");
      lcd.setCursor(6, 1);
      digitalWrite(out, LOW);
      
    } else if (count > 3) {
      password[0] = 0;
      password[1] = 0;
      password[2] = 0;
      password[3] = 0;
      count = 0;
      lcd.setCursor(4, 0);
      lcd.print(" Error! ");
      beeps(1500);
      delay(1500);
      lcd.setCursor(4, 0);
      lcd.print("Password");
      lcd.setCursor(6, 1);
      lcd.print("----");
      lcd.setCursor(6, 1);
    }
  }
  delay(30);
}

void beeps(int time){
  digitalWrite(beep, HIGH);
  delay(time);
  digitalWrite(beep, LOW);
}
