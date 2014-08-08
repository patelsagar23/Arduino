int switchState = 0;
const int sensorPin=A0;

int sensorVal = analogRead(sensorPin);
float voltage = (sensorVal/1024.0) * 5.0;
float temperature = (voltage - .5) * 100;

void setup(){
  Serial.begin(9600);
  pinMode(7,INPUT);
}

void loop(){
  switchState = digitalRead(7);
  if (switchState == HIGH) {
    
    int sensorVal = analogRead(sensorPin);
    float voltage = (sensorVal/1024.0) * 5.0;
    float temperature = (voltage - .5) * 100;
    const float baselineTemp = temperature;
    
    Serial.print("Debug Values: ");
    Serial.println(baselineTemp);
    
    Serial.print("Sensor Value: ");
    Serial.print(sensorVal);
    Serial.print(", Volts: ");
    Serial.print(voltage);
    Serial.print(", degrees C: ");
    Serial.println(temperature);
  }
  
  else{
   
    int sensorVal = analogRead(sensorPin);
    float voltage = (sensorVal/1024.0) * 5.0;
    float temperature = (voltage - .5) * 100;
    
    const float baselineTemp = temperature;
    Serial.println(baselineTemp);
 
  }
  delay(2000);
}



