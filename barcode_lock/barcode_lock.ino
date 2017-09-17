
String buf="";
String one = "4600395004698\r";
String two = "5013662210019\r";
String three = "8594052538571\r";
String four = "4820008125286\r";
int i = 0;
int order = 0;

#define relay 2
#define BEEP 3

void beep(){
  digitalWrite(BEEP, HIGH);
  delay(1500);
  digitalWrite(BEEP, LOW);  
}

void beep_s(){
  digitalWrite(BEEP, HIGH);
  delay(200);
  digitalWrite(BEEP, LOW);  
}

void wrong(){
  buf = "";
  i=0;
  order = 0;
  beep();  
}
void setup() {
  // initialize both serial ports:
  Serial.begin(9600);
  Serial1.begin(9600);
  pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH);
  
  pinMode(BEEP, OUTPUT);
  digitalWrite(BEEP, LOW);
}

void loop() {

  if(Serial1.available()){
    char ch = (char) Serial1.read();
    buf += ch;
    i++;    
  }
  
  if(i == 14){
    // 1st code
    if(buf == one){
      if(order == 0){
        Serial.print(buf);
        Serial.print('\n');
        buf = "";
        i=0;
        order = 1;
        beep_s();
      }
      else wrong();
    }
    // 2nd code
    else if(buf == two){
      if(order == 1){
        Serial.print(buf);
        Serial.print('\n');
        buf = "";
        i=0;
        order = 2;
        beep_s();
      }
      else wrong();
    }
    // 3rd code
    else if(buf == three){
      if(order == 2){
        Serial.print(buf);
        Serial.print('\n');
        buf = "";
        i=0;
        order = 3;
        beep_s();
      }
      else wrong();
    }
    //4rd code
    else if(buf == four){
      if(order == 3){
        Serial.print(buf);
        Serial.print('\n');
        buf = "";
        i=0;
        digitalWrite(BEEP, HIGH);
        delay(100);
        digitalWrite(BEEP, LOW);
        delay(300); 
        digitalWrite(BEEP, HIGH);
        delay(100);
        digitalWrite(BEEP, LOW);  
        digitalWrite(relay, LOW);
        while(1);
      }
      else wrong();
    }
    else wrong();
   
  }
}
