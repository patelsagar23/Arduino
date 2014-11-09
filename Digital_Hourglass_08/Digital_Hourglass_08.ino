const int tilt = 8;
unsigned long previousTime = 0;
int switchState = 0;
int prevswitchState = 0;
int led = 2;
long interval = 10000;
int l=13;

void setup(){
  for(int x = 2;x<8;x++){
    pinMode(x,OUTPUT);
  }
  
  pinMode(l,OUTPUT);
  digitalWrite(l,LOW);
  
  pinMode(tilt,INPUT);
}

void loop(){
  unsigned long currentTime = millis();
  if (currentTime>0){
    digitalWrite(l,HIGH);
  }
  if (currentTime - previousTime > interval){
    previousTime = currentTime;
    digitalWrite(led,HIGH);
    led++;
    if(led == 8){
      digitalWrite(l,LOW);
      for(int x = 2;x<8;x++){
        delay(250);
        digitalWrite(x,LOW);
      }
      for(int x = 2;x<8;x++){
        digitalWrite(x,HIGH);
      }
    }
    switchState= digitalRead(tilt);
    if(switchState != prevswitchState){
      for(int x = 2;x<8;x++){
        digitalWrite(x,LOW);
      }
      led =2;
      previousTime = currentTime;
    }
    prevswitchState = switchState;
  }
}


