//Setting the Constants for the code

//Constants for the LED
const int greenLEDPin = 9;
const int redLEDPin = 11;
const int blueLEDPin = 10;

//Constants for the sensors
const int redSensorPin = A0;
const int greenSensorPin = A1;
const int blueSensorPin = A2;

//Int variables
int red = 0;
int green = 0;
int blue = 0;
int redvalue = 0;
int greenvalue = 0;
int bluevalue = 0;

void setup(){
  Serial.begin(9600);
  
  //Setting pins as outputs
  pinMode(greenLEDPin,OUTPUT);
  pinMode(redLEDPin,OUTPUT);
  pinMode(blueLEDPin,OUTPUT);
}

void loop(){
  
  //Reading the values of all the sensors
  redvalue = analogRead(redSensorPin);
  delay(5);
  greenvalue = analogRead(greenSensorPin);
  delay(5);
  bluevalue = analogRead(blueSensorPin);
  delay(5);
  
  //Display the readings
  Serial.print("Raw Sensor Values: /t Red: ");
  Serial.print(redvalue);
  Serial.print("/t Green");
  Serial.print(greenvalue);
  Serial.print("/t Blue");
  Serial.println(bluevalue);
  
  //Converting the values to PWM values for the LED
  red = redvalue/4;
  green = greenvalue/4;
  blue = bluevalue/4;
  
  //PWM values calculated above
  Serial.print("Mapped Sensor Values /t Red: ");
  Serial.print(red);
  Serial.print("/t Green: ");
  Serial.print(green);
  Serial.print("/t Blue: ");
  Serial.println(blue);
  
  //Setting the output values to the LED
  analogWrite(redLEDPin, red);
  analogWrite(greenLEDPin, green);
  analogWrite(blueLEDPin, blue);
}
