#define sound_sensor A3
#define light_sensor A5
#define sound_out 3
#define light_out 4

const int SOUND_SAMPLE_LENGTH = 6000; 
const int CLAP_DURATION_WINDOW = 30000;
const int CLAPS_FOR_TRIGGER = 2; 

bool light_flag = false;

int soundSampleLength = SOUND_SAMPLE_LENGTH;
int clapDurationWindow = CLAP_DURATION_WINDOW;
int currentClaps = 0;
int claps = 0;

void setup() {
  pinMode(sound_sensor, INPUT);
  pinMode(light_sensor, INPUT);

  pinMode(sound_out, OUTPUT);
  pinMode(light_out, OUTPUT);

  digitalWrite(sound_out, LOW);
  digitalWrite(light_out, LOW);

  Serial.begin(57600);
}

void loop() {
  if ( !digitalRead(light_sensor) && !light_flag) {
    Serial.println("light");
    digitalWrite(light_out, HIGH);
    delay(50);
    digitalWrite(light_out, LOW);
    light_flag = true;
  } else if (digitalRead(light_sensor) && light_flag) {
    light_flag = false;
  }

  soundSensorCntrl();
  
}

void soundSensorCntrl(){

  if ( digitalRead(sound_sensor) ) {
    currentClaps ++;
  }

  if(currentClaps > 0){
    soundSampleLength--;
  }

  if(soundSampleLength == 0){
    Serial.println("2");
    claps ++;
    currentClaps = 0;
    soundSampleLength = SOUND_SAMPLE_LENGTH;
  }
  
  if(clapDurationWindow == 0){
    Serial.println("3");
    if(claps == 2){
      pulseSound();
      
    }
    currentClaps = 0;
    claps = 0;
    clapDurationWindow = CLAP_DURATION_WINDOW;
  }
  
  if(currentClaps || claps){
    clapDurationWindow--;
  }
  
}

void pulseSound(){
  Serial.println("sound");
  digitalWrite(sound_out, HIGH);
  delay(50);
  digitalWrite(sound_out, LOW);
  delay(300);
}
