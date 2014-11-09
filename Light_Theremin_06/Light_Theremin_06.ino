int sensorValue;
int sensorlow = 1023;
int sensorhigh = 0;
const int ledPin = 13;

void setup(){
  pinMode(ledPin,OUTPUT);
  digitalWrite(ledPin,HIGH);
  while(millis()<5000){
    sensorValue = analogRead(A0);
    if (sensorValue>sensorhigh){
      sensorhigh = sensorValue;
    }
    if (sensorValue< sensorlow){
      sensorlow = sensorValue;
    }
  }
  digitalWrite(ledPin,LOW);
}

void loop(){
  sensorValue = analogRead(A0);
  int pitch= map(sensorValue,sensorlow,sensorhigh,50,4000);
  tone(8,pitch,20);
  delay(10);
}
