#define IN 9
#define OUT A3
#define LED 13

bool outFlag = false;

void setup() {
   pinMode(OUT, OUTPUT);
   pinMode(LED, OUTPUT);

  digitalWrite(OUT, HIGH);
  digitalWrite(LED, LOW);
      
  pinMode(IN, INPUT_PULLUP);
  delay(2000);
}

void loop() {
  if ( digitalRead(IN) ) {
    soundSensorController();
  }
}

void soundSensorController(void) {
  int counter = 0;
  int clapCounter = 0;
  bool toggleLightsFlag = false;
  bool skipFlag = false;
  int micState = 0;         // current state of the button
  int lastMicState = 0;     // previous state of the button

  while (counter <= 1200) {
    micState = digitalRead(IN);
    if (micState != lastMicState) {
      if(micState == HIGH){
        clapCounter ++;
      }
      delay(200);
    }
    lastMicState = micState;
    delay(1);
    counter ++;
  }

  if (clapCounter == 2) {
      digitalWrite(OUT, HIGH);
      digitalWrite(LED, HIGH);
      delay(150);
      digitalWrite(OUT, LOW);
      digitalWrite(LED, LOW);
  }
}
