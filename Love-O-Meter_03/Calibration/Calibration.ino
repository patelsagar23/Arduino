const int sensorPin=A0;
float baselineTemp;
int switchState=0;
int x;
float runningSum = 0;
int sensorVal = analogRead(sensorPin);

void setup(){
  
  Serial.begin(9600);
  for(int pinNumber = 2; pinNumber<5; pinNumber++){
    pinMode(pinNumber,OUTPUT);
    digitalWrite(pinNumber, LOW);
  }
  pinMode(7,INPUT);
}

void loop(){
  switchState = digitalRead(7);
  if(switchState ==HIGH){
    
    int sensorVal = analogRead(sensorPin);
    float runningSum = 0;
    int x;
    
    digitalWrite(2,HIGH);
    digitalWrite(3,LOW);
    digitalWrite(4,LOW);
     for(x=0; x < 19; x++){
    runningSum = runningSum + (((sensorVal / 1024.0) * 5.0) - .5) * 100.0;
    delay(250);
     }
     
    digitalWrite(2,LOW);
    digitalWrite(3,HIGH);
    digitalWrite(4,LOW);
    delay(250);
    
    digitalWrite(2,LOW);
    digitalWrite(3,LOW);
    digitalWrite(4,HIGH);
    delay(250);
    
    digitalWrite(2,LOW);
    digitalWrite(3,LOW);
    digitalWrite(4,LOW);
    
  baselineTemp = runningSum/x;
  Serial.print("Baseline Temperature is: ");
  Serial.println(baselineTemp);
}
  
  else{
    int sensorVal = analogRead(sensorPin);
    Serial.print("Sensor Value: ");
    Serial.print(sensorVal);
    
    float voltage = (sensorVal/1024.0) * 5.0;
    Serial.print(", Volts: ");
    Serial.print(voltage);
    
    Serial.print(", degrees C: ");
    float temperature = (voltage - .5) * 100;
    Serial.println(temperature);
    
    if(temperature < baselineTemp){
      digitalWrite(2,LOW);
      digitalWrite(3,LOW);
      digitalWrite(4,LOW);
    
    }else if(temperature >=baselineTemp+1 && temperature < baselineTemp+2){
      digitalWrite(2,HIGH);
      digitalWrite(3,LOW);
      digitalWrite(4,LOW);
      
    }else if(temperature >=baselineTemp+2 && temperature < baselineTemp+3){
      digitalWrite(2,HIGH);
      digitalWrite(3,HIGH);
      digitalWrite(4,LOW);
      
    }else if(temperature >=baselineTemp+3 && temperature < baselineTemp+4){
      digitalWrite(2,HIGH);
      digitalWrite(3,HIGH);
      digitalWrite(4,HIGH);
    }
    delay(2000);
  }
}
