#define lock A4
#define sw 2
#define led 13

void setup() {
  pinMode(lock, OUTPUT);
  pinMode(sw, INPUT_PULLUP);

  digitalWrite(lock, HIGH);
  delay(100);
}

void loop() {
  if( !digitalRead(sw) ){
    digitalWrite(lock, LOW);
    delay(5000);
    digitalWrite(lock, HIGH);
  }
     
}
